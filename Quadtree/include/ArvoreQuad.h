#ifndef ARVOREQUAD_H
#define ARVOREQUAD_H
#include "NoQuad.h"

using namespace std;


class ArvoreQuad
{
    public:
        ArvoreQuad();
        virtual ~ArvoreQuad();
        int getTamanho();
        void setTamanho(int tam);
        void setRaiz(NoQuad* no);
        NoQuad* getRaiz();
        NoQuad* auxBusca(int x, int y, NoQuad* p);
        NoQuad* busca(int x, int y);
        void auxInsere(int x, int y, NoQuad* q, NoQuad* p);
        void insere(int x, int y);

    private:
        NoQuad* raiz;
        int tamanho;

};

#endif // ARVOREQUAD_H
