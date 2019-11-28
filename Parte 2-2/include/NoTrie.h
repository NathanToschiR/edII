#ifndef NOTRIE_H
#define NOTRIE_H
#include <iostream>
#include <string>

using namespace std;

class NoTrie {
    public: 
        NoTrie();
        ~NoTrie();
        float getFreq();
        void setFreq(float freq);
        char getLetra();
        void setLetra(char letra);
        string getHuff();
        void setHuff(string huff);
        NoTrie* getFilhoEsq();
        NoTrie* getFilhoDir();
        void setFilhoEsq(NoTrie* noFilhoEsq);
        void setFilhoDir(NoTrie* noFilhoDir);
    
    private:
        float freq;
        char letra;
        string huff;
        NoTrie* FilhoEsq;
        NoTrie* FilhoDir;

};

#endif //NOTRIE_H