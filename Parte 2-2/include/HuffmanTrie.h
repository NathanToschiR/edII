#ifndef HUFFMANTRIE_H
#define HUFFMANTRIE_H

#include <iostream>
#include "NoTrie.h"

using namespace std;

class HuffmanTrie {
    public:
        HuffmanTrie();
        ~HuffmanTrie();
        NoTrie* getRaiz();
        void setRaiz(NoTrie* raiz);
        int ConstroiHuffmanTrie(string msg, int n);
        void DefineCodigos(NoTrie* p, string str, int n, NoTrie* vet);
        string AchaCodigo(char a);

    private:
        int AchaNoVet(char letra, int n, NoTrie* vet);
        void ConstroiHuffmanTrieAux(NoTrie* vet, int n);
        NoTrie* raiz;
};

#endif //HUFFMANTRIE_H