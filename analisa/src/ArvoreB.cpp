#include <iostream>
#include <algorithm>
#include "../include/ArvoreB.h"
using namespace std;

#define d 2

ArvoreB::ArvoreB()
{
    this->raiz = NULL;
}

ArvoreB::~ArvoreB()
{
    libera(this->raiz);
}

No* ArvoreB::BuscaValor(int valor, int* posicao, No* p, bool* result)
{
    for(int i = 0 ; i < p->getNumChaves() ; i++)
    {
        if(valor == p->getValor(i))
        {
            *result = true;
            *posicao = i;
            return p;
        }

        if(valor < p->getValor(i))
        {
            if(p->getNo(i) == NULL)
            {
                *result = false;
                *posicao = i;
                return p;
            }
            else
                return BuscaValor(valor, posicao, p->getNo(i), result);
        }
    }
    if(p->getNo(p->getNumChaves()) == NULL)
    {
        *result = false;
        *posicao = p->getNumChaves();
        return p;
    }
    else
        return BuscaValor(valor, posicao, p->getNo(p->getNumChaves()), result);
}

No* getMaiorMaisProximo(int valor, No* p, int* i) {
    No* ptt = p->getNo(i + 1);
    while (ptt->getNo(0) != NULL) {
        ptt = ptt->getNo(0);
    }
    i = ptt->getValor(0);
    return ptt;
}

int ArvoreB::achaMediano(No* p, int val, int* posicaoMed) {
    int aux;
    if (p->getValor(d - 1) > val) {
        *posicaoMed = d - 1;
        aux = p->getValor(d - 1);
        p->setValor(d - 1, val);
        return aux;
    }
    if (p->getValor(d) < val){
        *posicaoMed = d;
        aux = p->getValor(d);
        p->setValor(d, val);
        return aux;
    }
    else {
        *posicaoMed = d - 1;
        return val;
    }
}

void ArvoreB::setRelacao(No* pai, int posicao, No* filho) {
    pai->setNo(filho, posicao);
    filho->setPai(pai);
}

void ArvoreB::separaNo(No* p, No* novoFilhoEsq, No* novoFilhoDir, No* novoNoEsq, No* novoNoDir, int val, int k) {
    int h = 0;
    int l = 0, c = 0;
    for (l; l < d; l++) {
        if (l == k) {
            novoNoEsq->setValor(l, val);
            setRelacao(novoNoEsq, l, novoFilhoEsq);
            setRelacao(novoNoEsq, l + 1, novoFilhoDir);
            if (k != d - 1)
                novoNoEsq->setValor(l + 1, p->getValor(l));
        }
        else {
            novoNoEsq->setValor(l, p->getValor(h));
            setRelacao(novoNoEsq, l, p->getNo(h));
            h++;
        }
    }
    if (k != d - 1 && k != d)
        setRelacao(novoNoEsq, d, p->getNo(h));
    h = d;
    if (k == d) {
        setRelacao(novoNoEsq, d, novoFilhoEsq);
        setRelacao(novoNoDir, 0, novoFilhoDir);
        novoNoDir->setValor(1, p->getValor(d));
        l = 1;
    }
    else {
        if (k < d)
            l = 0;
        else {
            l = 1;
            c = 1;
            h++;
        }
    }
    for (l; l - c < d; l++) {
        if (l + d == k) {
            novoNoDir->setValor(l - c, val);
            setRelacao(novoNoDir, l - c, novoFilhoEsq);
            setRelacao(novoNoDir, l - c + 1, novoFilhoDir);
            l++;
            if (k != 2 * d) {
                h++;
                novoNoDir->setValor(l - c, p->getValor(k));
            }
        }
        else {
            novoNoDir->setValor(l - c, p->getValor(h));
            setRelacao(novoNoDir, l - c, p->getNo(h));
            h++;
        }
    }
    if (k != (2 * d))
        setRelacao(novoNoDir, d, p->getNo(2 * d));
}

void ArvoreB::splitPropagado(No* p, No* novoFilhoEsq, No* novoFilhoDir, int valor, int k) {
    int posicao;
    int mediano = achaMediano(p, valor, &posicao);
    No* novoNoEsq = new No();
    No* novoNoDir = new No();
    novoNoDir->setNumChaves(d);
    novoNoEsq->setNumChaves(d);
    if (p == this->raiz) {
        No* novaRaiz = new No();
        this->raiz = novaRaiz;
        novaRaiz->setValor(0, mediano);
        separaNo(p, novoFilhoEsq, novoFilhoDir, novoNoEsq, novoNoDir, valor, k);
        setRelacao(novaRaiz, 0, novoNoEsq);
        setRelacao(novaRaiz, 1, novoNoDir);
        novaRaiz->setNumChaves(1);
    }
    else {
        int j;
        for (j = 0; j < p->getPai()->getNumChaves(); j++) {
            if (mediano < p->getPai()->getValor(j))
                break;
        }
        if (p->getPai()->getNumChaves() == 2 * d) {
            No* novoNoEsq = new No();
            No* novoNoDir = new No();
            separaNo(p, novoFilhoEsq, novoFilhoDir, novoNoEsq, novoNoDir, valor, k);
            splitPropagado(p->getPai(), novoNoEsq, novoNoDir, mediano, j);
        }
        else {
            separaNo(p, novoFilhoEsq, novoFilhoDir, novoNoEsq, novoNoDir, valor, k);
            for (int l = p->getPai()->getNumChaves(); l > j; l--) {
                p->getPai()->setValor(l, p->getPai()->getValor(l - 1));
                p->setNo(p->getPai()->getNo(l), l + 1);
            }
            p->getPai()->setValor(j, mediano);
            setRelacao(p->getPai(), j, novoNoEsq);
            setRelacao(p->getPai(), j + 1, novoNoDir);
            p->getPai()->setNumChaves(p->getPai()->getNumChaves() + 1);
        }
    }
}

