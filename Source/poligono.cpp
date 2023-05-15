#include "poligono.h"

Poligono::Poligono(){
    this->qnt_pontos = 0;    
};

Poligono::Poligono(Ponto p1)
{
    this->qnt_pontos = 1;
    this->vetor_de_pontos.push_back(p1);
}; 

void Poligono::orderPoligono(){
    Ponto medio = Ponto(0,0);
    Ponto ponto_volta;
    vector<pontoAngulo> vetor_ponto_angulo;
    vector<Ponto> vp;
    pontoAngulo pa;

    int indice = 0;
    double y_min;

    for (int i = 0; i < this->qnt_pontos; i++){
        medio = Ponto(medio.x + (this->vetor_de_pontos[i].x/this->qnt_pontos) , medio.y + (this->vetor_de_pontos[i].y/this->qnt_pontos));
    }

    for (int i = 0; i < this->qnt_pontos; i++){
        Vetor v(this->vetor_de_pontos[i].x - medio.x, this->vetor_de_pontos[i].y - medio.y);
        pa.p = Ponto(this->vetor_de_pontos[i].x - medio.x, this->vetor_de_pontos[i].y - medio.y);
        pa.a = anguloBase(v);
        vetor_ponto_angulo.push_back(pa);
    }    

    quickSort(vetor_ponto_angulo, 0, this->qnt_pontos-1);

    y_min = vetor_ponto_angulo[0].p.y;

    for (int i = 1; i < this->qnt_pontos; i++){
        if (vetor_ponto_angulo[i].p.y < y_min){
            y_min = vetor_ponto_angulo[i].p.y;
            indice = i;
        }
    } 

    for (int i = 0; i < this->qnt_pontos; i++){
        
        if (indice < this->qnt_pontos){
            ponto_volta = Ponto(vetor_ponto_angulo[indice].p.x + medio.x, vetor_ponto_angulo[indice].p.y + medio.y);
            vp.push_back(ponto_volta);
        }
        else{
            indice -= this->qnt_pontos;
            ponto_volta = Ponto(vetor_ponto_angulo[indice].p.x + medio.x, vetor_ponto_angulo[indice].p.y + medio.y);
            vp.push_back(ponto_volta);
            indice += this->qnt_pontos;
        }
        indice += 1;
    }

    this->vetor_de_pontos = vp;
};

void Poligono::inserirPonto(Ponto p1){
    this->vetor_de_pontos.push_back(p1);
    this->qnt_pontos += 1;

    if (this->qnt_pontos > 2){
        this->setPoligono();
    };
};

double Poligono::areaPoligono(){
    Triangulo t;
    double area = 0;
    int isCCW = 0;

    for (int i = 0; i < this->qnt_pontos - 2; i++){
        t = Triangulo(this->vetor_de_pontos[0], this->vetor_de_pontos[i+1], this->vetor_de_pontos[i+2]);
        area += areaTriangulo(t);
    }

    for (int j = 0; j < this->qnt_pontos; j++){

        if (j == this->qnt_pontos - 2){
            t = Triangulo(this->vetor_de_pontos[j], this->vetor_de_pontos[j+1], this->vetor_de_pontos[0]);

            if (ccwTriangulo(t) == true){
                isCCW += 1;
            };
        }

        else if (j == this->qnt_pontos - 1){
            t = Triangulo(this->vetor_de_pontos[j], this->vetor_de_pontos[0], this->vetor_de_pontos[1]);

            if (ccwTriangulo(t) == true){
                isCCW += 1;
            };
        }

        else{
            t = Triangulo(this->vetor_de_pontos[j], this->vetor_de_pontos[j+1], this->vetor_de_pontos[j+2]);

            if (ccwTriangulo(t) == true){
                isCCW += 1;
            };
        };
    };

    if (isCCW == this->qnt_pontos){
        this->isCounterClockWise = true;
        this->isConvex = true;
        return area;
    };

    if (isCCW == 0){
        this->isCounterClockWise = false;
        this->isConvex = true;
        return (-area);
    };

    this->isConvex = false;
    return 0;
};

void Poligono::setPoligono(){
    int isCCW = 0;
    Triangulo t;

    for (int j = 0; j < this->qnt_pontos; j++){

        if (j == this->qnt_pontos - 2){
            t = Triangulo(this->vetor_de_pontos[j], this->vetor_de_pontos[j+1], this->vetor_de_pontos[0]);

            if (ccwTriangulo(t) == true){
                isCCW += 1;
            };
        }

        else if (j == this->qnt_pontos - 1){
            t = Triangulo(this->vetor_de_pontos[j], this->vetor_de_pontos[0], this->vetor_de_pontos[1]);

            if (ccwTriangulo(t) == true){
                isCCW += 1;
            };
        }

        else{
            t = Triangulo(this->vetor_de_pontos[j], this->vetor_de_pontos[j+1], this->vetor_de_pontos[j+2]);

            if (ccwTriangulo(t) == true){
                isCCW += 1;
            };
        };
    };

    this->isConvex = false;

    if (isCCW == this->qnt_pontos){
        this->isCounterClockWise = true;
        this->isConvex = true;
    };

    if (isCCW == 0){
        this->isCounterClockWise = false;
        this->isConvex = true;
    };
};