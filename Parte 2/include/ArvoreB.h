#ifndef ARVOREB_H
#define ARVOREB_H
#include <iostream>
#include "No.h"

using namespace std;

class ArvoreB {
    public:
        ArvoreB();
        ~ArvoreB();
        void insercao(int valor);
        No* BuscaValor(int valor, int* posicao, No* p, bool* result);
        No* libera(No* no);
        void splitPropagado(No* p, No* novoFilhoEsq, No* novoFilhoDir, int valor, int k);
        void Imprime();
        int achaMediano(No* p, int val, int* posicaoMed);
        void setRelacao(No* pai, int posicao, No* filho);
        void separaNo(No* p, No* novoFilhoEsq, No* novoFilhoDir, No* novoNoEsq, No* novoNoDir, int val, int k);
        void primeiroSplit(No* p, int valor);

    private:
        No* raiz;

};

#endif // ARVOREB_H