#include <iostream>
#include "NoTrie.h"
#include "MinHeapTrie.h"

using namespace std;

void ConstroiHuffmanTrie(NoTrie* vet, int n) {
    if (n != 1) {
        BuildMinHeap(vet, n);
        trocar(&vet[0], &vet[n - 1]);
        BuildMinHeap(vet, n - 1);
        NoTrie* noTriePai = new NoTrie();
        noTriePai->setFreq(vet[n - 1]->getFreq() + vet[n - 2]->getFreq());
        noTriePai->setFilhoEsq(vet[n - 1]);
        noTriePai->setFilhoDir(vet[n - 2]);
        vet[n - 2] = noTriePai;
        ConstroiHuffmanTrie(vet, n - 1);
    }
}