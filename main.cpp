#include <iostream>
#include "Source/aresta.h"
#include "Source/primitivas.h"
#include "Source/poligono.h"

using namespace std;

int main() {

    Ponto p1(-3, 0);
    Ponto p2( 3, 0);
    Ponto p5( 3, 6);

    Ponto p3(-1,-5);
    Ponto p4(2,2);

    Aresta a1(p1, p2);
    Aresta a2(p3, p4);
    
    Vetor v1(0.3, -8);
    Vetor v2(-3 , -4);
   
    Triangulo t1(p1,p2,p5);

    Poligono p(p2);
    p.inserirPonto(p3);

    cout << p.vetor_de_pontos[1].y << endl; 

    return 0;
}