#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

//---------------------------------------------------------- FUNCOES AUXILIARES ------------------------------------------------------------------------

struct userId {
    string user;
    int id;
} ;

struct CategoriaAuxiliar {
    int idJogo;
    string categoria;
} ;

struct CategoriaFreq {
    int quant;
    string categoria;
} ;

bool procuraChave(string str) {
    for (int k = 0; k < str.length(); k++) {
        if (str[k] == ']') {
            return 1;
        }
    }
    return 0;
}

string substitui(string str, string inicial, string final){
    //filtra as categorias
    std::string replace = inicial;

    //Find 'replace'
    std::size_t pos = str.find(replace);

    //If it found 'replace', replace it with "night"
    if (pos != std::string::npos)
    str.replace(pos, replace.length(), final);
    return str;
}

void trocarCategorias(CategoriaFreq* a, CategoriaFreq* b)
{
    CategoriaFreq aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void trocarAvaliacoes(userId* a, userId* b)
{
    userId aux;
    aux = *a;
    *a = *b;
    *b = aux;
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

bool checacaract(string str) {
    int j = 0;
    for (int k = 0; k < str.length(); k++) {
        if (str[k] == '[')
            j++;
        if (j > 1)
            return 1;
    }
    return 0;
}

int primoPosterior(int valor)
{
	int candidatoADivisor, resto;
    bool ehPrimo;

    candidatoADivisor = 2;

    ehPrimo = false; // Supomos que o valor seja primo de inicio

    if (valor <= 1)
    {
        cout << "ERRO: VALOR INVALIDO";
    }

    while (candidatoADivisor <= (valor / 2) && ehPrimo != true)
    {
        resto = valor % candidatoADivisor;
        if (resto == 0)
        {
            ehPrimo = false;
            valor++;
            candidatoADivisor = 2;
        } // se nao for primo, pego o valor logo posterior ao valor inserido como argumento e faco os testes desde o inicio
          // para checar se esse sim eh primo
        candidatoADivisor++;
    }
    return valor;
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

//------------------------------------------------------------------ PRE-PROCESSAMENTO -------------------------------------------------------------------------

void PreProcessamentoCategorias(CategoriaAuxiliar* vetConj){
    fstream leitura("games_detailed_info.csv");

    if(leitura.is_open()) // leitura do arquivo "games_detailed_info.csv"
    {
        int j = 0;
        string str, strAux;
        getline(leitura, str); // getline para passar pela primeira linha de referência
        for (j; j < 17062; j++)  // Passagem dos ids para o vetor auxiliar vetConj
        {
            getline(leitura, str, ',');
            for (int k = 0; k < 16; k++){
                getline(leitura, str, ',');
            }
            getline(leitura, str, ',');
            if (str[0] == '"' && !procuraChave(str)) {
                getline(leitura, str, ']');
                getline(leitura, str, ',');
            }
            getline(leitura, str, ',');
            getline(leitura, str, ',');
            getline(leitura, str, ',');
            getline(leitura, str, ',');
            if (str[0] == '"' && !procuraChave(str)) {
                getline(leitura, str, ']');
                getline(leitura, str, ',');
            }
            getline(leitura, str, ',');
            if (str[0] == '"' && !procuraChave(str)) {
                getline(leitura, strAux,']');
                str = str + ',' + strAux;
                getline(leitura, strAux, ','); // ver aq
                str = str + ']';
            }

            str = substitui(str, "Children's Game", "Childrens Game");
            str = substitui(str, "Childrens Game", "'Childrens Game'");

            str.erase(std::remove(str.begin(), str.end(), '['), str.end());
            str.erase(std::remove(str.begin(), str.end(), ']'), str.end());
            str.erase(std::remove(str.begin(), str.end(), '"'), str.end());
            str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

            vetConj[j].categoria = str;
            for (int k = 0; k < 7; k++) {
                getline(leitura, str, ',');
                if (checacaract(str)) {
                    getline(leitura, str, '"');
                    getline(leitura, str, ',');
                }
                if (str[0] == '"' && !procuraChave(str)) {
                    getline(leitura, str, ']');
                    getline(leitura, str, ',');
                }
            }
            getline(leitura, str, ']');
            getline(leitura, str, ',');
            getline(leitura, str, ',');
            if (str[0] == '"') {
                getline(leitura, str, '"');
                getline(leitura, str, ',');
                while (checagem(str)) {
                    getline(leitura, str, '"');
                    getline(leitura, str, ',');
                }
            }
            getline(leitura, str, ',');
            if (j == 2704)
                vetConj[j].idJogo = 132497;
            if (j == 10833)
                vetConj[j].idJogo = 84913;
            if (j != 2704 && j != 10833)
                vetConj[j].idJogo = stoi(str);
            getline(leitura, str);
        }
    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    leitura.close();
}

void PassagemUserIdStruct(fstream* leitura, userId* vetorStruct, int i) {
    string str;
    getline(*leitura, str, ',');
    getline(*leitura, str, ',');
    vetorStruct[i].user = str;
    if (checagem(str))   // Ha users que possuem virgula, logo devemos checar se esse é o caso e passar o resto do nome para o user da Struct,
    {                    // caso contrario o getline para na virgula no meio do nome nao pega ele por completo
        getline(*leitura, str, ',');
        vetorStruct[i].user = vetorStruct[i].user + str;
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
    vetorStruct[i].id = ID;
    getline(*leitura, str);
}

void LeituraAvaliacoes(int n, userId* vetorStruct) {
    fstream leitura("bgg-13m-reviews.csv");
    userId* vetorStructAux = new userId[13170074];
    string str;
    getline(leitura, str);

    for (int k = 0; k < 13170073; k++) {
        PassagemUserIdStruct(&leitura, vetorStructAux, k);
    }
    int aleatorio;
    for (int h = 0; h < n; h++) {
        aleatorio = randomLarge(13170073 - h);
        vetorStruct[h] = vetorStructAux[aleatorio];
        trocarAvaliacoes(&vetorStructAux[aleatorio], &vetorStructAux[13170073 - h]);
    }

    delete [] vetorStructAux;
}

//------------------------------------------------------------ HASH E ALGORITMO DE SORTING ---------------------------------------------------------------------------

void insertionSort(CategoriaFreq* vet, int n) { // Como o que vamos ordenar é um vetor de 87 posicoes (categorias), já foi verificado que o desepenho do 
    for(int i = 1; i < n ; i++)                 // InsertionSort para vetores menores é mais eficiente, logo foi o algoritmo de ordenacao que usamos
    {
        for(int j = i - 1; j >= 0 ; j--)
        {
            if(vet[j].quant > vet[j+1].quant)
            {
                trocarCategorias(&vet[j], &vet[j + 1]);
            }
            else
                break;
        }
    }
}

void inicializarHashAvaliacoes(userId* hash, int N)
{
    for (int i = 0 ; i < N ; i++)
    {
        hash[i].id = -1;
        hash[i].user = "";
    }
}

void inicializarHashCategorias(CategoriaFreq* hash, int N)
{
    for (int i = 0 ; i < N ; i++)
    {
        hash[i].quant = 0;
        hash[i].categoria = "";
    }
}

void inserirQuadraticohashCategorias(CategoriaFreq* hash, string elemento, int N) {
    int categ = 0;
    for(int z = 0 ; z < elemento.length() ; z++)
    {
        categ = elemento[z] + categ;
    }
    unsigned long chave = categ;
    int posicao = chave % N;
    unsigned long j = 1;
    unsigned long compar = 0;

    while(hash[posicao].quant != 0)
    {
        if (hash[posicao].categoria != elemento){
            posicao = (chave + j*j) % N;
            j++;
        }
        else
            break;
    }

    hash[posicao].quant++;
    hash[posicao].categoria = elemento;

}

void inserirQuadratico(userId* hash, userId elemento, int N) {
    int user = 0;
    for(int z = 0 ; z < elemento.user.length() ; z++)
    {
        user = elemento.user[z] + user;
    }
    unsigned long chave = elemento.id + user;
    int posicao = chave % N;
    unsigned long j = 1;
    unsigned long compar = 0;

    if(hash[posicao].id == -1)
        compar++;
    else
    {
        while(hash[posicao].id != -1)
        {
            posicao = (chave + j*j) % N;
            j++;
        }
    }
    hash[posicao].id = elemento.id;
    hash[posicao].user = elemento.user;

}

//-----------------------------------------------------------------------------------------------------------------------------------------------

void ContagemCategorias(CategoriaFreq* hash, userId* vetAvaliacoes, int n, CategoriaAuxiliar* vetCategoriasAux) {
    string str;
    for (int k = 0; k < n; k++) {
        int j = 0;
        while (vetAvaliacoes[k].id != vetCategoriasAux[j].idJogo)
            j++;
        for (int i = 0; i < vetCategoriasAux[j].categoria.length(); i++){
            if (vetCategoriasAux[j].categoria[i] == ',') {
                inserirQuadraticohashCategorias(hash, str, 87); // Primeiro primo apos 85 (numero de categorias)
                str.clear();
            }
            else {
                str = str + vetCategoriasAux[j].categoria[i];
            }
        }
        inserirQuadraticohashCategorias(hash, str, 87);
        str.clear();
    }
    insertionSort(hash, 87);
}

int main() {
    srand(time(NULL));
    int n,m;
    cout << "Digite o numero N de avaliacoes a serem consideradas: ";
    cin >> n;
    cout << "Digite o numero M para a mostragem das M categorias mais frequentes (Lembramos que so temos 85 categorias): ";
    cin >> m;

    userId* vetorStruct = new userId[n];
    CategoriaAuxiliar* vetConj = new CategoriaAuxiliar[17062];

    LeituraAvaliacoes(n, vetorStruct);


    PreProcessamentoCategorias(vetConj);

    int N = primoPosterior(n);
    userId* hash = new userId[N];
    inicializarHashAvaliacoes(hash, N);

    for (int k = 0; k < n; k++) {
        inserirQuadratico(hash, vetorStruct[k], N);
    }


    CategoriaFreq* hashCateg = new CategoriaFreq[87];
    inicializarHashCategorias(hashCateg, 87);

    ContagemCategorias(hashCateg, vetorStruct, n, vetConj);

    for (int l = 0; l < m; l++) {
        if (hashCateg[86 - l].quant != 0)
            cout << l << "a" << hashCateg[86 - l].categoria << "   " << hashCateg[86 - l].quant << "   " << endl;
    }
}