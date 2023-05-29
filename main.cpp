#include <iostream>
#include "Source/aresta.h"
#include "Source/primitivas.h"
#include "Source/poligono.h"
#include "Source/operacoes.h"
#include "SDL2/SDL.h"

using namespace std;

// PARA RODAR ESSE PROGRAMA, BASTA TER O COMPILADOR G++ INSTALADO
// E RODAR O COMANDO "make" NO TERMINAL E EM SEGUIDA "./run"


bool pontosValidos(vector<Ponto> pontos, vector<Ponto> validos){

    bool valido = validos.size() == pontos.size();

    for(Ponto ponto_valido : validos){

        bool incluso = false;
        for(Ponto ponto : pontos){
            if(mesmoPonto(ponto, ponto_valido)){
                incluso = true;
            }
        }

        valido = valido && incluso;
    }

    return valido;
}


int main() {

    vector<Ponto> vp, feixo;
    Ponto p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;

    p1 = Ponto(8,-6);
    p2 = Ponto(15,10);
    p3 = Ponto(3,20);
    p4 = Ponto(-8,20);
    p5 = Ponto(-21,4);
    p6 = Ponto(-9,-6);
    p7 = Ponto(2, 2);
    p8 = Ponto(-2,2);
    p9 = Ponto(-16,-1);
    p10 = Ponto(-4,11);
    p11 = Ponto(1,12);
    p12 = Ponto(7,7);
    p13 = Ponto(0, 0);
    p14 = Ponto(5,-1);
    p15 = Ponto(-7,-1);

    vp.push_back(p1);
    vp.push_back(p2);
    vp.push_back(p3);
    vp.push_back(p4);
    vp.push_back(p5);
    vp.push_back(p6);
    vp.push_back(p7);
    vp.push_back(p8);
    vp.push_back(p9);
    vp.push_back(p10);
    vp.push_back(p11);
    vp.push_back(p12);
    vp.push_back(p13);
    vp.push_back(p14);
    vp.push_back(p15);

    Poligono p = Poligono(vp);
    p.orderPoligono();

    feixo = feixoConvexo(p);

    for(int i = 0; i < feixo.size(); i++){
        cout <<"Ponto " << i+1 << ": " << feixo[i].x << " " << feixo[i].y << endl;
    };

    return 0;
}