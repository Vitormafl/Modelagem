#include <iostream>
#include "Source/aresta.h"

using namespace std;

int main() {

    Ponto p1 = Ponto(1.467 , 1.2);
    Ponto p2 = Ponto(2.43, 4.873);

    Aresta a1 = Aresta(p1, p2);

    cout << a1.p2.x << endl; 

    return 0;
}