#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <chrono>
#include "arvoreRN.h"
#include "noRN.h"
#include "No.h"
#include "ArvoreB.h"

using namespace std;

struct userRatingId {
    string user;
    float rating;
    int id;
} ;

void trocar(int* a, int* b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
} // criada função troca para simplificar os códigos

void auxQuickSort(int *vet, int p, int n, int *comp, int* troca)
{
    if (n == 2)
    {
        if (vet[p] > vet[p + 1])
        {
            trocar(&vet[p], &vet[p+1]);
            (*troca)++;
        }
        (*comp)++;
    }
    if (n > 2)
    {
        int r = vet[p + n - 1];
        int i = p;
        for (int j = p; j < p + n - 1; j++)
        {
            if (vet[j] < r)
            {
                if (j != i)
                {
                    trocar(&vet[i], &vet[j]);
                    (*troca)++;
                }
                i++;
            }
        }
        *comp = *comp + n - 1;
        vet[p + n - 1] = vet[i];
        vet[i] = r;
        auxQuickSort(vet, p, i - p, comp, troca);
        auxQuickSort(vet, i+1, p+n-i-1, comp, troca);
    }
}

void quickSort(int *vet, int n, float *vetdados) {
    int comp = 0;
    int troca = 0;
    auxQuickSort(vet, 0, n, &comp, &troca);
    cout << "\nquickSort Trocas: " << troca;
    cout << "\nquickSort Comparacoes: " << comp << "\n";
    vetdados[0] = troca + vetdados[0];
    vetdados[1] = comp + vetdados[1];
}

int random(int min, int max)
{
    int num;
    srand(time(NULL));
    num = (rand()%(max-min));

    return num;
}

int randomLarge(int max)
{
    int num;
    num = ((rand() * rand() ) % max);

    return num;
}

bool checagem(string str) {
    if (str.length() == 0)
        return 0;
    else {
        int cont = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '"')
            cont++;
        }
        if (cont % 2 == 0)
            return 0;
        else
            return 1;
    }
}

int testeLeitura(fstream* leitura) {
    string str;
    getline(*leitura, str, ',');
    getline(*leitura, str, ',');
    if (checagem(str))
    {
        getline(*leitura, str, ',');
    }
    getline(*leitura, str, ',');
    getline(*leitura, str, ',');
    if(str[0] == '"')
    {
        if (checagem(str))
        {
            getline(*leitura, str, '"');
            getline(*leitura, str, ',');
            if (checagem(str))
            {
                while (checagem(str))
                {
                    getline(*leitura, str, '"');
                    getline(*leitura, str, ',');
                }
            }
        }
    }
    getline(*leitura, str, ',');
    int ID = stoi(str); // -std=c++11
    getline(*leitura, str);
    return ID;
}

void medias11(int grupo, float *vetDadosInsercao, float *vetDadosBusca, int *vetConj, int x){

    cout << "Entrou no media" << endl;
    int r;
    int c = 0;
    cout << "Grupo: " << grupo << "X = " << x << endl;   //Cria a arvore escolhida
    if(x == 1){
        arvoreRN* arv = new arvoreRN();
    }else if(x == 2){
        ArvoreB* arv = new ArvoreB();
    }else if(x == 3){
        ArvoreB* arv = new ArvoreB();
    }else{
        cout << "ERRO: X E INVALIDO" << endl;
        exit(0);
    }

    int *teste = new int[grupo];             //cria o vetor que sera utilizado no teste
    cout << "Criou o vet teste e a vore" << endl;

    for(int i = 0; i < 5; i++){              //ele deve fazer isso 5 vezes, como pedido
        cout << "Entrou no For" << i+1 << "do media" << endl;
        c = 0;

        auto i1 = std::chrono::high_resolution_clock::now();    //comeca a contar
        while(c++ < grupo) {                 //faz a insercao na arvore
            r = randomLarge(506542);
            teste[c] = r;
            arv->inserirValor(r, vetDadosInsercao);
        }
        auto i2 = std::chrono::high_resolution_clock::now();    //termina de contar
        auto durationInsercao = std::chrono::duration_cast<std::chrono::microseconds>( i2 - i1 ).count();
        vetDadosInsercao[2] + durationInsercao;

        cout << endl;
        if(x == 1){
            noRN* p = new noRN();
        }else{
            No* p = new No();
        }

        auto b1 = std::chrono::high_resolution_clock::now();    //comeca a contar
        for(c = 0; c < grupo; c++){
            p = arv->busca(teste[c], vetDadosBusca);
        }
        auto b2 = std::chrono::high_resolution_clock::now();    //termina de contar
        auto durationBusca = std::chrono::duration_cast<std::chrono::microseconds>( b2 - b1 ).count();
        vetDadosBusca[2] = vetDadosBusca[2] + durationBusca;
        cout << "\n";
    }

    cout << "Saiu do for analisa" << endl;

    vetDadosInsercao[0] = vetDadosInsercao[0]/5.0;  //divide todos por 5 para fazer a media
    vetDadosInsercao[1] = vetDadosInsercao[1]/5.0;
    vetDadosInsercao[2] = vetDadosInsercao[2]/5.0;

    vetDadosBusca[0] = vetDadosBusca[0]/5.0;  //divide todos por 5 para fazer a media
    vetDadosBusca[1] = vetDadosBusca[1]/5.0;
    vetDadosBusca[2] = vetDadosBusca[2]/5.0;

    cout << "vai sair do analisa" << endl;

    delete [] arv;

    return;


}

