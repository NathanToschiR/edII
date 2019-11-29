
#ifndef ARVORERN_H
#define ARVORERN_H
#include <iostream>
#include "noRN.h"

class arvoreRN
{
    public:
        arvoreRN();
        arvoreRN(int valor);
        ~arvoreRN();
        noRN* getRaiz();
        void setRaiz(noRN* raiz);
        void inserirNo(noRN* no, double* vetDadosInsercao);
        void inserirValor(int valor, double* vetDadosInsercao);
        noRN* busca(int valor, double* vetDadosBusca);
        void imprimirArv();
        void auxImprimirArv(noRN* no);

    private:
        noRN* raiz;
        void getFamilia(noRN* no, noRN** pPai, noRN** pTio, noRN** pAvo);
        void rotacaoDir(noRN* no);
        void rotacaoEsq(noRN* no);
        void rotacaoDuploEsq(noRN* no);
        void rotacaoDuploDir(noRN* no);
};

#endif // ARVORERN_H