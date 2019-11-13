#include "ArvoreQuad.h"
#include <iostream>

ArvoreQuad::ArvoreQuad()
{
    tamanho = 0;
    raiz = NULL;
}

ArvoreQuad::~ArvoreQuad()
{
    delete raiz;
}

int ArvoreQuad::getTamanho(){
    return tamanho;
}

void ArvoreQuad::setTamanho(int tam){
    tamanho = tam;
}

void ArvoreQuad::setRaiz(NoQuad* no){
    raiz = no;
}

NoQuad* ArvoreQuad::getRaiz(){
    return raiz;
}

NoQuad* ArvoreQuad::auxBusca(int x, int y, NoQuad* p){
    if(x == p->getX() && y == p->getY()){
        return p;
    }

    if(x > p->getX() && y > p->getY()){
        if(p->getNoNL() == NULL){
            return NULL;
        }else{
            return auxBusca(x, y, p->getNoNL());
        }
    }

    if(x > p->getX() && y < p->getY()){
        if(p->getNoSL() == NULL){
            return NULL;
        }else{
            return auxBusca(x, y, p->getNoSL());
        }
    }

    if(x <= p->getX() && y <= p->getY()){
        if(p->getNoSO() == NULL){
            return NULL;
        }else{
            return auxBusca(x, y, p->getNoSO());
        }
    }

    if(x <= p->getX() && y > p->getY()){
        if(p->getNoNO() == NULL){
            return NULL;
        }else{
            return auxBusca(x, y, p->getNoNO());
        }
    }
    return NULL;
}

NoQuad* ArvoreQuad::busca(int x, int y){

    NoQuad* p;

    if(getTamanho() == 0){
        return NULL;
    }

    p = raiz;
    return auxBusca(x, y, p);

}

void ArvoreQuad::auxInsere(int x, int y, NoQuad* q, NoQuad* p){

    if(x > p->getX() && y > p->getY()){
        if(p->getNoNL() == NULL){
            p->setNoNL(q);
            setTamanho(getTamanho()+1);
            return;
        }else{
           auxInsere(x, y, q, p->getNoNL());
        }
    }

    if(x > p->getX() && y < p->getY()){
        if(p->getNoSL() == NULL){
            p->setNoSL(q);
            setTamanho(getTamanho()+1);
            return;
        }else{
           auxInsere(x, y, q, p->getNoSL());
        }
    }

    if(x <= p->getX() && y <= p->getY()){
        if(p->getNoSO() == NULL){
        p->setNoSO(q);
        setTamanho(getTamanho()+1);
        return;
        }else{
            auxInsere(x, y, q, p->getNoSO());
        }
    }

    if(x <= p->getX() && y > p->getY()){
        if(p->getNoNO() == NULL){
            p->setNoNO(q);
            setTamanho(getTamanho()+1);
            return;
        }else{
            auxInsere(x, y, q, p->getNoNO());
        }
    }

    cout << "JA INSERIDO!" << endl;
    exit(1);

}

void ArvoreQuad::insere(int x, int y){

    NoQuad* p;
    NoQuad* q = new NoQuad;
    q->setX(x);
    q->setY(y);

    if(tamanho == 0){
        setRaiz(q);
        setTamanho(getTamanho()+1);
        return;
    }
    p = raiz;

    auxInsere(x, y, q, p);

    return;
}