void ArvoreB::primeiroSplit(No* p, int valor) {
    No* novoNoEsq = new No();
    No* novoNoDir = new No();
    novoNoDir->setNumChaves(d);
    novoNoEsq->setNumChaves(d);
    int vet[(2*d) + 1];
    for (int k = 0; k < 2 * d; k++) {
        vet[k] = p->getValor(k);
    }
    vet[2 * d] = valor;
    sort(vet, vet + (2*d) + 1);
    for(int k = 0; k < d; k++)
        novoNoEsq->setValor(k, vet[k]);
    for(int k = d + 1; k < (2*d) + 1; k++)
        novoNoDir->setValor(k - d - 1, vet[k]);
    if (p != this->raiz) {
        int k = 0;
        for (k; k < p->getPai()->getNumChaves(); k++) {
            if (vet[d] < p->getPai()->getValor(k))
                break;
        }
        if (p->getPai()->getNumChaves() == 2 * d) {
            splitPropagado(p->getPai(), novoNoEsq, novoNoDir, vet[d], k);
        }
        else {
            for (int i = p->getPai()->getNumChaves() - 1; i >= k; i--) {
                p->getPai()->setValor(i + 1, p->getPai()->getValor(i));
                p->getPai()->setNo(p->getPai()->getNo(i + 1), i + 2);
            }
            p->getPai()->setValor(k, vet[d]);
            p->getPai()->setNumChaves(p->getPai()->getNumChaves() + 1);
            setRelacao(p->getPai(), k, novoNoEsq);
            setRelacao(p->getPai(), k + 1, novoNoDir);
        }
    }
    else {
        No* novaRaiz = new No();
        this->raiz = novaRaiz;
        novaRaiz->setValor(0, vet[d]);
        setRelacao(novaRaiz, 0, novoNoEsq);
        setRelacao(novaRaiz, 1, novoNoDir);
        novaRaiz->setNumChaves(1);
    }
    p->~No();
}

void ArvoreB::insercao(int valor)
{
    if (this->raiz != NULL) {
        bool result;
        int posicao = 0;
        No* p = BuscaValor(valor, &posicao, this->raiz, &result);
        if (result != true) {
            if (p->getNumChaves() < 2 * d) {
                for (int i = p->getNumChaves() - 1; i >= posicao; i--) {
                    p->setValor(i + 1, p->getValor(i));
                }
                p->setValor(posicao, valor);
                p->setNumChaves(p->getNumChaves() + 1);
            }
            else {
                primeiroSplit(p, valor);
            }
        }
        else{
            cout << "Valor ja inserido ou algo assim" << endl;
        }

    }
    else {
        this->raiz = new No();
        this->raiz->setValor(0, valor);
        this->raiz->setNumChaves(1);
    }
}

No* ArvoreB::libera(No* no)
{
    if (no != NULL)
    {
        for(int i = 0 ; i < (2*d) + 1 ; i++)
        {
            no->setNo(libera(no->getNo(i)), i);
        }
        delete no;
    }
    return NULL;
}

void ArvoreB::Remocao(int valor) {
    No* p = BuscaValor(valor);
    if (p->getBool() == false) {
        int novoValor;
        No* ptt = getMaiorMaisProximo(valor, p, &novoValor);
    }
}

void ImprimeAux(No* p, int cont) {
    if (p->getNo(0) != NULL) {
        for (int k = 0; k < p->getNumChaves(); k++) {
            ImprimeAux(p->getNo(k), cont + 1);
            for (int j = 0; j < cont; j++)
                cout << "|";
            cout << "  " <<  p->getValor(k) << "  ";
            for (int j = 0; j < cont; j++)
                cout << "|";
        }
        ImprimeAux(p->getNo(p->getNumChaves()), cont + 1);
    }
    else {
        cout << "(";
        for (int k = 0; k < p->getNumChaves(); k++) {
            cout << "  " << p->getValor(k) << "  ";
        }
        cout << ")";
    }
}

void ArvoreB::Imprime() {
    ImprimeAux(this->raiz, 1);
}
