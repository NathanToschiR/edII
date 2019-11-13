#include <iostream>
#include "../include/arvoreRN.h"
#include "../include/noRN.h"

int main() {
    arvoreRN* arv = new arvoreRN();

    arv->inserirValor(5);
    arv->inserirValor(10);
    arv->inserirValor(2);
    arv->inserirValor(1);
    arv->inserirValor(8);
    arv->imprimirArv();
    return 0;
}