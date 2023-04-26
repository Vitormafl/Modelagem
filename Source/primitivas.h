#ifndef PRIMITIVAS_H
#define PRIMITIVAS_H

#include "vetor.h"

Vetor somaVetorial(Vetor a, Vetor b);
Vetor multEscalar(float lambda, Vetor a);
double prodEscalar(Vetor a, Vetor b);
double norma(Vetor a);
double prodVetorial(Vetor a, Vetor b);
bool isCounterClockWise(Vetor a, Vetor b); // retorna verdadeiro caso b esteja a esquerda de a

double distância(Vetor a, Vetor b);
double angulo(Vetor a, Vetor b);

#endif