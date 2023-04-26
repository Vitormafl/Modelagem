#include <iostream>
#include "Source/aresta.h"
#include "Source/primitivas.h"

using namespace std;

int main() {

    Ponto p1 = Ponto(2.0 , 1.2);
    Ponto p2 = Ponto(2.43, 4.873);

    Aresta a1 = Aresta(p1, p2);

    Vetor v1(12.0 , 2.0);
    Vetor v2(8, -3);

    Vetor v3 = multEscalar(5.0, v2); 

    cout << isCounterClockWise(v2, v1) << endl; 

    return 0;
}