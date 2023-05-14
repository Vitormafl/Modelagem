#ifndef PONTO_H 
#define PONTO_H

#include <math.h>

class Ponto
{
    public: 

        float x;
        float y;

        Ponto();

        Ponto(float x, float y);
};

struct pontoAngulo{
    Ponto p;
    double a;
};

#endif