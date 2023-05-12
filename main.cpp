#include <iostream>
#include "Source/aresta.h"
#include "Source/primitivas.h"
#include "Source/poligono.h"
#include "Source/operacoes.h"

using namespace std;

int main() {

    Ponto p1(-3, 0);
    Ponto p2( 3, 0);
    Ponto p3(3,6);
    Ponto p4(-3,6);
    Ponto p5( 0, 10);
    Ponto p6(3,6);

    Ponto p7(0,0);
    Ponto p8(0,5);


    Poligono p(p1);
    p.inserirPonto(p2);
    p.inserirPonto(p3);
    p.inserirPonto(p5);
    p.inserirPonto(p4);

    Aresta a1(p1,p2);
    Aresta a2(p7,p8);

    //Vetor v1(-1,0);
    //Vetor v2(0,1);

    //Triangulo t(p4,p3,p5);

    //pontoEmTriangulo(t, p6);

    cout << intersecçãoSegmentos(a1,a2) << endl; 

    return 0;
}