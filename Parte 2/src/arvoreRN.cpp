#include <iostream>
#include "../include/arvoreRN.h"

using namespace std;

arvoreRN::arvoreRN()
{
    raiz = NULL;
}

arvoreRN::arvoreRN(int valor)
{
    raiz->setValor(valor);
    raiz->setCor(0);
}

arvoreRN::~arvoreRN(){
    //libera(this->raiz);
}

noRN* arvoreRN::getRaiz()
{
    return raiz;
}

void arvoreRN::setRaiz(noRN* raiz)
{
    raiz->setCor(0);
    this->raiz = raiz;
}

noRN* arvoreRN::hNegra(arvoreRN* arv)
{
    noRN* p = arv->getRaiz();
    auxHNegra(p, 0, 0);

    return p; 
} // se p for NULL significa que altura negra é igual dos ambos os lados
  // mas se nao for, retorna o No problematico    

void arvoreRN::auxHNegra(noRN* p, int hNegraE, int hNegraD)
{
    if(p == NULL)
    {
        if(hNegraE == hNegraD)
            p = NULL;

        return;
    }
    if(p->getEsq()->getCor() == 0)
        auxHNegra(p->getEsq(), hNegraE + 1, hNegraD);
    else
        auxHNegra(p->getEsq(), hNegraE, hNegraD);

    if(p->getDir()->getCor() == 0)
        auxHNegra(p->getDir(), hNegraE, hNegraD + 1);
    else
        auxHNegra(p->getDir(), hNegraE, hNegraD);    
}
void arvoreRN::rotacaoDir(noRN* no)
{
    noRN* avo = no->getAvo();
    noRN* pai = no->getPai();

    avo->setEsq(pai->getDir());
    pai->setDir(avo);

    if(avo != this->raiz)
    {
        noRN* sup = avo->getPai();
        if(avo == sup->getEsq())
            sup->setEsq(pai);
        else
            sup->setDir(pai);
    }

    pai->setCor(0);
    avo->setCor(1);
}

void arvoreRN::rotacaoEsq(noRN* no)
{
    noRN* avo = no->getAvo();
    noRN* pai = no->getPai();

    avo->setDir(pai->getEsq());
    pai->setEsq(avo);

    if(avo != this->raiz)
    {
        noRN* sup = avo->getPai();
        if(avo == sup->getEsq())
            sup->setEsq(pai);
        else
            sup->setDir(pai);
    }

    pai->setCor(0);
    avo->setCor(1);
}

void arvoreRN::rotacaoDuploEsq(noRN* no)
{
    noRN* avo = no->getAvo();
    noRN* pai = no->getPai();

    pai->setEsq(no->getDir());
    avo->setDir(no);
    no->setDir(pai);

    rotacaoEsq(pai);
}

void arvoreRN::rotacaoDuploDir(noRN* no)
{
    noRN* avo = no->getAvo();
    noRN* pai = no->getPai();

    pai->setDir(no->getEsq());
    avo->setEsq(no);
    no->setEsq(pai);

    rotacaoDir(pai);
}

void arvoreRN::inserirNo(noRN* novoNo)
{
    noRN* p = raiz;
    noRN* pAnt = NULL;

    if(p == NULL)
    {
        novoNo->setCor(0);
        raiz = novoNo;

        return;
    } // caso a arvore esteja vazia

    while(p != NULL)
    {
        if(novoNo->getValor() < p->getValor())
        {
            pAnt = p;
            p = p->getEsq();
        }
        else
        {
            pAnt = p;
            p = p->getDir();
        }
    } // pAnt eh o no folha, futuro pai do novoNo
    
    if(novoNo->getValor() < pAnt->getValor())
        pAnt->setEsq(novoNo);
    else
        pAnt->setDir(novoNo);

    // metodos para manter propriedades de arvore rubro negra
    if(novoNo->getPai()->getCor() == 1)
    {
        if(novoNo->getTio()->getCor() == 1)
        {
            novoNo->getAvo()->setCor(1);
            novoNo->getTio()->setCor(0);
            novoNo->getPai()->setCor(0);
        } // caso tio tambem for vermelho, recolorimos os tres nos
        else
        {
            noRN* avo = novoNo->getAvo();
            noRN* pai = novoNo->getPai();

            if(avo->getDir() == pai && pai->getDir() == novoNo)
                rotacaoEsq(novoNo);
            if(avo->getEsq() == pai && pai->getEsq() == novoNo)
                rotacaoDir(novoNo);
            if(avo->getDir() == pai && pai->getEsq() == novoNo)
                rotacaoDuploEsq(novoNo);
            if(avo->getEsq() == pai && pai->getDir() == novoNo)
                rotacaoDuploDir(novoNo);
        } // caso tio for preto, aplicar rotacoes
    } // se o pai for vermelho, como o filho
}

void arvoreRN::inserirValor(int valor)
{
    noRN* novoNo = new noRN();
    novoNo->setValor(valor);

    inserirNo(novoNo);
}