#include <iostream>
#include "Source/aresta.h"
#include "Source/primitivas.h"

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

    Vetor v3 = multEscalar(5.0, v2); 

    cout << areaTriangulo(t1) << endl; 

    return 0;
}