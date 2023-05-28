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

vector<Ponto> merge(vector<Ponto> feixo_esquerdo, vector<Ponto> feixo_direito){

    int e = feixo_esquerdo.size();
    int d = feixo_direito.size();
    int i = 0, j = 0;


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

    int left, int right;

    //A tangente inferior é obtida através desse algoritmo
    vector<int> inferior = obterTangenteInferior(esquerdo,direito);
    
    vector<int> superior = obterTangenteSuperior(esquerdo, direito);

    //Pegar esses quatro pontos e ligar os feixos esquerdos com o direito
    //fazer tal algoritmo...

    //Adiciona a parte do polígono direito
    //Pega o ponto do polígono direito da tangente inferior
    //Vai até o começo da tangente superior adicionando todos pontos entre eles
    for(int i = inferior[1]; i != superior[0]; i = (i + 1) % direito.size()){
        feixo.push_back(direito[i]);
    }
    feixo.push_back(direito[superior[0]]);

    //Adiciona a parte do polígono esquerdo
    for(int i = superior[1]; i != inferior[0]; i = (i + 1) % esquerdo.size()){
        feixo.push_back(esquerdo[i]);
    }
    feixo.push_back(direito[inferior[0]]);

    return feixo;
}

vector<int> obterTangenteInferior(vector<Ponto> esquerdo, vector<Ponto> direito){

    //Lógica: 
    //pegar o índice do ponto mais a direita do lado esquerdo
    left = 0;
    for(int i = 0; i < esquerdo.size(); i++)
        if(esquerdo[i].x > esquerdo[left].x)
            left = i;
    
    //pegar o índice do ponto mais a esquerda do lado direito    
    right = 0;
    for(int i = 0; i < direito.size(); i++)
        if(direito[i].x < direito[right].x)
            right = i;

    vector<int> tangente;

    Triangulo trianguloE, trianguloD;
    bool orientacao_esquerda, orientacao_direita;
    int next_left, next_right;
    
    //Consegue o ponto counterclockwise antecessor ao esquerdo
    //O modulo faz isso ser uma operação circular, ou seja
    //Se fosse 0 => (0 + n - 1) % n = n-1, ultimo elemento
    next_left =  (left+esquerdo.size()-1)%esquerdo.size(); //Anterior n-1
    next_right = (right + 1) % direito.size();             //Proximo  n+1

    trianguloE = Triangulo(esquerdo[left], esquerdo[next_left], direito[right]);
    trianguloD = Triangulo(direito[right], direito[next_right], esquerdo[left]);

    orientacao_esquerda = ccwTriangulo(trianguloE);
    orientacao_direita  = ccwTriangulo(trianguloD);

    //Enquanto o não (esquerdo ser clowise e direito ser counterclockwise)
    while(!(!orientacao_esquerda && orientacao_direita)){

        //Desce no polígono direito => adiciona
        if(!orientacao_esquerda && !orientacao_direita){
            right = (right + 1) % direito.size(); 
        }
        //Desce no polígono esquerdo => subtrai
        else if(orientacao_esquerda && orientacao_direita){
            left = (left - 1 + esquerdo.size()) % esquerdo.size();
        }

        next_left =  (left+esquerdo.size()-1)%esquerdo.size(); //Anterior n-1
        next_right = (right + 1) % direito.size();             //Proximo  n+1

        trianguloE = Triangulo(esquerdo[left], esquerdo[next_left], direito[right]);
        trianguloD = Triangulo(direito[right], direito[next_right], esquerdo[left]);

        orientacao_esquerda = ccwTriangulo(trianguloE);
        orientacao_direita  = ccwTriangulo(trianguloD);
    }
    
    tangente.push_back(left);
    tangente.push_back(right);

    //Tangente inferior => obtida, ligar esquerdo[left] com direito[right]
    return tangente;
}