#include <iostream>
#include "No.h"

#define d 2

using namespace std;

No::No() {
    vetValor = new int[2 * d];
    vetNo = new No*[(2 * d) + 1];
    numChaves = 0;
    verificaFolha = true;

    for (int k = 0; k < (2 * d) + 1; k++) {
        vetNo[k] = NULL;
    }
}

No::~No() {
    delete [] vetValor;
    for (int k = 0; k < (2 * d) + 1; k++) {
        delete [] vetNo[k];
    }
    delete [] vetNo;
}

int No::getValor(int i) {
    return vetValor[i];
}

void No::setValor(int i, int val) {
    vetValor[i] = val;
}

int No::getNumChaves() {
    return numChaves;
}

void No::setNumChaves(int val) {
    this->numChaves = val;
}

No* No::getNo(int i) {
    return vetNo[i];
}

void No::setNo(No* no, int i) {
    vetNo[i] = no;
}

No* No::getPai() {
    return this->pai;
}

void No::setPai(No* no) {
    this->pai = no;
}

bool No::getBool() {
    return this->verificaFolha;
}

void No::setBool(bool verif) {
    this->verificaFolha = verif;
}