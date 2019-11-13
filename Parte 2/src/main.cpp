#include <iostream>
#include "../include/arvoreRN.h"
#include "../include/noRN.h"

using namespace std;

int main() {
    arvoreRN* arv = new arvoreRN();

    arv->inserirValor(5);
    arv->inserirValor(10);
    arv->inserirValor(1);
    arv->inserirValor(0);
    arv->inserirValor(8);
    arv->inserirValor(2);
    arv->inserirValor(4);
    arv->inserirValor(3);
    cout << arv->getRaiz()->getValor() << endl;
    arv->imprimirArv();
    return 0;
}
