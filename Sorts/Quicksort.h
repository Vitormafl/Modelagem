#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <vector>
#include "../Source/ponto.h"

using namespace std;

void swap(pontoAngulo& a, pontoAngulo& b);
int partition(vector<pontoAngulo>& arr, int low, int high);
void quickSort(vector<pontoAngulo>& arr, int low, int high);

#endif