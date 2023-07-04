#include <iostream>
#include <fstream>
#include "Source/aresta.h"
#include "Source/primitivas.h"
#include "Source/poligono.h"
#include "Source/operacoes.h"
#include "Triangulation/TACR.h"
#include "Visualization/window.h"

using namespace std;

// PARA RODAR ESSE PROGRAMA, BASTA TER O COMPILADOR G++ INSTALADO
// E RODAR O COMANDO "make" NO TERMINAL E EM SEGUIDA "./run"


bool pontosValidos(vector<Ponto> pontos, vector<Ponto> validos){

    bool valido = validos.size() == pontos.size();

    for(Ponto ponto_valido : validos){

        bool incluso = false;
        for(Ponto ponto : pontos){
            if(mesmoPonto(ponto, ponto_valido)){
                incluso = true;
            }
        }

        valido = valido && incluso;
    }

    return valido;
}

vector<vector<Ponto>> leOBJ(const string &nomearq) {

  vector<vector<Ponto>> listaObjs;

  ifstream file(nomearq);
  string linha;

  if (!file.is_open()) {
    cout << "Erro ao abrir o arquivo " << nomearq << endl;
    return listaObjs;
  }

  // int i = 0;
  vector<Ponto> objatual;

  while (file) {

    getline(file, linha);

    // novo objeto encontrado
    if (linha.substr(0, 2) == "o ") {

      // se o atual eh maior que 0... salvar!
      if (objatual.size() > 0) {
        listaObjs.push_back(objatual);
        objatual.clear(); // limpo para a proxima iteracao
      }
    }

    if (linha.substr(0, 2) == "v ") {

      Ponto p;
      double aux;

      sscanf(linha.c_str(), "v %f %f %f", &p.x, &aux, &p.y);

      objatual.push_back(p);
    }
  }

  // se nao ta vazio
  if (objatual.size() > 0) {
    listaObjs.push_back(objatual);
  }

  return listaObjs;
}

vector<Ponto> lePLY(const string &nomearq) {

  vector<Ponto> listaPontos;

  ifstream file(nomearq);
  string linha;
  int quantVerts = 0;

  if (!file.is_open()) {
    cout << "Erro ao abrir o arquivo " << nomearq << endl;
    return listaPontos;
  }

  while (getline(file, linha)) {
    if (linha.find("element vertex") != std::string::npos) {
      sscanf(linha.c_str(), "element vertex %d", &quantVerts);
    } else if (linha.find("end_header") != std::string::npos) {
      break;
    }
  }

  for (int i = 0; i < quantVerts; ++i) {
    getline(file, linha);
    Ponto ponto;
    double aux; // apenas para pegar o zero
    sscanf(linha.c_str(), "%f %f %f", &(ponto.x), &aux, &(ponto.y));
    listaPontos.push_back(ponto);
  }

  return listaPontos;
}

void escreverPontosEmArquivo(const std::vector<vector<Ponto>>& lista, const std::string& nomeArquivo) {
  std::ofstream arquivo(nomeArquivo);
  
  if (arquivo.is_open()) {
    for(vector<Ponto> pontos : lista){
      arquivo << "Novo Feixo" << std::endl;
      for (const auto& ponto : pontos) {
          arquivo << ponto.x << " " << ponto.y << std::endl;
      }
    }
      arquivo.close();
      std::cout << "Pontos gravados no arquivo " << nomeArquivo << std::endl;
  } else {
      std::cerr << "Não foi possível abrir o arquivo " << nomeArquivo << " para escrita" << std::endl;
  }
}

void run_merge(){
  vector<vector<Ponto>> listalistaPontos = leOBJ("Objects/partesconvexas.obj");

  vector<vector<Ponto>> organizar2;

  for(vector<Ponto> pontos : listalistaPontos){

    Poligono p = Poligono(pontos);

    p.orderPoligono();
    
    organizar2.push_back(feixoConvexo(p));

  }

  escreverPontosEmArquivo(organizar2, "Results/merge.txt");
}

int main(int argc, char* argv[]) {

  vector<vector<Ponto>> listalistaPontos = leOBJ("Objects/partesconvexas.obj");

  vector<vector<Ponto>> organizar2;

  vector<vector<Triangulo>> vvt;

  vector<Triangulo> vt;

  // juntar os feixos
  Ponto u24 = Ponto(listalistaPontos[2][0].x, listalistaPontos[2][17].y);
  Ponto u01 = Ponto((1.50089 + 1.38887)/2, (0.349084-0.909608)/2);
  Ponto u10 = Ponto(1.71252,2.29207);
  Ponto u13 = Ponto(1.40607,1.79777);
  Ponto u31 = Ponto(1.36515,1.30766);
  Ponto u313 = Ponto((1.32422 + 1.24237)/2, (0.817538-0.162697)/2);
  Ponto u73 = Ponto(0.915531,0.974361);
  Ponto u37 = Ponto(0.890564,0.775897);
  Ponto u53 = Ponto(1.14172,1.75864);
  Ponto u35 = Ponto(1.04393,1.54923);
  Ponto u63 = Ponto(0.979728,1.26179);
  Ponto u36 = Ponto(0.915531,0.974361);
  

  listalistaPontos[0].push_back(listalistaPontos[2][20]);
  listalistaPontos[0].push_back(listalistaPontos[2][21]);
  listalistaPontos[1].push_back(u01);
  listalistaPontos[1].push_back(u10);
  listalistaPontos[2].push_back(u24);
  listalistaPontos[3].push_back(u13);
  listalistaPontos[3].push_back(u31);
  listalistaPontos[3].push_back(u313);
  listalistaPontos[4].push_back(u24);
  listalistaPontos[4].push_back(listalistaPontos[2][14]);
  listalistaPontos[5].push_back(u53);
  listalistaPontos[5].push_back(u35);
  listalistaPontos[6].push_back(u63);
  listalistaPontos[6].push_back(u36);
  listalistaPontos[7].push_back(u73);
  listalistaPontos[7].push_back(u37);

  for(vector<Ponto> pontos : listalistaPontos){

    Poligono p = Poligono(pontos);

    p.orderPoligono();
    
    organizar2.push_back(improveHull(feixoConvexo(p),1));

  }

  escreverPontosEmArquivo(organizar2, "Results/merge.txt");

  for (int i = 0; i < organizar2.size(); i++){
    vt = Diagonals(organizar2[i]);
    vvt.push_back(vt);
  }

    // Initialize SDL2
  runWindow(organizar2, vvt);

    return 0;
}