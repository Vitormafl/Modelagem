#include "vetor.h"
#include "primitivas.h"

Vetor::Vetor(){};

Vetor::Vetor(double x, double y){
    this->x = x;
    this->y = y;
};

Vetor::Vetor(Ponto origem, Ponto destino){
    this->x = destino.x - origem.x;
    this->y = destino.y - origem.y;
}
