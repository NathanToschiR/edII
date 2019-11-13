#ifndef NOQUAD_H
#define NOQUAD_H
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;


class NoQuad
{
    public:
        NoQuad();
        virtual ~NoQuad();
        int getX();
        int getY();
        void setX(int x);
        void setY(int y);
        NoQuad* getNoNL();
        NoQuad* getNoSL();
        NoQuad* getNoSO();
        NoQuad* getNoNO();
        void setNoNL(NoQuad* no);
        void setNoSL(NoQuad* no);
        void setNoSO(NoQuad* no);
        void setNoNO(NoQuad* no);
        void setNome(string nome);
        string getNome();


    private:
        int x;
        int y;
        NoQuad* NoNL;
        NoQuad* NoSL;
        NoQuad* NoSO;
        NoQuad* NoNO;
        string nome;
};

#endif // NOQUAD_H
