#ifndef PONTO_H 
#define PONTO_H

#include <math.h>

class Ponto
{
    public: 

        double x;
        double y;

        Ponto();

        Ponto(double x, double y);

};

struct pontoAngulo{
    Ponto p;
    double a;
};

#endif