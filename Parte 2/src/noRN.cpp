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
        if(libera(this->esq) != NULL)
        {
            cout << "ERRO NO SETESQ" << endl;
            exit(1);
        }
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
        if(libera(this->dir) != NULL)
        {
            cout << "ERRO NO SETDIR" << endl;
            exit(1);
        }
    }

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