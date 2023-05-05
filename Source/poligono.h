#ifndef POLIGONO_H
#define POLIGONO_H

#include "ponto.h"
#include "triangulo.h"
#include "primitivas.h"
#include <vector>
#include <iostream>

using namespace std;
class Poligono
{
    public:
        int qnt_pontos;
        vector<Ponto> vetor_de_pontos;
        bool isCounterClockWise;
        bool isConvex;
        
        Poligono();
        Poligono(Ponto p1);

        void inserirPonto(Ponto p);
        void setPoligono();
        double areaPoligono();
};


#endif