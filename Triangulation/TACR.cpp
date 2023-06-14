#include "TACR.h"

int closestPointDiagonal(Triangulo t, vector<Ponto> p){
    int closest = 0;
    double determinante = (t.p1.x * t.p2.y + t.p2.x * t.p3.y + t.p3.x * t.p1.y) - (t.p1.x * t.p3.y + t.p3.x * t.p2.y + t.p2.x * t.p1.y);
    double lambdaAtual = (((p[0].x * t.p2.y + t.p2.x * t.p3.y + t.p3.x * p[0].y) - (p[0].x * t.p3.y + t.p3.x * t.p2.y + t.p2.x * p[0].y))/determinante);
    double lambdaProximo;

    for (int i = 1; i < p.size(); i++){
        lambdaProximo = (((p[i].x * t.p2.y + t.p2.x * t.p3.y + t.p3.x * p[i].y) - (p[i].x * t.p3.y + t.p3.x * t.p2.y + t.p2.x * p[i].y))/determinante);

        if (lambdaProximo > lambdaAtual){
            closest = i;
            lambdaAtual = lambdaProximo;
        }
    }

    return closest;
};

vector<Triangulo> Diagonals(vector<Ponto> feixo_convexo){
    // variáveis necesárias para o algoritmo
    vector<Triangulo> triangulação, recursive1, recursive2;
    vector<Ponto> pontos_teste = feixo_convexo, pontos_internos, pontos1, pontos2;
    int menor_x = 0, closest;

    //caso recursivo onde todos os triangulos já foram incluidos retorna vetor nulo
    if(pontos_teste.size() < 3)
        return triangulação;

    //localizar o indice do ponto de menor x
    for (int i = 1; i < feixo_convexo.size(); i++){
        if (feixo_convexo[i].x < feixo_convexo[menor_x].x)
            menor_x = i;
    }

    // criar o triangulo com o ponto anterior e posterior do menor x
    Triangulo t = Triangulo(feixo_convexo[menor_x], feixo_convexo[(menor_x+1)%feixo_convexo.size()], feixo_convexo[(menor_x - 1 + feixo_convexo.size())%feixo_convexo.size()]);

    // verificar se os pontos do poligono estão nesse feixo
    for (int i = 0; i < pontos_teste.size(); i++){
        if (pontoEmTriangulo(t,pontos_teste[i])){
            pontos_internos.push_back(pontos_teste[i]);
        }
    }

    // CASO 1, onde não há pontos internos na triangulação selecionada
    // excluimos o ponto testado, no caso o de indice menor_x
    // adicionamos o triangulo t ao vetor da triangulação
    // rodamos o algoritmo recursivamente para os pontos restantes

    if (pontos_internos.size() == 0){
        feixo_convexo.erase(feixo_convexo.begin() + menor_x);
        triangulação.push_back(t);

        recursive1 = Diagonals(feixo_convexo);
        
        for (int i = 0; i < recursive1.size(); i++){
            triangulação.push_back(recursive1[i]);
        } 
    }

    // CASO 2, existem pontos internos ao triangulo,
    // precisamos calcular o mais próximo do ponto de índice menor_x
    // agora vamos divir os pontos de em dois vetores
    // vetor 1 = menor_x, meno_x + 1, ..., closest
    // vetor 2 = menor_x, closest, closest + 1,...
    // rodamos o algortimo recursivamente para esses dois vetores 
    // adicionamos as triangulações resultantes na triangulação do contexto atual
    
    else {
        closest = closestPointDiagonal(t, pontos_internos);

        for (int i = menor_x; i != closest; i = (i+1)%feixo_convexo.size()){
            pontos1.push_back(feixo_convexo[i]);
        }
        pontos1.push_back(feixo_convexo[closest]);

        pontos2.push_back(feixo_convexo[menor_x]);
        for (int i = closest; i != menor_x; i = (i+1)%feixo_convexo.size()){
            pontos2.push_back(feixo_convexo[i]);
        }

        recursive1 = Diagonals(pontos1);
        recursive2 = Diagonals(pontos2);

        for (int i = 0; i < recursive1.size(); i++){
            triangulação.push_back(recursive1[i]);
        }         

        for (int i = 0; i < recursive2.size(); i++){
            triangulação.push_back(recursive2[i]);
        } 
    }

    return triangulação;
};
