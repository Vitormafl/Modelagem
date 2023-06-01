const getTurnos = (texto) => texto.split("Novo Feixo").slice(2).map(palavra => palavra.trim()).filter(palavra => palavra.length > 1);
const separarTurnos = (texto) => texto.map((elemento, indice) => texto.slice(indice, indice+4));
let tirarElementos = (texto) => texto.filter((e,i) => i%4 == 0)
let separarPontos = (texto) => texto.map(elemento => elemento.map(palavra => palavra.split("),").filter(a => a.length > 0).map(pontoTexto => pontoTexto.trim().split(",").map(a => parseFloat(a.split("").filter(b => b != "(").join(""))))));
let criarPontos = (texto) => texto.map(turno => turno.map(tipo => tipo.map(ponto => {return {x: ponto[0], y: ponto[1]}})))
let criarTurnos = (texto) => texto.map(elemento => {return {esquerdo: elemento[0], direito: elemento[1], inferior: elemento[2], superior: elemento[3]}})


class Historico{

  constructor(texto){
    this.pontos = this.extrairPontos(texto);
    this.dicionario = this.construirDicionario();
    this.turnos = this.extrairTurnos(texto);

    this.mapear();

  }

  extrairTurnos(texto){
    let turnos = criarTurnos(criarPontos(separarPontos(tirarElementos(separarTurnos(getTurnos(texto))))))
    
    return turnos;
  }

  construirDicionario(){

    const dicionario = {};

    for(const ponto of this.pontos){
        const x = ponto.x;
        const y = ponto.y;

        if(!dicionario[x]) 
            dicionario[x] = {};
            
        dicionario[x][y] = ponto;
    }

    return dicionario;

  }

  extrairPontos(texto){
    let pontos = criarPontos(separarPontos([[texto.split("Novo Feixo")[1].trim()]]))[0][0];

    return pontos.map((ponto, i) => ({...ponto, indice:i}));
  }

  mapear(){

    const mapearPonto = feixo => feixo.map(ponto => {
        try{
            return this.dicionario[ponto.x][ponto.y]
        }
        catch(error){
            return {x:0,y:0,indice:492304, erro:"Esse resultado é um erro"};
        }
    });

    this.turnos = this.turnos.map(turno => ({
                                            esquerdo:mapearPonto(turno.esquerdo), 
                                            direito: mapearPonto(turno.direito),
                                            inferior:mapearPonto(turno.inferior),
                                            superior:mapearPonto(turno.superior)
    }));

    const desfatorar = turno => [turno.esquerdo, turno.direito];

    const concatenar = (soma, esquerdoDireito) => soma.concat(esquerdoDireito);

    //Retorna se o feixo está sendo repetido
    const repetido = (feixo, feixoRepetido) => feixoRepetido.map(pontos => pontos.length == feixo.length && pontos.map(ponto => ponto in feixo)).reduce((a,b) => a && b, false);

    const mapearFeixoLeft  = (feixo,turnos) => turnos.map(turno => repetido(feixo,turno.esquerdo)? ({...turno, esquerdo:feixo}) : turno.esquerdo);
    const mapearFeixoRight = (feixo,turnos) => turnos.map(turno => repetido(feixo,turno.direito)?  ({...turno,  direito:feixo}) : turno.direito);

    const mapearFeixo      = feixo => mapearFeixoRight(feixo,mapearFeixoLeft(feixo,this.turnos));

    this.feixos = [];

    for(let i = 0; i < this.turnos.length; i++){

      let feixo;

      feixo = this.turnos[i].esquerdo;

      if(!(feixo in this.feixos)){
        this.turnos = mapearFeixo(feixo);
        this.feixos.push(feixo);
      }

      feixo = this.turnos[i].direito;

      if(!(feixo in this.feixos)){
        this.turnos = mapearFeixo(feixo);
        this.feixos.push(feixo);
      }
    }

    let a = 0;

    for(const feixo of this.feixos){
      feixo.indice = a++;
    }

    console.log(this.feixos);

    return this;
  }
}

class Animador{

    constructor(historico, canvasContext){
        this.historico = historico;
        this.contexto = canvasContext;
        this.frames = this.getFrames();
        this.previousTimestamp = 0;
        this.feixos = {};
        this.pilha = [];
    }

