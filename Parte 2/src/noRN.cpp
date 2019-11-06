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

arvoreRN* noRN::getArvore()
{
    return this->arv;
}

void noRN::setArvore(arvoreRN* arv)
{
    this->arv = arv;
}

noRN* noRN::getPai()
{
    noRN* p = this->getArvore()->getRaiz();
    noRN* pPai = NULL;

    while(p != this)
    {
        if(this->getValor() < p->getValor())
        {
            pPai = p;
            p = p->getEsq();
        }
        else
        {
            pPai = p;
            p = p->getDir();
        }
    }

    return pPai;
}

noRN* noRN::getTio()
{
    noRN* p = this->getArvore()->getRaiz();
    noRN* pPai = NULL;
    noRN* pTio = NULL;

    while(p != this || p != NULL)
    {
        if(this->getValor() < p->getValor())
        {
            pTio = pPai->getEsq();
            pPai = p;
            p = p->getEsq();
        }
        else
        {
            pTio = pPai->getDir();
            pPai = p;
            p = p->getDir();
        }
    }

    return pTio;
}

noRN* noRN::getAvo()
{
    noRN* p = this->getArvore()->getRaiz();
    noRN* pPai = NULL;
    noRN* pAvo = NULL;

    while(p != this || p != NULL)
    {
        if(this->getValor() < p->getValor())
        {
            pAvo = pPai;
            pPai = p;
            p = p->getEsq();
        }
        else
        {
            pAvo = pPai;
            pPai = p;
            p = p->getDir();
        }
    }

    return pAvo;
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