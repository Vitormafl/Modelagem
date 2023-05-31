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

    const mapearPonto = tipo => tipo.map(ponto => {
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

    return this;
  }
}

class Animador{

    constructor(historico, canvasContext){
        this.historico = historico;
        this.contexto = canvasContext;
        this.turno = 0;
        this.previousTimestamp = 0;
    }

    rodarTurno(indice){
        
        const turno = this.historico.turnos[indice];

        this.maiorFeixoEsquerdo = (this.maiorFeixoEsquerdo)? 
                                  (this.maiorFeixoEsquerdo.length > turno.esquerdo.length)? 
                                  this.maiorFeixoEsquerdo :
                                  turno.esquerdo :
                                  turno.esquerdo;

        this.maiorFeixoDireito = (this.maiorFeixoDireito)? 
                                  (this.maiorFeixoDireito.length > turno.direito.length)? 
                                  this.maiorFeixoDireito :
                                  turno.direito :
                                  turno.direito;

        this.desenharFeixo(this.maiorFeixoEsquerdo, 'red');
        this.desenharFeixo(this.maiorFeixoDireito, 'red');

        this.desenharFeixo(turno.esquerdo);
    }

    desenharFeixo(feixo, cor = 'blue'){

        const ctx = this.contexto;

        const corrigido = feixo.map(ponto => ({x:ponto.x*100, y:ponto.y*100+400}));

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
        // Array of circle objects
        const circles = this.historico.pontos.map(ponto => ({x: ponto.x*100, y: ponto.y*100+400, radius:3}))
        
        // Draw circles on the canvas
        circles.forEach(function(circle) {
            ctx.beginPath();
            ctx.arc(circle.x, circle.y, circle.radius, 0, 2 * Math.PI);
            ctx.fillStyle = 'purple';
            ctx.fill();
            ctx.closePath();
        });
    }

    animate(timestamp) {

        const elapsedTime      = timestamp - this.previousTimestamp;
        this.previousTimestamp = timestamp;

        this.contexto.clearRect(0, 0, 800, 800);
        this.desenharVertices();
        try{
            this.rodarTurno(Math.round(this.turno));
        }
        catch(erro){
            console.log(erro);
        }

        this.turno += elapsedTime/100;

        this.turno = Math.min(this.turno, this.historico.turnos.length-1)
        
        requestAnimationFrame(this.animate.bind(this));
    }
}

//Fazer pilha do merge: desenhar todos os feixos já escritos
//Adicionar os indices dos pontos dele ao dicionário
//Se algum dos pontos já estiver no dicionário, então remover ele da pilha

// Create an input element to allow the user to select a file
var input = document.createElement('input');
input.type = 'file';

// Listen for changes in the input element
input.addEventListener('change', function(e) {
  var file = e.target.files[0]; // Get the selected file
  
  var reader = new FileReader(); // Create a new FileReader instance
  
  // Define a function to be executed when the file is successfully loaded
  reader.onload = function(e) {
    var contents = e.target.result; // Get the file contents
    
    const historico = new Historico(contents);

    // Create a canvas element
    var canvas = document.createElement('canvas');
    canvas.width = 800;
    canvas.height = 800;
    
    // Add the canvas to the document
    document.body.appendChild(canvas);
    
    // Get the 2D context of the canvas
    var ctx = canvas.getContext('2d');

    const animador = new Animador(historico, ctx);

    animador.desenharVertices();

    // animador.rodarTurno(historico.turnos.length-1);
    animador.animate(0);
  };
  
  reader.readAsText(file); // Read the file as text
});

document.addEventListener('DOMContentLoaded', () =>document.body.append(input))
