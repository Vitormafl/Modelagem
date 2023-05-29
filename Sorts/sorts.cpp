#include "sorts.h"

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


void trocar(Ponto& a, Ponto& b) {
    Ponto temp = a;
    a = b;
    b = temp;
}

int particionar(vector<Ponto>& pontos, int low, int high) {
    double pivot = pontos[high].x;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (pontos[j].x < pivot) {
            i++;
            trocar(pontos[i], pontos[j]);
        }
    }

    trocar(pontos[i + 1], pontos[high]);
    return (i + 1);
}

void quicksort(vector<Ponto>& pontos, int low, int high) {
    if (low < high) {
        int pi = particionar(pontos, low, high);

        quicksort(pontos, low, pi - 1);
        quicksort(pontos, pi + 1, high);
    }
}
