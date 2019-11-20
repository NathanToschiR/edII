
#include <iostream>

using namespace std;

class NoTrie {
    public: 
        NoTrie();
        ~NoTrie();
        float getFreq();
        void setFreq(float freq);
        NoTirie* getFilhoEsq();
        NoTirie* getFilhoDir();
        void setFilhoEsq(NoTrie* noFilhoEsq);
        void setFilhoDir(NoTrie* noFilhoDir);
    
    private:
        float freq;
        NoTrie* FilhoEsq;
        NoTrie* FilhoDir;

};