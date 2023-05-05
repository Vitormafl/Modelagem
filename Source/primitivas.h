#ifndef PRIMITIVAS_H
#define PRIMITIVAS_H

#define PI 3.14159265358979323846

#include "vetor.h"
#include "aresta.h"
#include "triangulo.h"

Vetor somaVetorial(Vetor a, Vetor b);
Vetor multEscalar(float lambda, Vetor a);
double prodEscalar(Vetor a, Vetor b);
double norma(Vetor a);
double prodVetorial(Vetor a, Vetor b);
bool isCounterClockWise(Vetor a, Vetor b); // retorna verdadeiro caso b esteja a esquerda de a

double distância(Vetor a, Vetor b);
double angulo(Vetor a, Vetor b);
double anguloBase(Vetor a);
double pseudoAngulo(Vetor a);
double pseudoAngulo(Vetor a, Vetor b);

bool intersecçãoSegmentos(Aresta a, Aresta b);
bool ccwTriangulo(Triangulo a);
double areaTriangulo(Triangulo a);


#endif