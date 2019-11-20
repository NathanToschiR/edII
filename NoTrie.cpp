#include <iostream>
#include "NoTrie.h"

using namespace std;

NoTrie::NoTrie() {
    this->freq = 0;
    this->FilhoEsq = NULL;
    this->FilhoDir = NULL;
}

NoTrie::~NoTrie() {

}

float NoTrie::getFreq() {
    return this->freq;
}

void NoTrie::setFreq(float freq) {
    this->freq = freq;
}

NoTrie* NoTrie::getFilhoEsq() {
    return this->FilhoEsq;
}

NoTrie* NoTrie::getFilhoDir() {
    return this->FilhoDir;
}

void NoTrie::setFilhoEsq(NoTrie* noFilhoEsq) {
    this->FilhoEsq = noFilhoEsq;
}

void NoTrie::setFilhoDir(NoTrie* noFilhoDir) {
    this->FilhoDir = noFilhoDir;
}