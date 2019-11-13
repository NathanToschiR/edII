#include <iostream>
#include "NoQuad.h"
#include "ArvoreQuad.h"
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

int main()
{
    ArvoreQuad Arvore;

    Arvore.insere(30, 45);
    Arvore.insere(35, 50);
    Arvore.insere(2, 30);



    if(Arvore.busca(35, 50) != NULL){
        cout << "ACHOU!" << endl;
    }

    if(Arvore.busca(80,50) == NULL){
        cout << "NAO ACHOU" << endl;
    }



    return 0;
}
