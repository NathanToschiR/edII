#ifndef NORN_H
#define NORN_H
#include <iostream>

class noRN
{
    public:
        noRN();
        noRN(unsigned int valor);
        ~noRN();
        unsigned int getValor();
        void setValor(unsigned int valor);
        noRN* getEsq();
        void setEsq(noRN* esq);
        noRN* getDir();
        void setDir(noRN* dir);
        int getCor();
        void setCor(int cor);
        noRN* libera(noRN* no);

    private:
        unsigned int valor;
        int cor; // 0 - preto, 1 - vermelho;
        noRN* esq;
        noRN* dir;
};


#endif // NORN_H