#ifndef POLIGONO_H
#define POLIGONO_H

#include "ponto.h"
#include <vector>

using namespace std;
class Poligono
{
    public:
        int qnt_pontos;
        
        vector<Ponto> vetor_de_pontos;
        
        Poligono();

        Poligono(Ponto p1);

        void inserirPonto(Ponto p);

        double areaPoligono();
};


#endif