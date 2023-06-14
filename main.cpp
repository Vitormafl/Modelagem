#include <iostream>
#include <fstream>
#include "Source/aresta.h"
#include "Source/primitivas.h"
#include "Source/poligono.h"
#include "Source/operacoes.h"
#include "SDL2/SDL.h"

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

int main() {

  Ponto p1 = Ponto(-1.0, 0.0);
  Ponto p2 = Ponto(1.0, 0.0);
  Ponto p3 = Ponto(0.0, 1.0);
  Ponto p4 = Ponto(0.0, 0.33333);

  Triangulo t = Triangulo(p1,p2,p3);

  cout << pontoEmTriangulo(t, p4) << endl;
  
  return 0;
}