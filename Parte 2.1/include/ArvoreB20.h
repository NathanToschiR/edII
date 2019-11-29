#ifndef ARVOREB20_H
#define ARVOREB20_H
#include <iostream>
#include "No.h"

using namespace std;

class ArvoreB20 {
    public:
        ArvoreB20();
        ~ArvoreB20();
        void inserirValor(int valor, double* copias, double* comp);
        No* BuscaValorParaInsercao(int valor, int* posicao, No* p, bool* result, double* comp);
        void busca(int valor, double* comp);
        No* libera(No* no);
        void splitPropagado(No* p, No* novoFilhoEsq, No* novoFilhoDir, int valor, int k, double* copias, double* comp);
        void Imprime();
        int achaMediano(No* p, int val, int* posicaoMed, double* comp);
        void setRelacao(No* pai, int posicao, No* filho);
        void separaNo(No* p, No* novoFilhoEsq, No* novoFilhoDir, No* novoNoEsq, No* novoNoDir, int val, int k, double* copias, double* comp);
        void primeiroSplit(No* p, int valor, double* copias, double* comp);
        void remove(int valor, double* comp);

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

#endif // ARVOREB20_H