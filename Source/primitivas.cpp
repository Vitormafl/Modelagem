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

bool mesmoPonto(Ponto p1, Ponto p2){
    if (p1.x == p2.x && p1.y == p2.y)
        return true;
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

    //Operação para extender levemente o final da aresta b a fim de gerar interseção no ponto final
    Vetor vetor_de_correção(b.p2.x - b.p1.x, b.p2.y - b.p1.y);
    vetor_de_correção = multEscalar(0.000001, vetor_de_correção);

    Ponto corrigido = Ponto(b.p2.x + vetor_de_correção.x, b.p2.y + vetor_de_correção.y);
    Aresta c(b.p1, corrigido);

    //Vetores partindo de a.p1
    Vetor va1(a.p2.x - a.p1.x, a.p2.y - a.p1.y);
    Vetor va2(c.p1.x - a.p1.x, c.p1.y - a.p1.y);
    Vetor va3(c.p2.x - a.p1.x, c.p2.y - a.p1.y);
    //Vetores partindo de b.p1
    Vetor vb1(c.p2.x - c.p1.x, c.p2.y - c.p1.y);
    Vetor vb2(a.p1.x - c.p1.x, a.p1.y - c.p1.y);
    Vetor vb3(a.p2.x - c.p1.x, a.p2.y - c.p1.y);

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
