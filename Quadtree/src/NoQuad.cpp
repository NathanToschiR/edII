#include "NoQuad.h"

NoQuad::NoQuad()
{
    x = -1;
    y = -1;
    NoNL = NULL;
    NoSL = NULL;
    NoSO = NULL;
    NoNO = NULL;

}

NoQuad::~NoQuad()
{

}

int NoQuad::getX(){
    return x;
}

int NoQuad::getY(){
    return y;
}

void NoQuad::setX(int numero){
    x = numero;
}

void NoQuad::setY(int numero){
    y = numero;
}

NoQuad* NoQuad::getNoNL(){
    return NoNL;
}

NoQuad* NoQuad::getNoSL(){
   return NoSL;
}

NoQuad* NoQuad::getNoSO(){
    return NoSO;
}

NoQuad* NoQuad::getNoNO(){
    return NoNO;
}

void NoQuad::setNoNL(NoQuad* no){
    NoNL = no;
}

void NoQuad::setNoSL(NoQuad* no){
    NoSL = no;
}

void NoQuad::setNoSO(NoQuad* no){
    NoSO = no;
}

void NoQuad::setNoNO(NoQuad* no){
    NoNO = no;
}

string NoQuad::getNome(){
    return nome;
}

void NoQuad::setNome(string name){
    nome = name;
}


