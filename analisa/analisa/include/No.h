#ifndef NOB_H
#define NOB_H
#include <iostream>

using namespace std;

class No {
    public:
        No();
        ~No();
        int getNumChaves();
        void setNumChaves(int val);
        int getValor(int i);
        void setValor(int i, int val);
        No* getNo(int i);
        void setNo(No* no, int i);
        No* getPai();
        void setPai(No* no);
        bool getBool();
        void setBool(bool verif);

    private:
        int* vetValor;
        No** vetNo;
        int numChaves;
        bool verificaFolha;
        No* pai;

};

#endif // NOB_H
