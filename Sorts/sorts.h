#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include <vector>
#include "../Source/ponto.h"

using namespace std;

void trocar(Ponto& a, Ponto& b);
void swap(pontoAngulo& a, pontoAngulo& b);
int partition(vector<pontoAngulo>& arr, int low, int high);
int particionar(vector<Ponto>& pontos, int low, int high);
void quickSort(vector<pontoAngulo>& arr, int low, int high);
void quicksort(vector<Ponto>& pontos, int low, int high); 

#endif