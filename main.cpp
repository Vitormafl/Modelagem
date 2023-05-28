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


//Teste 1
int teste1(){
    

    Ponto p1(-3, 0);
    Ponto p2( 3, 0);
    Ponto p3(3,6);
    Ponto p4(-3,6);
    Ponto p5( 1, 2);
    Ponto p6(2,2);
    Ponto p7(0,1);
    Ponto p8( -2, 4);
    Ponto p9(2.5,5);
    Ponto p10(1,5);
    Ponto p11( 0.5,4);

    Poligono p(p1);
    p.inserirPonto(p2);
    p.inserirPonto(p3);
    p.inserirPonto(p4);
    p.inserirPonto(p5);
    p.inserirPonto(p6);
    p.inserirPonto(p7);
    p.inserirPonto(p8);
    p.inserirPonto(p9);
    p.inserirPonto(p10);
    p.inserirPonto(p11);


    //cout << "vetor de pontos inicial: "<< endl;
//
    //for (int i = 0; i < p.qnt_pontos; i++){
    //    cout << "Ponto: (" << p.vetor_de_pontos[i].x << ", " << p.vetor_de_pontos[i].y << ") " << endl; 
    //};

    //cout << "teste 1" << endl;
    Poligono feixo = Graham(p);

    //cout << "feixo convexo: "<< endl;
//
    //for (Ponto ponto : feixo.vetor_de_pontos){
    //    cout << "Ponto: (" << ponto.x << ", " << ponto.y << ") " << endl; 
    //};

    vector<Ponto> pontos_validos = {p1,p2,p3,p4};

    return pontosValidos(feixo.vetor_de_pontos, pontos_validos);
}

int teste2(){
    

    Ponto p1(-3, 0);
    Ponto p2( 3, 0);
    Ponto p3(3,6);
    Ponto p4(-3,6);
    Ponto p5( 0, 2);

    Poligono p(p1);
    p.inserirPonto(p2);
    p.inserirPonto(p3);
    p.inserirPonto(p4);
    p.inserirPonto(p5);

    //cout << "vetor de pontos inicial: "<< endl;
//
    //for (int i = 0; i < p.qnt_pontos; i++){
    //    cout << "Ponto: (" << p.vetor_de_pontos[i].x << ", " << p.vetor_de_pontos[i].y << ") " << endl; 
    //};
//
    //cout << "teste 2" << endl;
    Poligono feixo = Graham(p);
//
    //cout << "feixo convexo: "<< endl;
//
    //for (Ponto ponto : feixo.vetor_de_pontos){
    //    cout << "Ponto: (" << ponto.x << ", " << ponto.y << ") " << endl; 
    //};

    vector<Ponto> pontos_validos = {p1,p2,p3,p4};

    return pontosValidos(feixo.vetor_de_pontos, pontos_validos);
}

int teste3(){
    

    Ponto p1(-2,-5);
    Ponto p2(-1,-3);
    Ponto p3(5,-4);
    Ponto p4(10,-1);
    Ponto p5(15,9);
    Ponto p6(11,8);
    Ponto p7(9,7);
    Ponto p8(8,6);
    Ponto p9(-4,10);
    Ponto p10(-10,3);

    //Os pontos que esperamos que sejam os determinados pelo feixo convexo
    vector<Ponto> pontos_validos = {p1,p3,p4,p5,p9,p10};

    Poligono p(p1);
    p.inserirPonto(p2);
    p.inserirPonto(p3);
    p.inserirPonto(p4);
    p.inserirPonto(p5);
    p.inserirPonto(p6);
    p.inserirPonto(p7);
    p.inserirPonto(p8);
    p.inserirPonto(p9);
    p.inserirPonto(p10);

    //cout << "vetor de pontos inicial: "<< endl;
//
    //for (int i = 0; i < p.qnt_pontos; i++){
    //    cout << "Ponto: (" << p.vetor_de_pontos[i].x << ", " << p.vetor_de_pontos[i].y << ") " << endl; 
    //};
//
    //cout << "teste 3" << endl;
    Poligono feixo = Graham(p);
//
    //cout << "feixo convexo: "<< endl;
//
    //for (Ponto ponto : feixo.vetor_de_pontos){
    //    cout << "Ponto: (" << ponto.x << ", " << ponto.y << ") " << endl; 
    //};

    return pontosValidos(feixo.vetor_de_pontos, pontos_validos);
}

int main() {

    bool resultado1 = teste1();
    bool resultado2 = teste2();
    bool resultado3 = teste3();

    cout << ((resultado1)? "teste 1 válido" : "teste 1 inválido") << endl;
    cout << ((resultado2)? "teste 2 válido" : "teste 2 inválido") << endl;
    cout << ((resultado3)? "teste 3 válido" : "teste 3 inválido") << endl;

    return 0;
}