    rodarTurno(indice){
        
        const turno = this.historico.turnos[indice];

        // console.log(this.pilha)
      
        const getlength = (pilha) => (pilha.maiorEsquerdo)? pilha.maiorEsquerdo.length + pilha.maiorDireito.length : 0;

        if(getlength(this.pilha) < turno.esquerdo.length + turno.direito.length){
          this.pilha.maiorEsquerdo = turno.esquerdo;
          this.pilha.maiorDireito  =  turno.direito;
        }
        
        const maiorEsquerdo = this.pilha.maiorEsquerdo;
        const maiorDireito = this.pilha.maiorDireito;

        this.pilha = [turno.esquerdo, turno.direito, this.pilha.maiorEsquerdo, this.pilha.maiorDireito];
        this.pilha.maiorDireito = maiorDireito;
        this.pilha.maiorEsquerdo = maiorEsquerdo;
    }

    desenharFeixo(feixo, cor = 'blue'){

        const ctx = this.contexto;

        const corrigido = feixo.map(ponto => ({y:ponto.x*100, x:ponto.y*100+400}));

        corrigido.forEach((a,i) => {

            const startPoint = a;
            const endPoint = corrigido[(i+1)%corrigido.length];

            ctx.beginPath();
            ctx.moveTo(startPoint.x, startPoint.y);
            ctx.lineTo(endPoint.x, endPoint.y);
            ctx.strokeStyle = cor;
            ctx.lineWidth = 3;
            ctx.stroke();
            ctx.closePath();
        })
    }

    desenharVertices(){

        const ctx = this.contexto;

        const highlighted = (ponto) => this.pilha.reduce((a,b) => a.concat(b),[]).filter(p => p && p.x == ponto.x && p.y == ponto.y).length > 0;

        // Array of circle objects
        const circles = this.historico.pontos.map(ponto => ({y: ponto.x*100, x: ponto.y*100+400, radius:3, inside: highlighted(ponto)}));
        
        // Draw circles on the canvas
        circles.forEach(function(circle) {
            ctx.beginPath();
            ctx.arc(circle.x, circle.y, circle.radius, 0, 2 * Math.PI);
            ctx.fillStyle = (circle.inside)? 'red':'purple';
            ctx.fill();
            ctx.closePath();
        });
    }

    *getFrames(){
      for(let turno = 0; turno < this.historico.turnos.length; turno++){
        yield this.rodarTurno(turno);
      }
    }
}

//Fazer pilha do merge: desenhar todos os feixos já escritos
//Adicionar os indices dos pontos dele ao dicionário
//Se algum dos pontos já estiver no dicionário, então remover ele da pilha

// Create an input element to allow the user to select a file
var input = document.createElement('input');
input.type = 'file';

input.multiple = true;
let previousTimestamp = 0;
let tempo = 0;
const animadores = [];


// Listen for changes in the input element
input.addEventListener('change', function(e) {

  // Create a canvas element
  var canvas = document.createElement('canvas');
  canvas.width = 800;
  canvas.height = 800;
  
  // Add the canvas to the document
  document.body.appendChild(canvas);
  
  // Get the 2D context of the canvas
  var ctx = canvas.getContext('2d');

  console.log(e.target.files);

  const files  = e.target.files;


  for(const file of files){
  
    var reader = new FileReader(); // Create a new FileReader instance
    
    // Define a function to be executed when the file is successfully loaded
    reader.onload = function(e) {
      var contents = e.target.result; // Get the file contents

      const historico = new Historico(contents);

      console.log(historico);

      animadores.push(new Animador(historico, ctx));

      animadores.map(animador => animador.desenharVertices());

    };
    
    reader.readAsText(file); // Read the file as text
  }
});

document.addEventListener('DOMContentLoaded', () =>document.getElementById("centro").append(input))

function animate(timestamp = 0) {

  tempo += timestamp - previousTimestamp;

  previousTimestamp = timestamp;

  if(tempo > 50){

      try{
          if(animadores && animadores[0]){
            animadores[0].contexto.clearRect(0, 0, 800, 800);
          }
          animadores.forEach(animador =>{
            animador.frames.next();
            animador.desenharVertices();
            animador.pilha.forEach(feixo => animador.desenharFeixo(feixo));
          })
      }
      catch(erro){
          console.log(erro);
      }
      tempo = 0;
  }

  requestAnimationFrame(animate);
}

requestAnimationFrame(animate);