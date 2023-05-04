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

    //if (this->qnt_pontos > 2){
    //    this->setPoligono();
    //};
};

double Poligono::areaPoligono(){
    Triangulo t;
    double area = 0;
    int isCCW = 0;

    for (int i = 0; i < this->qnt_pontos - 2; i++){
        t = Triangulo(this->vetor_de_pontos[0], this->vetor_de_pontos[i+1], this->vetor_de_pontos[i+2]);
        area += areaTriangulo(t);
    };

    for (int j = 0; j < this->qnt_pontos; j++){
        t = Triangulo(this->vetor_de_pontos[j], this->vetor_de_pontos[j+1], this->vetor_de_pontos[j+2]);

        if (ccwTriangulo(t) == true){
            isCCW += 1;
        };
    };

    if (isCCW == 6){
        this->isCounterClockWise = true;
        this->isConvex = true;
        return area;
    };

    if (isCCW == 0){
        this->isCounterClockWise = false;
        this->isConvex = true;
        return (-area);
    };

    this->isConvex = false;
    return 0;
};

void Poligono::setPoligono(){
    int isCCW = 0;
    Triangulo t;

    for (int j = 0; j < this->qnt_pontos; j++){
        t = Triangulo(this->vetor_de_pontos[j], this->vetor_de_pontos[j+1], this->vetor_de_pontos[j+2]);

        if (ccwTriangulo(t) == true){
            isCCW += 1;
        };
    };

    if (isCCW == 6){
        this->isCounterClockWise= true;
        this->isConvex = true;
    };

    if (isCCW == 0){
        this->isCounterClockWise = false;
        this->isConvex = true;
    };

    this->isConvex = false;
};