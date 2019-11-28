#include <iostream>
#include <algorithm>
#include "ArvoreB.h"
#include "No.h"
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

No* ArvoreB::BuscaValor(int valor, int* posicao, No* p, bool* result, unsigned int* comp)
{
    for(int i = 0 ; i < p->getNumChaves() ; i++)
    {
        (*comp) = (*comp) + 2;
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
                return BuscaValor(valor, posicao, p->getNo(i), result, comp);
        }   
    }
    if(p->getNo(p->getNumChaves()) == NULL)
    {
        *result = false;
        *posicao = p->getNumChaves();
        return p;
    }
    else
        return BuscaValor(valor, posicao, p->getNo(p->getNumChaves()), result, comp);
}

No* getMaiorMaisProximo(int valor, int posicao, No* p, int* i) {
    No* ptt = p->getNo(posicao + 1);
    while (ptt->getNo(0) != NULL) {
        ptt = ptt->getNo(0);
    }
    *i = ptt->getValor(0);
    return ptt;
}

int ArvoreB::achaMediano(No* p, int val, int* posicaoMed, unsigned int* comp) {
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
    (*comp) = (*comp) + 2;
}

void ArvoreB::setRelacao(No* pai, int posicao, No* filho) {
    pai->setNo(filho, posicao);
    filho->setPai(pai);
}

void ArvoreB::separaNo(No* p, No* novoFilhoEsq, No* novoFilhoDir, No* novoNoEsq, No* novoNoDir, int val, int k, unsigned int* copias, unsigned int* comp) {
    int h = 0;
    int l = 0, c = 0;
    for (l; l < d; l++) {
        if (l == k) {
            novoNoEsq->setValor(l, val);
            setRelacao(novoNoEsq, l, novoFilhoEsq);
            setRelacao(novoNoEsq, l + 1, novoFilhoDir);
            if (k != d - 1) {
                novoNoEsq->setValor(l + 1, p->getValor(l));
                (*copias)++;
            }
        }
        else {
            novoNoEsq->setValor(l, p->getValor(h));
            setRelacao(novoNoEsq, l, p->getNo(h));
            h++;
        }
    }
    (*copias) = (*copias) + d;
    if (k != d - 1 && k != d)
        setRelacao(novoNoEsq, d, p->getNo(h));
    h = d;
    if (k == d) {
        setRelacao(novoNoEsq, d, novoFilhoEsq);
        setRelacao(novoNoDir, 0, novoFilhoDir);
        novoNoDir->setValor(1, p->getValor(d));
        (*copias)++;
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
            (*copias)++;
            setRelacao(novoNoDir, l - c, novoFilhoEsq);
            setRelacao(novoNoDir, l - c + 1, novoFilhoDir);
            l++;
            if (k != 2 * d) {
                h++;
                novoNoDir->setValor(l - c, p->getValor(k));
                (*copias)++;
            }
        }
        else {
            novoNoDir->setValor(l - c, p->getValor(h));
            (*copias)++;
            setRelacao(novoNoDir, l - c, p->getNo(h));
            h++;
        }
    }
    if (k != (2 * d))
        setRelacao(novoNoDir, d, p->getNo(2 * d));
}

