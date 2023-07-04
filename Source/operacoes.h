#ifndef OPERACOES_H
#define OPERACOES_H

#include "poligono.h"

bool pontoEmTriangulo(Triangulo t, Ponto p);
bool pontoEmPoligonoTiro(Poligono p, Ponto p1);
bool pontoEmPoligonoRotação(Poligono p, Ponto p1);

vector<Ponto> merge( vector<Ponto> feixo_esquerdo, vector<Ponto> feixo_direito);

vector<Ponto> Graham(vector<Ponto> pontos);
vector<Ponto> mergeHull(vector<Ponto>);

vector<Ponto> feixoConvexo(Poligono P);
vector<Ponto> improveHull(vector<Ponto> hull, int depth);

#endif