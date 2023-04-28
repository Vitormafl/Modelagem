#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "ponto.h"

class Triangulo
{
    public:
        Ponto p1, p2, p3;

        Triangulo();

        Triangulo(Ponto p1, Ponto p2, Ponto p3);
};

#endif