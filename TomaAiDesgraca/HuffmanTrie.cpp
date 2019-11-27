#include <iostream>
#include "NoTrie.h"
#include "HuffmanTrie.h"

using namespace std;


void copia(NoTrie *a, NoTrie *b) {
    a->setLetra(b->getLetra());
    a->setFreq(b->getFreq());
    a->setHuff(b->getHuff());
    a->setFilhoEsq(b->getFilhoEsq());
    a->setFilhoDir(b->getFilhoDir());
}

void trocar(NoTrie *a, NoTrie *b)
{
    NoTrie aux;
    copia(&aux, a);
    copia(a, b);
    copia(b, &aux);
}

void heapify(NoTrie* vet, int i, int n) { // Passamos o inteiro n para que não comparemos elementos com indices maiores que n.
  int l = (2*i) + 1;
  int r = (2*i) + 2;
  int menor = i;
  if (l < n) { // If para que não apliquemos este passo em um nó folha->
    if (vet[i].getFreq() > vet[l].getFreq())
        menor = l;
  }
  if (r < n) { // If para que não apliquemos este passo em um nó folha->
    if (vet[menor].getFreq() > vet[r].getFreq())
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

HuffmanTrie::HuffmanTrie() {
    this->raiz = NULL;
}

HuffmanTrie::~HuffmanTrie() {
}

NoTrie* HuffmanTrie::getRaiz() {
    return this->raiz;
}

void HuffmanTrie::setRaiz(NoTrie* raiz) {
    this->raiz = raiz;
}

void HuffmanTrie::ConstroiHuffmanTrieAux(NoTrie* vet, int n) {
    if (n != 1) {
        BuildMinHeap(vet, n);
        trocar(&vet[0], &vet[n - 1]);
        BuildMinHeap(vet, n - 1);
        trocar(&vet[0], &vet[n - 2]);
        NoTrie* noTriePai = new NoTrie();
        NoTrie* filhoEsq = new NoTrie();
        NoTrie* filhoDir = new NoTrie();
        copia(filhoEsq, &vet[n - 2]);
        copia(filhoDir, &vet[n - 1]);
        noTriePai->setFreq(vet[n - 1].getFreq() + vet[n - 2].getFreq());
        noTriePai->setFilhoEsq(filhoEsq);
        noTriePai->setFilhoDir(filhoDir);
        copia(&vet[n - 2], noTriePai);
        ConstroiHuffmanTrieAux(vet, n - 1);
    }
    else
        this->raiz = &vet[0];
}

void HuffmanTrie::ConstroiHuffmanTrie(string msg, int n) {
    NoTrie* vet = new NoTrie[msg.length()];
    NoTrie* vetAux = new NoTrie[msg.length()];
    bool ver;
    for (int k = 0; k < msg.length(); k++) {
        vet[k].setLetra(' '); // mudar 
    }
    int h = 0;
    for (int i = 0; i < msg.length(); i++) {
        ver = true;
        for (int j = 0; j < i && ver == true; j++) {
            if (vet[j].getLetra() == msg[i]) {
                vet[j].setFreq(vet[j].getFreq() + 1);
                ver = false;
            }
        }
        if (ver == true){
            vet[h].setLetra(msg[i]);
            vet[h].setFreq(1);
            h++;
        }
    }
    for (int k = 0; k < msg.length(); k++){
        if (vet[k].getLetra() == ' '){
            h = k;
            break;
        }
        else
            vetAux[k] = vet[k];
    }
    ConstroiHuffmanTrieAux(vetAux, h);
}

bool AchaCodigoAux(char a, NoTrie* p, string* str, string strAux) {
    if (p->getFilhoEsq() == NULL) {
        if (p->getLetra() == a) {
            *str = strAux;
            return 1;
        }
        return 0;
    }
    else  {
        if (AchaCodigoAux(a, p->getFilhoEsq(), str, strAux + '0'))
            return 1;
        if (AchaCodigoAux(a, p->getFilhoDir(), str, strAux + '1'))
            return 1;
        return 0;
    }
}

string HuffmanTrie::AchaCodigo(char a) {
    NoTrie* p = this->raiz;
    string str ("");
    string strAux ("");
    AchaCodigoAux(a, p, &str, strAux);
    return str;
}