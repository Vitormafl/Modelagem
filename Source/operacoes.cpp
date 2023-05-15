#include "operacoes.h"

bool pontoEmTriangulo(Triangulo t, Ponto p){
    double lambda1, lambda2, lambda3;

    double determinante = (t.p1.x * t.p2.y + t.p2.x * t.p3.y + t.p3.x * t.p1.y) - (t.p1.x * t.p3.y + t.p3.x * t.p2.y + t.p2.x * t.p1.y);

    lambda1 = (((p.x * t.p2.y + t.p2.x * t.p3.y + t.p3.x * p.y) - (p.x * t.p3.y + t.p3.x * t.p2.y + t.p2.x * p.y))/determinante);
    lambda2 = (((t.p1.x * p.y + p.x * t.p3.y + t.p3.x * t.p1.y) - (t.p1.x * t.p3.y + t.p3.x * p.y + p.x * t.p1.y))/determinante);
    lambda3 = (((t.p1.x * t.p2.y + t.p2.x * p.y + p.x * t.p1.y) - (t.p1.x * p.y + p.x * t.p2.y + t.p2.x * t.p1.y))/determinante);

    if (lambda1 < 0  || lambda2 < 0  || lambda3 < 0 )
        return false;

    return true;
};

bool pontoEmPoligonoTiro(Poligono P, Ponto p){

    int qnt_interseções = 0;
    Aresta a, b;

    //usando segmento de reta "infinito" no sentido do eixo x
    Ponto infinito = Ponto(p.x + 999999999,p.y);
    a = Aresta(p, infinito);

    for (int i = 0; i < P.qnt_pontos; i++){
        if (i == P.qnt_pontos - 1){
            if (P.vetor_de_pontos[i].y > P.vetor_de_pontos[0].y ){
                b = Aresta(P.vetor_de_pontos[0], P.vetor_de_pontos[i]);
            }
            else{
                b = Aresta(P.vetor_de_pontos[i], P.vetor_de_pontos[0]);
            }
                
            if (intersecçãoSegmentos(a,b) == true){
                qnt_interseções += 1;
            }
        }
        else {
            if (P.vetor_de_pontos[i].y > P.vetor_de_pontos[i+1].y){
                b = Aresta(P.vetor_de_pontos[i+1], P.vetor_de_pontos[i]);
            }
            else{
                b = Aresta(P.vetor_de_pontos[i], P.vetor_de_pontos[i+1]);
            }

            if (intersecçãoSegmentos(a,b) == true){
                qnt_interseções += 1;
            };
        }
    };

    if (qnt_interseções%2 == 0)
        return 0;
    
    return 1;

};

bool pontoEmPoligonoRotação(Poligono p, Ponto p1){
    float soma_angulos = 0;
    Vetor a,b;

    for (int i = 0; i < p.qnt_pontos; i++){
        if (i == p.qnt_pontos - 1){
            a = Vetor(p.vetor_de_pontos[i].x - p1.x, p.vetor_de_pontos[i].y - p1.y);
            b = Vetor(p.vetor_de_pontos[0].x - p1.x, p.vetor_de_pontos[0].y - p1.y);
        }
        else {
            a = Vetor(p.vetor_de_pontos[i].x - p1.x, p.vetor_de_pontos[i].y - p1.y);
            b = Vetor(p.vetor_de_pontos[i+1].x - p1.x, p.vetor_de_pontos[i+1].y - p1.y);
        }

        soma_angulos += pseudoAngulo(a,b);
    };

    if (soma_angulos == -8 || soma_angulos == 8)
        return 1;
    return 0;

};

//Poligono Graham(Poligono P){
//    vector<Ponto> feixo_convexo;
//    Poligono feixo = Poligono();
//    Ponto anterior, atual, proximo;
//
//    P.orderPoligono();
//
//    feixo_convexo.push_back(P.vetor_de_pontos[0]);
//    //feixo_convexo.push_back(P.vetor_de_pontos[1]);
//    //feixo_convexo.push_back(P.vetor_de_pontos[2]);
//
//
//    for(int i=2; i < P.qnt_pontos;){
//        // a ultima verificação tu tem que mudar os indices pra poder usar o p[0]
//        anterior = feixo_convexo[feixo_convexo.size()-1];
//        atual    = P.vetor_de_pontos[i%P.qnt_pontos];
//        proximo  = P.vetor_de_pontos[(i+1)%P.qnt_pontos];    
//
//        Vetor a = Vetor(anterior, atual);
//        Vetor b = Vetor(atual, proximo);
//
//        if(isCounterClockWise(a,b)){
//            feixo_convexo.push_back(atual);
//            i++;
//        }
//        else if(feixo_convexo.size() > 1){
//            feixo_convexo.pop_back();
//        }
//        else{
//            i++;
//        }
//    }
//
//    for (Ponto ponto : feixo_convexo){
//        feixo.inserirPonto(ponto);
//    }
//
//    return feixo;
//};

Poligono Graham(Poligono P){
    vector<Ponto> feixo_convexo;
    Poligono feixo = Poligono();
    Ponto anterior, atual, proximo;
    Vetor a,b;
    int pontos_testados = 1;

    P.orderPoligono();

    feixo_convexo.push_back(P.vetor_de_pontos[0]);

    while (pontos_testados < P.qnt_pontos){
        a = Vetor(feixo_convexo[feixo_convexo.size()-1], P.vetor_de_pontos[pontos_testados]);
        b = Vetor(feixo_convexo[feixo_convexo.size()-1], P.vetor_de_pontos[pontos_testados+1]);

        if (isCounterClockWise(a,b)){
            feixo_convexo.push_back(P.vetor_de_pontos[pontos_testados]);
            pontos_testados += 1;
        }
        else {
            pontos_testados += 1;
        }
    }

    for (int i = 0; i < feixo_convexo.size(); i++){
        feixo.inserirPonto(feixo_convexo[i]);
    }

    return feixo;    
};

