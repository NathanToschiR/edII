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

void arvoreRN::getFamilia(noRN* no, noRN** pPai, noRN** pTio, noRN** pAvo)
{
    noRN* p = this->raiz;

    if(no != NULL)
    {
        while(p != no)
        {
            *pAvo = *pPai;
            *pPai = p;

            if(no->getValor() < p->getValor())
                p = p->getEsq();
            else
                p = p->getDir();
        }

        if(*pAvo == NULL)
            *pTio = NULL;
        else
        {
            if(*pPai == (*pAvo)->getDir())
            {
                if((*pAvo)->getEsq() != NULL)
                    *pTio = (*pAvo)->getEsq();
            }
            else
            {
                if((*pAvo)->getDir() != NULL)
                    *pTio = (*pAvo)->getDir();
            }
        }
    }
    else
    {
        cout << "ERRO: NO NULO" << endl;
        exit(1);
    }
}

void arvoreRN::rotacaoDir(noRN* no)
{
    noRN* pai = NULL;
    noRN* tio = NULL;
    noRN* avo = NULL;

    getFamilia(no, &pai, &tio, &avo);

    avo->setEsq(pai->getDir());
    pai->setDir(avo);

    if(avo != this->raiz)
    {
        noRN* a = NULL;
        noRN* b = NULL;
        noRN* sup = NULL; // no pai do no avo
        getFamilia(avo, &sup, &a, &b);

        if(avo == sup->getEsq())
            sup->setEsq(pai);
        else
            sup->setDir(pai);
    }
    else
    {
        this->setRaiz(pai);
    }

    pai->setCor(0);
    avo->setCor(1);
}

void arvoreRN::rotacaoEsq(noRN* no)
{
    noRN* pai = NULL;
    noRN* tio = NULL;
    noRN* avo = NULL;

    getFamilia(no, &pai, &tio, &avo);

    avo->setDir(pai->getEsq());
    pai->setEsq(avo);

    if(avo != this->raiz)
    {
        noRN* a = NULL;
        noRN* b = NULL;
        noRN* sup = NULL;
        getFamilia(avo, &sup, &a, &b);
        if(avo == sup->getEsq())
            sup->setEsq(pai);
        else
            sup->setDir(pai);
    }
    else
    {
        this->setRaiz(pai);
    }

    pai->setCor(0);
    avo->setCor(1);
}

void arvoreRN::rotacaoDuploEsq(noRN* no)
{
    noRN* pai = NULL;
    noRN* tio = NULL;
    noRN* avo = NULL;

    getFamilia(no, &pai, &tio, &avo);

    pai->setEsq(no->getDir());
    avo->setDir(no);
    no->setDir(pai);

    rotacaoEsq(pai);
}

void arvoreRN::rotacaoDuploDir(noRN* no)
{
    noRN* pai = NULL;
    noRN* tio = NULL;
    noRN* avo = NULL;

    getFamilia(no, &pai, &tio, &avo);

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
        this->raiz = novoNo;

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
    noRN* pai = NULL;
    noRN* tio = NULL;
    noRN* avo = NULL;

    getFamilia(novoNo, &pai, &tio, &avo);

    if(pai->getCor() == 1)
    {
        if(tio != NULL && tio->getCor() == 1)
        {
            avo->setCor(1);
            tio->setCor(0);
            pai->setCor(0);

            if(avo == this->getRaiz())
            {
                avo->setCor(0);
                return;
            }

            noRN* aPai = NULL;
            noRN* aTio = NULL;
            noRN* aAvo = NULL;

            getFamilia(avo, &aPai, &aTio, &aAvo);


            while(aPai->getCor() == 1)
            {
                if(aTio != NULL && aTio->getCor() == 1)
                {
                    aAvo->setCor(1);
                    aTio->setCor(0);
                    aPai->setCor(0);

                    noRN* bisa = NULL;

                    getFamilia(aAvo, &aPai, &aTio, &bisa);

                    aAvo = bisa;
                }
                else
                {
                    if(aAvo->getDir() == aPai && aPai->getDir() == avo)
                        rotacaoEsq(avo);
                    if(aAvo->getEsq() == aPai && aPai->getEsq() == avo)
                        rotacaoDir(avo);
                    if(aAvo->getDir() == aPai && aPai->getEsq() == avo)
                        rotacaoDuploEsq(avo);
                    if(aAvo->getEsq() == aPai && aPai->getDir() == avo)
                        rotacaoDuploDir(avo);
                    break;
                }
            }

        } // caso tio tambem for vermelho, recolorimos os tres nos
        else
        {
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

    raiz->setCor(0);
}

void arvoreRN::inserirValor(int valor)
{
    noRN* novoNo = new noRN();
    novoNo->setValor(valor);

    inserirNo(novoNo);
}

void arvoreRN::auxImprimirArv(noRN* no)
{
    if(no != NULL)
    {
        auxImprimirArv(no->getEsq());
        cout << no->getValor();
        if(no->getCor() == 0)
            cout << "(p)  ";
        else
            cout << "(v)  ";

        auxImprimirArv(no->getDir());
    }
}

void arvoreRN::imprimirArv()
{
    noRN* p = this->raiz;

    auxImprimirArv(p);
}
