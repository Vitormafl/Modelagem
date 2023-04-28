#include "poligono.h"

Poligono::Poligono(){};

Poligono::Poligono(Ponto p1)
{
    this->qnt_pontos = 1;
    this->vetor_de_pontos.push_back(p1);
};

void Poligono::inserirPonto(Ponto p1){
    this->vetor_de_pontos.push_back(p1);
    this->qnt_pontos += 1;
};

double Poligono::areaPoligono(){
    vector<Vetor> v;
    for (int i = 0; i < this->qnt_pontos; i++){
        v.push_back(Vetor(this->vetor_de_pontos[i].x,this->vetor_de_pontos[i].y));
    };
};