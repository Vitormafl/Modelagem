#include <iostream>
#include "Source/aresta.h"
#include "Source/primitivas.h"
#include "Source/poligono.h"
#include "Source/operacoes.h"

using namespace std;

// PARA RODAR ESSE PROGRAMA, BASTA TER O COMPILADOR G++ INSTALADO
// E RODAR O COMANDO "make" NO TERMINAL E EM SEGUIDA "./run"

int main() {

    Ponto p1(-3, 0);
    Ponto p2( 3, 0);
    Ponto p3(3,6);
    Ponto p4(-3,6);
    Ponto p5( 0, -4);
    Ponto p6(4,3);

    Poligono p(p5);
    p.inserirPonto(p1);
    p.inserirPonto(p4);
    p.inserirPonto(p2);
    p.inserirPonto(p3);
    p.inserirPonto(p6);

    cout << "vetor de pontos inicial: "<< endl;

    for (int i = 0; i < p.qnt_pontos; i++){
        cout << "Ponto: (" << p.vetor_de_pontos[i].x << ", " << p.vetor_de_pontos[i].y << ") " << endl; 
    };

    p.orderPoligono();

    cout << "vetor de pontos final: "<< endl;

    for (int i = 0; i < p.qnt_pontos; i++){
        cout << "Ponto: (" << p.vetor_de_pontos[i].x << ", " << p.vetor_de_pontos[i].y << ") " << endl; 
    };

    return 0;
}