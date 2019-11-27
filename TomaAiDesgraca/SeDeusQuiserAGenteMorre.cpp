#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include "HuffmanTrie.h"
#include "NoTrie.h"

using namespace std;

void trocaString(string* a, string* b)
{
    string aux;
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

bool procuraChave(string str) {
    for (int k = 0; k < str.length(); k++) {
        if (str[k] == ']') {
            return 1;
        }
    }
    return 0;
}

bool VerificaAspas(string str) {
    int j = 0;
    for (int k = 0; k < str.length(); k++) {
        if (str[k] == '"')
            j++;
    }
    if (j % 2 == 0)
        return 0;
    else
        return 1;
}

vector<int> codificacaoLZW(string sequencia)
{
    if(sequencia != "")
    {
        string str, c;
        vector<string> dic;
        vector<int> codificacao;
        vector<string>::iterator it;
        vector<string>::iterator it2;

        int i = 0;
        int cont = 0;
        string strAux;

        for(i ; i < 256 ; i++)
        {
            strAux = i;
            dic.push_back(strAux);
        }

        str = sequencia[0];
        cont++;
        while(cont <= sequencia.length())
        {
            c = sequencia[cont];
            it = find(dic.begin(), dic.end(), str+c);
            it2 = find(dic.begin(), dic.end(), str);

            if(find(dic.begin(), dic.end(), str+c) != dic.end()) // ou seja, encontrou str+c no dic
            {
                str = str+c;
            }
            else
            {
                strAux = str + c;
                codificacao.push_back(std::distance(dic.begin(), it2)); // posicao da str no dicionario
                dic.push_back(strAux);
                str = c;
            }
            cont++;
        }

        return codificacao;
    }
    else
    {
        cout << "ERRO: SEQUENCIA VAZIA" << endl;
        exit(1);
    }
}

void PreProcessamentoDescricoes(string* vetConj){
    fstream leitura("games_detailed_info.csv");

    if(leitura.is_open()) // leitura do arquivo "games_detailed_info.csv"
    {
        int j = 0;
        string str, strAux;
        getline(leitura, str); // getline para passar pela primeira linha de referência
        for (j; j < 17062; j++)  // Passagem dos ids para o vetor auxiliar vetConj
        {
            for (int k = 0; k < 17; k++){
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
            for (int k = 0; k < 10; k++) {
                getline(leitura, str, ',');
                if (str[0] == '"' && !procuraChave(str)) {
                    getline(leitura, str, ']');
                    getline(leitura, str, ',');
                }
            }
            getline(leitura, str, ',');
            if (VerificaAspas(str)) {
                getline(leitura, strAux, ',');
                str = str + strAux;
                while(!VerificaAspas(strAux)) {
                    getline(leitura, strAux, ',');
                    str = str + strAux;
                }
            }
            vetConj[j] = str;
            getline(leitura, str);
        }
    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    leitura.close();
}

void AlgoritmoDeHuffman(string* vetAux, int grupo, unsigned int *vetDados) {
    HuffmanTrie* trie = new HuffmanTrie();
    string stringCodificada ("");
    int taxaDeComp = 0;
    int armazen = 0;
    for (int i = 0; i < grupo; i++) {
        trie->ConstroiHuffmanTrie(vetAux[i], vetAux[i].length());
        for (int j = 0; j < vetAux[i].length(); j++) {
            stringCodificada = stringCodificada + trie->AchaCodigo(vetAux[i][j]);
        }
        taxaDeComp = taxaDeComp + (stringCodificada.length() / (64 * vetAux[i].length()));
        armazen = armazen + (stringCodificada.length() / 8);
    }
    vetDados[0] = vetDados[0] + (taxaDeComp / grupo);
    vetDados[1] = vetDados[1] + (armazen / grupo);
}

void AlgoritmoLZW(string* vetAux, int grupo, unsigned int *vetDados) {
    vector<int> codigo;
    int taxaDeComp = 0;
    int armazen = 0;
    for (int i = 0; i < grupo; i++) {
        codigo = codificacaoLZW(vetAux[i]);
        taxaDeComp = taxaDeComp + (codigo.size() / vetAux[i].length());
        armazen = armazen + (codigo.size() * 8);
    }
    vetDados[3] = vetDados[3] + (taxaDeComp / grupo);
    vetDados[4] = vetDados[4] + (armazen / grupo);
}

void medias2(int grupo, unsigned int *vetDados, string *vetConj){
    int r;
    int c = 0;
    string* vetAux = new string[grupo];

    for(int i = 0; i < 5; i++){            //ele deve fazer isso 5 vezes, como pedido
        c = 0;
        while(c < grupo) {                 //preenche o vetor com valores aleatorios referente a entrada
            r = randomLarge(17061 - c);                  // Para nao haver repeticoes no vetor que iremos ordenar (vetAux), quando geramos um numero
            vetAux[c] = vetConj[r];                        // aleatorio, passamos o elemento correspondente a essa posicao para vetAux e trocamos este elemento,
            trocaString(&vetConj[r], &vetConj[17061 - c]);    // no vetConj, com o ultimo elemento do vetor e geramos um numero aleatorio entre 0 e 1013082 - c,
            c++;                                           // para q nao coletemos o mesmo valor uma outra vez
        }
        auto t1 = std::chrono::high_resolution_clock::now();    //comeca a contar o tempo

        AlgoritmoDeHuffman(vetAux, grupo, vetDados);

        auto t2 = std::chrono::high_resolution_clock::now();    //termina de contar o tempo
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        vetDados[2] = vetDados[2] + duration;
/*

        t1 = std::chrono::high_resolution_clock::now();    //comeca a contar o tempo

        AlgoritmoLZW(vetAux, grupo, vetDados);

        t2 = std::chrono::high_resolution_clock::now();    //termina de contar o tempo
        duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        vetDados[5] = vetDados[5] + duration;*/

    }

    vetDados[0] = vetDados[0]/5.0;  //divide todos por 5 para fazer a media
    vetDados[1] = vetDados[1]/5.0;
    vetDados[2] = vetDados[2]/5.0;

    return;
}

void analisaCenario2(string* vetConj){

    fstream entrada("entradaExperimental.txt");
    fstream saida("saidaExperimental.txt", ios::app);

    string enes, conj;
    int k = 0;

    getline(entrada, conj);              //le o numero de conjuntos que serao gerados a partir do arquivo de entrada
    int numGrupo = stoi(conj);
    cout << "\nConjunto: " << numGrupo << endl;
    int N[numGrupo];

    getline(entrada, enes);             //cria um vetor com a quantidade que cada conjunto deverá ter (N[0] = 1000, N[1] = 5000, ...)
    while(numGrupo > 0){
        N[k] = stoi(enes);
        numGrupo--;
        k++;
        getline(entrada, enes);
    }


    unsigned int vetDados[6];    // Vetor que armazena as metricas (numero de comparacoes e trocas, tempo)
    int i, j;

    saida << "Parte 2 - 2\n";

    for(i = 0; i < k; i++){          //para cada conjunto, a analise sera feita
        for(j = 0; j < 6; j++){
            vetDados[j] = 0;         //zera o vetor de dados
        }
        medias2(N[i], vetDados, vetConj);   //lança na funcao que retornarao as medias
        saida << "Algoritmo de Huffman: " << endl;
        saida << "Medias do conjunto de " << N[i] << " dados - Taxa de Compressao: " << vetDados[0] << ", Armazenamento em Disco: " 
        << vetDados[1] << " e Tempo: " << (double)vetDados[2]/1000 << "\n";  //imprime no arquivo
        saida << "Algoritmo LZW: " << endl;
        saida << "Medias do conjunto de " << N[i] << " dados - Taxa de Compressao: " << vetDados[3] << ", Armazenamento em Disco: " 
        << vetDados[4] << " e Tempo: " << (double)vetDados[5]/1000 << "\n";  //imprime no arquivo
    }

    saida << endl;
    return;
}

int main()
{
    srand(time(NULL));
    string* vetAux = new string[17062];


    PreProcessamentoDescricoes(vetAux);

    analisaCenario2(vetAux);


    cout << "ACABOU!!!";
    
    delete [] vetAux;
    return 0;
}