#include <iostream>
#include "../include/noRN.h"

using namespace std;

noRN::noRN()
{
    valor = -1;
    esq = NULL;
    dir = NULL;
    cor = 1;
}

noRN::noRN(int valor)
{
    this->valor = valor;
    esq = NULL;
    dir = NULL;
    cor = 1;
}

noRN::~noRN(){
}

int noRN::getValor()
{
    return valor;
}

void noRN::setValor(int valor)
{
    this->valor = valor;
}

noRN* noRN::getEsq()
{
    return esq;
}

void noRN::setEsq(noRN* esq)
{
    if(this->esq != NULL)
    {
        libera(this->esq);
    }

    this->esq = esq;    
}

noRN* noRN::getDir()
{
    return dir;
}

void noRN::setDir(noRN* dir)
{
    if(this->dir != NULL)
    {
        libera(this->dir);
    }

    this->dir = dir;  
}

int noRN::getCor()
{
    if(this == NULL)
    {
        return 0;
    } // caso o No for NULL ele é por padrao, preto

    return cor;
}

void noRN::setCor(int cor)
{
    this->cor = cor;
}

noRN* noRN::libera(noRN* no)
{
    if (no != NULL)
    {
        no->setEsq(libera(no->getEsq()));
        no->setDir(libera(no->getDir()));
        delete no;
    }
    return NULL;
}