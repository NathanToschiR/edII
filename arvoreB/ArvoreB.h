#ifndef ARVOREB_H
#define ARVOREB_H
#include <iostream>
#include "No.h"

using namespace std;

class ArvoreB {
    public:
        ArvoreB();
        ~ArvoreB();
        void insercao(int valor, unsigned int* copias, unsigned int* comp);
        No* BuscaValor(int valor, int* posicao, No* p, bool* result, unsigned int* comp);
        No* libera(No* no);
        void splitPropagado(No* p, No* novoFilhoEsq, No* novoFilhoDir, int valor, int k, unsigned int* copias, unsigned int* comp);
        void Imprime();
        int achaMediano(No* p, int val, int* posicaoMed, unsigned int* comp);
        void setRelacao(No* pai, int posicao, No* filho);
        void separaNo(No* p, No* novoFilhoEsq, No* novoFilhoDir, No* novoNoEsq, No* novoNoDir, int val, int k, unsigned int* copias, unsigned int* comp);
        void primeiroSplit(No* p, int valor, unsigned int* copias, unsigned int* comp);
        void remove(int valor, unsigned int* comp);

    private:
        int ProcuraNoPai(No* p);
        void verificacaoBraba(No* p);
        void ConcatenaNosFolhas(No* p, No* r);
        void ConcatenaNosInternos(No* p, No* r);
        void RedistribuiNoFolha(No* p, No* r);
        void RedistribuiNoInterno(No* p, No* r);
        void PrimeiraRemocao(int valor, No* p, int posicao);
        No* raiz;

};

#endif // ARVOREB_H