#include "primitivas.h" 

Vetor somaVetorial(Vetor a, Vetor b){
    Vetor c(a.x + b.x, a.y + b.y);
    return c;
};

Vetor multEscalar(float lambda, Vetor a){
    Vetor b(lambda * a.x, lambda * a.y);
    return b;
};

double prodEscalar(Vetor a, Vetor b){
    return (a.x * b.x) + (a.y * b.y);
};

double norma(Vetor a){
    return sqrt(pow(a.x,2)+ pow(a.y, 2));
};

double prodVetorial(Vetor a, Vetor b){
    return (a.x * b.y) - (b.x * a.y);
};

bool isCounterClockWise(Vetor a, Vetor b){
    double k = prodVetorial(a, b);
    if ( k > 0){
        return true;
    }
    else 
        return false;
};

double distância(Vetor a, Vetor b){
    Vetor c(a.x - b.x, a.y - b.y);
    return norma(c);
};

double angulo(Vetor a, Vetor b){
    double theta = acos(prodEscalar(a,b)/(norma(a)*norma(b)));
    return theta;
};

double anguloBase(Vetor a){
    Vetor b(1,0);
    double theta = acos(prodEscalar(a,b)/(norma(a)*norma(b)));
    if (a.y >= 0){
        return theta;        
    }
    else
        theta = 2 * PI - theta;
    return theta;
};

double pseudoAngulo(Vetor a){
    if (a.y >= 0){
        if (a.x >= 0){
            if (a.x >= a.y){
                return a.y/a.x;
            }
            return 2 - a.x/a.y;
        }
        if (-a.x <= a.y){
            return 2 + (-a.x/a.y);
        }
        return 4 - (a.y/(-a.x));
    }
    if (a.x < 0){
        if (- a.x >= -a.y){
            return 4 + (-a.y/-a.x);
        }
        return 6 - (-a.x/-a.y);
    }
    if (a.x <= - a.y){
        return 6 + a.x/(-a.y);
    }
    return 8 - (-a.y)/a.x;
};

double pseudoAngulo(Vetor a, Vetor b){
    double va = pseudoAngulo(a);
    double vb = pseudoAngulo(b);

    if (va > vb){
        return (8 - va + vb);
    };

    return (vb - va);
};

bool intersecçãoSegmentos(Aresta a, Aresta b){
    //Vetores partindo de a.p1
    Vetor va1(a.p2.x - a.p1.x, a.p2.y - a.p1.y);
    Vetor va2(b.p1.x - a.p1.x, b.p1.y - a.p1.y);
    Vetor va3(b.p2.x - a.p1.x, b.p2.y - a.p1.y);
    //Vetores partindo de b.p1
    Vetor vb1(b.p2.x - b.p1.x, b.p2.y - b.p1.y);
    Vetor vb2(a.p1.x - b.p1.x, a.p1.y - b.p1.y);
    Vetor vb3(a.p2.x - b.p1.x, a.p2.y - b.p1.y);

    double pv1 = prodVetorial(va1, va2);
    double pv2 = prodVetorial(va1, va3);
    double pv3 = prodVetorial(vb1, vb2);
    double pv4 = prodVetorial(vb1, vb3);

    if ((pv1*pv2) < 0 && (pv3*pv4) < 0)
        return true;
    return false;
};

bool ccwTriangulo(Triangulo a){
    Vetor v1(a.p2.x - a.p1.x, a.p2.y - a.p1.y);
    Vetor v2(a.p3.x - a.p1.x, a.p3.y - a.p1.y);

    if (prodVetorial(v1,v2) > 0)
        return true;
    return false;
};

double areaTriangulo(Triangulo a){
    Vetor v1(a.p2.x - a.p1.x, a.p2.y - a.p1.y);
    Vetor v2(a.p3.x - a.p1.x, a.p3.y - a.p1.y);

    return (prodVetorial(v1,v2)/2);
};
 
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

            b = Aresta(P.vetor_de_pontos[i], P.vetor_de_pontos[0]);

            if (intersecçãoSegmentos(a,b) == true){
                qnt_interseções += 1;
            }
        }
        else {

            b = Aresta(P.vetor_de_pontos[i], P.vetor_de_pontos[i+1]);

            if (intersecçãoSegmentos(a,b) == true){
                qnt_interseções += 1;
            };
        }
    };

    if (qnt_interseções%2 == 0)
        return 0;
    
    return 1;

};