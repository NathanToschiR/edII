#include <iostream>
#include "../include/arvoreRN.h"
#include "../include/noRN.h"

using namespace std;

int main() {
    arvoreRN* arv = new arvoreRN();

    arv->inserirValor(50);
    arv->inserirValor(20);
    arv->inserirValor(80);
    arv->inserirValor(70);
    arv->inserirValor(75);
    arv->inserirValor(82);
    arv->inserirValor(77);
    arv->inserirValor(78);
    cout << arv->getRaiz()->getValor() << endl;
    arv->imprimirArv();
    return 0;
}
