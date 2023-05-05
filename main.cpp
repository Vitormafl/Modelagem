#include <iostream>
#include "Source/aresta.h"
#include "Source/primitivas.h"
#include "Source/poligono.h"

using namespace std;

int main() {

    Ponto p1(-3, 0);
    Ponto p2( 3, 0);
    Ponto p3(3,6);
    Ponto p4(-3,6);
    Ponto p5( 0, 10);


    //Poligono p(p1);
    //p.inserirPonto(p4);
    //p.inserirPonto(p5);
    //p.inserirPonto(p3);
    //p.inserirPonto(p2);

    Vetor v1(-1,0);
    Vetor v2(0,1);

    cout << pseudoAngulo(v2,v1) << endl; 

    return 0;
}