void ArvoreB::splitPropagado(No* p, No* novoFilhoEsq, No* novoFilhoDir, int valor, int k, unsigned int* copias, unsigned int* comp) {
    int posicao;
    int mediano = achaMediano(p, valor, &posicao, comp);
    No* novoNoEsq = new No();
    No* novoNoDir = new No();
    novoNoDir->setNumChaves(d);
    novoNoEsq->setNumChaves(d);
    novoNoEsq->setBool(false);
    novoNoDir->setBool(false);
    if (p == this->raiz) {
        No* novaRaiz = new No();
        this->raiz = novaRaiz;
        novaRaiz->setValor(0, mediano);
        (*copias)++;
        separaNo(p, novoFilhoEsq, novoFilhoDir, novoNoEsq, novoNoDir, valor, k, copias, comp);
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
        (*comp) = (*comp) + j + 1;
        if (p->getPai()->getNumChaves() == 2 * d) {
            No* novoNoEsq = new No();
            No* novoNoDir = new No();
            separaNo(p, novoFilhoEsq, novoFilhoDir, novoNoEsq, novoNoDir, valor, k, copias, comp);
            splitPropagado(p->getPai(), novoNoEsq, novoNoDir, mediano, j, copias, comp);
        }
        else {
            separaNo(p, novoFilhoEsq, novoFilhoDir, novoNoEsq, novoNoDir, valor, k, copias, comp);
            for (int l = p->getPai()->getNumChaves(); l > j; l--) {
                p->getPai()->setValor(l, p->getPai()->getValor(l - 1));
                p->setNo(p->getPai()->getNo(l), l + 1);
            }
            p->getPai()->setValor(j, mediano);
            (*copias) = (*copias) + p->getPai()->getNumChaves() - j + 1;
            setRelacao(p->getPai(), j, novoNoEsq);
            setRelacao(p->getPai(), j + 1, novoNoDir);
            p->getPai()->setNumChaves(p->getPai()->getNumChaves() + 1);
        }
    }
}

