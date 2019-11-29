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

noRN::noRN(unsigned int valor)
{
    this->valor = valor;
    esq = NULL;
    dir = NULL;
    cor = 1;
}

noRN::~noRN(){
}

unsigned int noRN::getValor()
{
    return this->valor;
}

void noRN::setValor(unsigned int valor)
{
    this->valor = valor;
}

noRN* noRN::getEsq()
{
    return esq;
}

void noRN::setEsq(noRN* esq)
{
    this->esq = esq;
}

noRN* noRN::getDir()
{
    return dir;
}

void noRN::setDir(noRN* dir)
{
    this->dir = dir;
}

int noRN::getCor()
{
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