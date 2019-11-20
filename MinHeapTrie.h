#include <iostream>
#include "NoTrie.h"

using namespace std;

void trocar(int* a, int* b)
{
  int aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

void heapify(NoTrie* vet, int i, int n) { // Passamos o inteiro n para que não comparemos elementos com indices maiores que n.
  int l = (2*i) + 1;
  int r = (2*i) + 2;
  int menor = i;
  if (l < n) { // If para que não apliquemos este passo em um nó folha.
    if (vet[i]->freq > vet[l]->freq)
        menor = l;
  }
  if (r < n) { // If para que não apliquemos este passo em um nó folha.
    if (vet[menor]->freq < vet[r]->freq)
        menor = r;
  }
  if (menor != i) {
    trocar(&vet[i], &vet[menor]);
    heapify(vet, menor, n);
  }
}

void BuildMinHeap(NoTrie* vet, int n) {
  int i = (n/2) - 1;
  for (i; i >= 0; i--) {
    heapify(vet, i, n);
  }
}

void HeapSort(NoTrie* vet, int n) {
    BuildMinHeap(vet, n);
    for (int i = n - 1; i >= 2; i--) {
        trocar(&vet[0], &vet[i]);
        BuildMinHeap(vet, i);
    }
    trocar(&vet[0], &vet[1]);
}