void ArvoreB::primeiroSplit(No* p, int valor, unsigned int* copias, unsigned int* comp) {
    No* novoNoEsq = new No();
    No* novoNoDir = new No();
    novoNoDir->setNumChaves(d);
    novoNoEsq->setNumChaves(d);
    int vet[(2*d) + 1];
    for (int k = 0; k < 2 * d; k++) {
        vet[k] = p->getValor(k);
    }
    (*copias) = (*copias) + (2*d) + 1;
    vet[2 * d] = valor;
    sort(vet, vet + (2*d) + 1);
    for(int k = 0; k < d; k++)
        novoNoEsq->setValor(k, vet[k]);
    for(int k = d + 1; k < (2*d) + 1; k++)
        novoNoDir->setValor(k - d - 1, vet[k]);
    (*copias) = (*copias) + 2;
    if (p != this->raiz) {
        int k = 0;
        for (k; k < p->getPai()->getNumChaves(); k++) {
            if (vet[d] < p->getPai()->getValor(k))
                break;
        }
        (*comp) = (*comp) + k;
        if (p->getPai()->getNumChaves() == 2 * d) {
            splitPropagado(p->getPai(), novoNoEsq, novoNoDir, vet[d], k, copias, comp);
        }
        else {
            for (int i = p->getPai()->getNumChaves() - 1; i >= k; i--) {
                p->getPai()->setValor(i + 1, p->getPai()->getValor(i));
                p->getPai()->setNo(p->getPai()->getNo(i + 1), i + 2);
            }
            p->getPai()->setValor(k, vet[d]);
            (*copias) = (*copias) + p->getNumChaves() + 1 - k;
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
        novaRaiz->setBool(false);
        (*copias) = (*copias) + 1;
    }
    p->~No();
}

void ArvoreB::insercao(int valor, unsigned int* copias, unsigned int* comp)
{
    if (this->raiz != NULL) {
        bool result;
        int posicao = 0;
        No* p = BuscaValor(valor, &posicao, this->raiz, &result, comp);
        if (result != true) {
            if (p->getNumChaves() < 2 * d) {
                for (int i = p->getNumChaves() - 1; i >= posicao; i--) {
                    p->setValor(i + 1, p->getValor(i));
                }
                p->setValor(posicao, valor);
                p->setNumChaves(p->getNumChaves() + 1);
                (*copias) = (*copias) + p->getNumChaves() - posicao + 1;
            }
            else {
                primeiroSplit(p, valor, copias, comp);
            }
        }
        else{
            cout << "Valor ja inserido" << endl;
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

int ArvoreB::ProcuraNoPai(No* p) {
    for (int k = 0; k < p->getPai()->getNumChaves(); k++) {
        if (p->getPai()->getNo(k)->getValor(0) == p->getValor(0))
            return k;
    }
    return p->getPai()->getNumChaves();
}

void verificacaoBraba(No* p); // Aqui da um problema de uma funcao chama a outra e a outra chama a um

void ArvoreB::ConcatenaNosFolhas(No* p, No* r) {
    int posicao = ProcuraNoPai(p);
    for (int k = r->getNumChaves() - 1; k >= 0; k--)
        r->setValor(k + p->getNumChaves() + 1, r->getValor(k));
    r->setValor(p->getNumChaves(), p->getPai()->getValor(posicao));
    
    for (int k = posicao; k < p->getPai()->getNumChaves() - 1; k++) {
        p->getPai()->setValor(k, p->getPai()->getValor(k + 1));
        setRelacao(p->getPai(), k + 1, p->getPai()->getNo(k + 2));
    }
    p->getPai()->setNo(NULL, p->getPai()->getNumChaves());
    
    for (int k = 0; k < p->getNumChaves(); k++)
        r->setValor(k, p->getValor(k));
    r->setNumChaves(r->getNumChaves() + p->getNumChaves() + 1);
    p->getPai()->setNumChaves(p->getPai()->getNumChaves() - 1);
    p->getPai()->setNo(r, posicao);

    if (p->getPai()->getNumChaves() == 0) {
        this->raiz = r;
    }
    else if (p->getPai()->getNumChaves() < d) {
        verificacaoBraba(p->getPai());
    }

}

void ArvoreB::ConcatenaNosInternos(No* p, No* r) {
    int posicao = ProcuraNoPai(p);
    for (int k = r->getNumChaves() - 1; k >= 0; k--){
        r->setValor(k + p->getNumChaves() + 1, r->getValor(k));
        r->setNo(r->getNo(k + 1), k + p->getNumChaves() + 2);
    }
    r->setNo(r->getNo(0), p->getNumChaves() + 1);
    r->setValor(p->getNumChaves(), p->getPai()->getValor(posicao));
        
    for (int k = posicao; k < p->getPai()->getNumChaves() - 1; k++) {
        p->getPai()->setValor(k, p->getPai()->getValor(k + 1));
        setRelacao(p->getPai(), k + 1, p->getPai()->getNo(k + 2));
    }
    p->getPai()->setNo(NULL, p->getPai()->getNumChaves());

    setRelacao(p->getPai(), posicao, r);
    for (int k = 0; k < p->getNumChaves(); k++) {
        r->setValor(k, p->getValor(k));
        setRelacao(r, k + 1, p->getNo(k + 1));
    }
    setRelacao(r, 0, p->getNo(0));
    r->setNumChaves(r->getNumChaves() + p->getNumChaves() + 1);
    p->getPai()->setNumChaves(p->getPai()->getNumChaves() - 1);
    p->getPai()->setNo(r, posicao);
    
    if (p->getPai()->getNumChaves() == 0) {
        this->raiz = r;
    }
    else if (p->getPai()->getNumChaves() < d) {
        verificacaoBraba(p->getPai());
    }

}

void ArvoreB::RedistribuiNoFolha(No* p, No* r) {
    int posicao = ProcuraNoPai(p);
    int num = p->getNumChaves() + r->getNumChaves() + 1;
    int vet[num];
    int k;
    for (k = 0; k < p->getNumChaves(); k++)
        vet[k] = p->getValor(k);
    vet[k] = p->getPai()->getValor(posicao);
    k++;
    for (int j = 0; j < r->getNumChaves(); j++)
        vet[k + j] = r->getValor(j);
    p->getPai()->setValor(posicao, vet[num/2]);
    for (int j = 0; j < num/2; j++)
        p->setValor(j, vet[j]);
    for (int j = (num/2) + 1; j < num; j++)
        r->setValor(j - (num/2) - 1, vet[j]);
    p->setNumChaves(num/2);
    r->setNumChaves(num - (num/2) - 1); // divisao inteira
}

void ArvoreB::RedistribuiNoInterno(No* p, No* r) {
    int posicao = ProcuraNoPai(p);
    int num = p->getNumChaves() + r->getNumChaves() + 1;
    int vet[num];
    No** vetNo = new No*[num + 1];
    int k;
    for (k = 0; k < p->getNumChaves(); k++){
        vet[k] = p->getValor(k);
        vetNo[k] = p->getNo(k);
    }
    vet[k] = p->getPai()->getValor(posicao);
    vetNo[k] = p->getNo(p->getNumChaves());
    k++;
    for (int j = 0; j < r->getNumChaves(); j++) {
        vet[k + j] = r->getValor(j);
        vetNo[k + j] = r->getNo(j);
    }
    vetNo[num] = r->getNo(r->getNumChaves());
    p->getPai()->setValor(posicao, vet[num/2]);
    for (int j = 0; j < num/2; j++) {
        p->setValor(j, vet[j]);
        setRelacao(p, j, vetNo[j]);
    }
    setRelacao(p, num/2, vetNo[num/2]);
    for (int j = (num/2) + 1; j < num; j++) {
        r->setValor(j - (num/2) - 1, vet[j]);
        setRelacao(r, j - (num/2) - 1, vetNo[j]);
    }
    setRelacao(r, num - (num/2) - 1, vetNo[num]);
    p->setNumChaves(num/2);
    r->setNumChaves(num - (num/2) - 1); // divisao inteira
}

void ArvoreB::verificacaoBraba(No* p) {
    if (p != this->raiz) {
        int posicaoNoPai = ProcuraNoPai(p);
        if (posicaoNoPai != p->getPai()->getNumChaves()) {
            if (p->getNumChaves() + p->getPai()->getNo(posicaoNoPai + 1)->getNumChaves() < 2 * d) {
                if (p->getBool())
                    ConcatenaNosFolhas(p, p->getPai()->getNo(posicaoNoPai + 1));
                else
                    ConcatenaNosInternos(p, p->getPai()->getNo(posicaoNoPai + 1));
                
            }
            else if (posicaoNoPai != 0) {
                if (p->getNumChaves() + p->getPai()->getNo(posicaoNoPai - 1)->getNumChaves() < 2 * d) {
                    if (p->getBool())
                        ConcatenaNosFolhas(p->getPai()->getNo(posicaoNoPai - 1), p);
                    else
                        ConcatenaNosInternos(p->getPai()->getNo(posicaoNoPai - 1), p);
                }
                else {
                    if (p->getBool())
                        RedistribuiNoFolha(p, p->getPai()->getNo(posicaoNoPai + 1));
                    else
                        RedistribuiNoInterno(p, p->getPai()->getNo(posicaoNoPai + 1));
                }
            } else {
                if (p->getBool())
                    RedistribuiNoFolha(p, p->getPai()->getNo(posicaoNoPai + 1));
                else
                    RedistribuiNoInterno(p, p->getPai()->getNo(posicaoNoPai + 1));
            }
        } else if (p->getNumChaves() + p->getPai()->getNo(posicaoNoPai - 1)->getNumChaves() < 2 * d) {
            if (p->getBool())
                ConcatenaNosFolhas(p->getPai()->getNo(posicaoNoPai - 1), p);
            else
                ConcatenaNosInternos(p->getPai()->getNo(posicaoNoPai - 1), p);
        } else {
            if (p->getBool())
                RedistribuiNoFolha(p->getPai()->getNo(posicaoNoPai - 1), p);
            else
                RedistribuiNoInterno(p->getPai()->getNo(posicaoNoPai - 1), p);
        }
    }
}

void ArvoreB::PrimeiraRemocao(int valor, No* p, int posicao) {
    for (int k = posicao; k < p->getNumChaves() - 1; k++)
        p->setValor(k, p->getValor(k + 1));
    p->setNumChaves(p->getNumChaves() - 1);
    if (p->getNumChaves() < d) {
        verificacaoBraba(p);
    }
}

void ArvoreB::remove(int valor, unsigned int* comp) {
    int posicao;
    bool result;
    No* p = new No();
    p = BuscaValor(valor, &posicao, this->raiz, &result, comp);
    if (result == true) {
        if (p->getBool() == false) {
            int novoValor;
            No* ptt = new No();
            ptt = getMaiorMaisProximo(valor, posicao, p, &novoValor);
            p->setValor(posicao, novoValor);
            valor = novoValor;
            posicao = 0;
            p = ptt;
        }
        PrimeiraRemocao(valor, p, posicao);
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