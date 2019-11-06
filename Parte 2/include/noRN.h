#ifndef NORN_H
#define NORN_H
#include <iostream>
#include "arvoreRN.h"

using namespace std;

class noRN
{
    public:
        noRN();
        noRN(int valor);
        ~noRN();
        int getValor();
        void setValor(int valor);
        noRN* getEsq();
        void setEsq(noRN* esq);
        noRN* getDir();
        void setDir(noRN* dir);
        noRN* getPai();
        noRN* getTio();
        noRN* getAvo();
        int getCor();
        void setCor(int cor);
        noRN* libera(noRN* no);

    private:
        int valor;
        int cor; // 0 - preto, 1 - vermelho;
        noRN* esq;
        noRN* dir;
};

#endif // NORN_H