void analisaParte21(int *vetregistro, int tamanho, int x){

    fstream entrada("entrada.txt");
    fstream saidaInsercao("saidaInsercao.txt");
    fstream saidaBusca("saidaBusca.txt");

    string enes, conj;
    int k = 0;

    getline(entrada, conj);                     //descobre quantos conjuntos serão gerados
    int grupo = stoi(conj);
    cout << "\nConjunto: " << grupo << endl;
    int N[grupo];

    getline(entrada, enes);             //cria um vetor com a quantidade que cada conjunto deverá ter
    while(grupo > 0){
        N[k] = stoi(enes);
        grupo--;
        k++;
        getline(entrada, enes);
    }

        cout << "Teste1.\n";

        int x;
        float vetDadosInsercao[3];
        float vetDadosBusca[3];
        int i, j;

        for(i = 0; i < k; i++){          //para cada conjunto, a analise sera feita
            cout << "For numero " << i << endl;
            for(j = 0; j < 3; j++){
                vetDadosInsercao[j] = 0;         //zera o vetor de dados
                vetDadosBusca[j] = 0;
            }
            medias11(N[i], vetDadosInsercao, vetDadosBusca, vetregistro, x);   //lança na funcao que retornarao as medias
            cout << "saiu do media";
            saidaInsercao << "Parte11\nMedias do conjunto de " << N[i] << " dados - Numero de comparacoes de chaves: " << vetDadosInsercao[0] << ", Numero de copias de registro: " <<
            vetDadosInsercao[1] << " e Tempo: " << (double)vetDadosInsercao[2]/1000 << "\n";  //imprime no arquivo de saida da insercao
            saidaBusca << "Parte11\nMedias do conjunto de " << N[i] << " dados - Numero de comparacoes de chaves: " << vetDadosBusca[0] << ", Numero de copias de registro: " <<
            vetDadosBusca[1] << " e Tempo: " << (double)vetDadosInsercao[2]/1000 << "\n";  //imprime no arquivo de saida da insercao
        }

        return;

}

void parte21(int x)
{
    fstream leitura("bgg-13m-reviews.csv");
    int* vetArc = new int[506542];

    if(leitura.is_open()) // leitura do arquivo "bgg-13m-reviews.csv"
    {
        int j = 0;
        int aleatorio;
        string str;
        getline(leitura, str); // getline para passar pela primeira linha de referência
        for (j; j < 506541; j++)
        {
            aleatorio = random(0, 25);
            for (int k = 0; k < aleatorio; k++)
            {
                getline(leitura, str);  // joga as linhas fora (antes da linha sortida de cada bloco)
            }
            vetArc[j] = testeLeitura(&leitura);
            for (int k = aleatorio + 1; k < 26; k++)
            {
                getline(leitura, str);  // joga as linhas fora (depois da linha sortida de cada bloco)
             }
        }
        aleatorio = random(0, 7);
        for (int k = 0; k < aleatorio; k++)
        {
            getline(leitura, str);  // joga as linhas fora (antes da linha sortida de cada bloco)
        }
        vetArc[j] = testeLeitura(&leitura);


        analisaParte21(vetArc, j, x);


        delete [] vetArc;

    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    leitura.close();
}

int main()
{
    int x;
    srand(time(NULL));
    cout << "Escolha qual arvore sera testada.\n Digite '1' para a ArvoreRN, '2' para a ArvoreB com d = 2 ou '3' para a ArvoreB com d = 20\n";
    cin >> x;

    if(x == 1){
        parte21(1);
    }else if(x == 2){
        parte21(2);
    }else if(x == 3){
        parte21(3);
    }else{
        cout << "arvore invalida invalido" << endl;
    }

    cout <<"\n\nACABOU!!!" << endl;
    return 0;
}
