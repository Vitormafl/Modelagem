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

vector<Ponto> feixoConvexo(Poligono P){
    P.orderPoligono();

    vector<Ponto> feixo, pontos = P.vetor_de_pontos;
    feixo = mergeHull(pontos);

    return feixo;
};

vector<Ponto> Graham(vector<Ponto> pontos_candidatos){
    vector<Ponto> feixo_convexo;
    Vetor a,b;
    int i = 1;

    feixo_convexo.push_back(pontos_candidatos[0]);

    while (i < pontos_candidatos.size()){

        a = Vetor(feixo_convexo[feixo_convexo.size()-1], pontos_candidatos[i]);
        b = Vetor(feixo_convexo[feixo_convexo.size()-1], pontos_candidatos[(i+1)%pontos_candidatos.size()]);


        if (isCounterClockWise(a,b)){
            feixo_convexo.push_back(pontos_candidatos[i]);
            i += 1;
        }
        else{
            pontos_candidatos.erase(pontos_candidatos.begin() + i);

            if (feixo_convexo.size() > 1){
                feixo_convexo.pop_back();
                i -= 1;
            }
        }
    }

    return feixo_convexo;    
};

vector<Ponto> mergeHull(vector<Ponto> pontos){

    vector<Ponto> feixo, esquerdo, direito, feixo_esquerdo, feixo_direito;
    int n = pontos.size();

    if (n < 6){
        feixo = Graham(pontos);
        return feixo;
    }

    int mid = n / 2;

    for (int i = 0; i < mid; i++) {
        esquerdo.push_back(pontos[i]);
    }
    for (int i = mid; i < n; i++) {
        direito.push_back(pontos[i]);
    }

    feixo_esquerdo = mergeHull(esquerdo);
    feixo_direito = mergeHull(direito);

    feixo = merge(feixo_esquerdo, feixo_direito);
    
    return feixo;
};

vector<Ponto> merge(vector<Ponto> esquerdo, vector<Ponto> direito){

    vector<Ponto> feixo;
    Aresta t_inf, t_sup;
    Triangulo t1, t2;
    bool ot1, ot2;

    int flag_inf = 0, flag_sup = 0;

    int maiorx = esquerdo[0].x, menorx = direito[0].x, i_maiorx = 0, i_menorx = 0;
    int tie, tid, tse, tsd;

    for(int i = 1; i < esquerdo.size(); i++){
        if(esquerdo[i].x > maiorx)
            maiorx = esquerdo[i].x;
            i_maiorx = i;
    }

    for(int i = 1; i < direito.size(); i++){
        if(direito[i].x < menorx)
            menorx = direito[i].x;
            i_menorx = i;
    }

    tie = i_maiorx;
    tse = i_maiorx;
    tid = i_menorx;
    tsd = i_menorx; 

    while (flag_inf != 1){
        t1 = Triangulo(esquerdo[tie],esquerdo[(tie - 1 + esquerdo.size())%esquerdo.size()], direito[tid]);
        t2 = Triangulo(direito[tid],direito[(tid + 1)%direito.size()], esquerdo[tie]);
        ot1 = ccwTriangulo(t1);
        ot2 = ccwTriangulo(t2);

        if (!ot1 && !ot2){
            tid = (tid + 1)%direito.size();
        }
        else if (ot1 && ot2){
            tie = (tie - 1 + esquerdo.size())%esquerdo.size();
        } 
        else if (!ot1 && ot2){
            flag_inf = 1;
        }
    }

    while (flag_inf != 2){
        t1 = Triangulo(esquerdo[tse],esquerdo[(tse + 1)%esquerdo.size()], direito[tsd]);
        t2 = Triangulo(direito[tsd],direito[(tsd - 1 + direito.size())%direito.size()], esquerdo[tse]);
        ot1 = ccwTriangulo(t1);
        ot2 = ccwTriangulo(t2);

        if (!ot1 && !ot2){
            tse = (tse + 1)%esquerdo.size();
        }
        else if (ot1 && ot2){
            tsd = (tsd - 1 + direito.size())%direito.size();
        } 
        else if (ot1 && !ot2){
            flag_inf = 2;
        }
        
    }

    for (int i = tid; i != tsd; i = (i+1)%direito.size()){
        feixo.push_back(direito[i]);
    } 
    feixo.push_back(direito[tsd]);

    for (int i = tse; i != tie; i = (i+1)%esquerdo.size()){
        feixo.push_back(esquerdo[i]);
    } 
    feixo.push_back(esquerdo[tie]);
    
    return feixo;
}