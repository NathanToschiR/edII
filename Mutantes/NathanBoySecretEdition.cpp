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
#include "ArvoreB20.h"

using namespace std;

struct userId {
    string user;
    unsigned long chave;
    int id;
} ;

void trocar(int* a, int* b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
} // criada função troca para simplificar os códigos

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

int testeLeitura(fstream* leitura, userId* vet, int j) {
    string str;
    getline(*leitura, str, ',');
    getline(*leitura, str, ',');
    vet[j].user = str;
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

void medias11(int grupo, double *vetDadosInsercao, double *vetDadosBusca, userId *vetConj){

    cout << "Entrou no media" << endl;
    int r;
    int c = 0;
    cout << "Grupo: " << grupo << "X = 1" << endl;   //Cria a arvore escolhida
    arvoreRN* arv = new arvoreRN();

    cout << "Criou o vet teste e arvore" << endl;

    for(int i = 0; i < 5; i++){              //ele deve fazer isso 5 vezes, como pedido
        cout << "Entrou no For" << i+1 << "do media" << endl;
        c = 0;

        auto i1 = std::chrono::high_resolution_clock::now();    //comeca a contar
        while(c++ < grupo) {                 //faz a insercao na arvore
            arv->inserirValor(vetConj[i].chave, vetDadosInsercao);
        }
        auto i2 = std::chrono::high_resolution_clock::now();    //termina de contar
        auto durationInsercao = std::chrono::duration_cast<std::chrono::microseconds>( i2 - i1 ).count();
        cout << "Specialization  " << durationInsercao << endl;
        vetDadosInsercao[2] = vetDadosInsercao[2] + durationInsercao;

        cout << endl;

        auto b1 = std::chrono::high_resolution_clock::now();    //comeca a contar
        for(c = 0; c < grupo; c++){
            arv->busca(vetConj[i].chave, &vetDadosBusca[0]);
        }
        auto b2 = std::chrono::high_resolution_clock::now();    //termina de contar
        auto durationBusca = std::chrono::duration_cast<std::chrono::microseconds>( b2 - b1 ).count();
        cout << "Specialization  " << durationBusca << endl;
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

void medias12(int grupo, double *vetDadosInsercao, double *vetDadosBusca, userId *vetConj){

    cout << "Entrou no media" << endl;
    int r;
    int c = 0;
    cout << "Grupo: " << grupo << "X = 2" << endl;   //Cria a arvore escolhida
    ArvoreB* arv = new ArvoreB();

    cout << "Criou o vet teste e arvore" << endl;

    for(int i = 0; i < 5; i++){              //ele deve fazer isso 5 vezes, como pedido
        cout << "Entrou no For" << i+1 << "do media" << endl;
        c = 0;

        auto i1 = std::chrono::high_resolution_clock::now();    //comeca a contar
        while(c++ < grupo) {                 //faz a insercao na arvore
            arv->inserirValor(vetConj[i].chave, &vetDadosInsercao[1], &vetDadosInsercao[0]);
        }
        auto i2 = std::chrono::high_resolution_clock::now();    //termina de contar
        auto durationInsercao = std::chrono::duration_cast<std::chrono::microseconds>( i2 - i1 ).count();
        vetDadosInsercao[2] = vetDadosInsercao[2] + durationInsercao;

        cout << endl;

        auto b1 = std::chrono::high_resolution_clock::now();    //comeca a contar
        for(c = 0; c < grupo; c++){
            arv->busca(vetConj[i].chave, &vetDadosBusca[0]);
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

    return;
}

void medias13(int grupo, double *vetDadosInsercao, double *vetDadosBusca, userId *vetConj){

    cout << "Entrou no media" << endl;
    int r;
    int c = 0;
    cout << "Grupo: " << grupo << "X = 3" << endl;   //Cria a arvore escolhida
    ArvoreB20* arv = new ArvoreB20();

    cout << "Criou o vet teste e arvore" << endl;

    for(int i = 0; i < 5; i++){              //ele deve fazer isso 5 vezes, como pedido
        cout << "Entrou no For" << i+1 << "do media" << endl;
        c = 0;

        auto i1 = std::chrono::high_resolution_clock::now();    //comeca a contar
        while(c++ < grupo) {                 //faz a insercao na arvore
            arv->inserirValor(vetConj[i].chave, &vetDadosInsercao[1], &vetDadosInsercao[0]);
        }
        auto i2 = std::chrono::high_resolution_clock::now();    //termina de contar
        auto durationInsercao = std::chrono::duration_cast<std::chrono::microseconds>( i2 - i1 ).count();
        vetDadosInsercao[2] = vetDadosInsercao[2] + durationInsercao;

        cout << endl;

        auto b1 = std::chrono::high_resolution_clock::now();    //comeca a contar
        for(c = 0; c < grupo; c++){
            arv->busca(vetConj[i].chave, &vetDadosBusca[0]);
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


    return;
}

void analisaParte21(userId *vetregistro, int tamanho, int x){

    fstream entrada("entrada.txt");
    fstream saidaInsercao("saidaInsercao.txt", ios::app);
    fstream saidaBusca("saidaBusca.txt", ios::app);

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

        double vetDadosInsercao[3];
        double vetDadosBusca[3];
        int i, j;

        for(i = 0; i < k; i++){          //para cada conjunto, a analise sera feita
            cout << "For numero " << i << endl;
            for(j = 0; j < 3; j++){
                vetDadosInsercao[j] = 0;         //zera o vetor de dados
                vetDadosBusca[j] = 0;
            }
            switch (x) {
            case 1:
                medias11(N[i], vetDadosInsercao, vetDadosBusca, vetregistro);
                break;
            case 2:
                medias12(N[i], vetDadosInsercao, vetDadosBusca, vetregistro);
                break;
            case 3:
                medias13(N[i], vetDadosInsercao, vetDadosBusca, vetregistro);
                break;
            }
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
    userId* vetArc = new userId[506542];

    if(leitura.is_open()) // leitura do arquivo "bgg-13m-reviews.csv"
    {
        int j = 0;
        int aleatorio;
        string str;
        getline(leitura, str); // getline para passar pela primeira linha de referência
        unsigned long user;
        for (j; j < 506541; j++)
        {
            aleatorio = random(0, 25);
            for (int k = 0; k < aleatorio; k++)
            {
                getline(leitura, str);  // joga as linhas fora (antes da linha sortida de cada bloco)
            }
            vetArc[j].id = testeLeitura(&leitura, vetArc, j);
            for(int z = 0 ; z < vetArc[j].user.length() ; z++)
                user = vetArc[j].user[z] + user;
            vetArc[j].chave = user;
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
        vetArc[j].id = testeLeitura(&leitura, vetArc, j);
        for(int z = 0 ; z < vetArc[j].user.length() ; z++)
            user = vetArc[j].user[z] + user;
        vetArc[j].chave = user;


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

    if(x == 1 || x == 2 || x == 3){
        parte21(x);
    }else{
        cout << "arvore invalida invalido" << endl;
    }

    cout <<"\n\nACABOU!!!" << endl;
    return 0;
}