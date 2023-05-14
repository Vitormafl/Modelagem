#include "Quicksort.h"

// Função auxiliar para trocar dois elementos do vetor
void swap(pontoAngulo& a, pontoAngulo& b) {
    pontoAngulo temp = a;
    a = b;
    b = temp;
}

// Função auxiliar para particionar o vetor
int partition(vector<pontoAngulo>& arr, int low, int high) {
    double pivot = arr[high].a;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].a < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Função principal do QuickSort
void quickSort(vector<pontoAngulo>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}