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
    return (a.x *b.x) + (a.y*b.y);
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