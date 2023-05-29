#ifndef POLIGONO_H
#define POLIGONO_H

#include "primitivas.h"
#include <vector>
#include <iostream>
#include "../Sorts/sorts.h"

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
        Poligono(vector<Ponto> vp);

        void orderPoligono();
        void inserirPonto(Ponto p);
        void setPoligono();
        double areaPoligono();
};


#endif