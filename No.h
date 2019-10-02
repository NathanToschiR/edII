#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

using std::string;

#ifndef NO_H
#define NO_H


class No
{
    public:
        No();
        ~No();
        int getId();
        string getUser();
        No* getProx();
        void setId(int val);
        void setUser(string userr);
        void setProx(No* p);

    private:
        string user;
        int id;
        No* prox;
};

#endif // NO_H
