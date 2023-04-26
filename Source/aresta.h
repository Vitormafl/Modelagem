#ifndef ARESTA_H
#define ARESTA_H

#include "ponto.h"

class Aresta
{
    public: 

        Ponto p1, p2;

        Aresta();
         
        Aresta(Ponto &p1, Ponto &p2);
};

#endif