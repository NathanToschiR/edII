#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

struct userIds {
    int idJogo;
    int id;
    string categoria;
} ;

struct categorias {
    string nome;
    float quant = 1;
    double freq;
};

bool procuraVirgula(string str) {
    for (int k = 0; k < str.length(); k++) {
        if (str[k] == ']') {
            return 1;
        }
    }
    return 0;
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

bool denovo(string str) {
    int j = 0;
    for (int k = 0; k < str.length(); k++) {
        if (str[k] == '[')
            j++;
        if (j > 1)
            return 1;
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

bool estaNoVetor(categorias* vetCat, string categoria, int tam){
    for(int i = 0; i < tam; i++){
        if(vetCat[i].nome == categoria){
            return true;
        }
    }
    return false;
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

void inicializarHash(categorias* hash, int N)
{
    for (int i = 0 ; i < N ; i++)
    {
        hash[i].nome = "";
        hash[i].freq = 0;
    }
}

void inserirQuadratico(categorias* vetCategorias, int nVet, unsigned long* vetDados) {
    int N = primoPosterior(nVet);
    categorias* hash = new categorias[N];
    inicializarHash(hash, N);
    int nome;

    for(int i = 0; i < nVet; i++)
    {
        nome = 0;
        for(int z = 0 ; z < vetCategorias[i].nome.length() ; z++)
        {
            nome = vetCategorias[i].nome[z] + nome;
        }
        unsigned long chave = vet[i].id + nome;
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
                compar++;
            }
        }
        hash[posicao].nome = vetCategorias[i].nome;
        hash[posicao].quant = vetCategorias[i].quant;
        hash[posicao].freq = vetCategorias[i].freq;
        vetDados[0] = vetDados[0] + compar;
    }

    delete [] hash;
}

void pesquisarCategoria(categorias* categoria)
{}

void frequencia(userIds* vetConj, int tamanho){
    categorias vetCategorias[85];
    fstream saida("fuck.txt", ios::app);
    string strAux ("Comeco");
    string str = strAux;
    int contador = 0, superContador = 0; //zero da um a mais pois
    for (int k = 0; k < 17062; k++) {
        saida << vetConj[k].categoria;
        saida << ',';
    }
    saida.close();
    fstream leitura("fuck.txt");
    while(!leitura.eof()) {
        getline(leitura, str, ',');
        if (!estaNoVetor(vetCategorias, str, contador)) {
            vetCategorias[contador].nome = str;
            contador++;
        }
        else {
            for (int h = 0; h < contador; h++) {
                if (vetCategorias[h].nome == str)
                    vetCategorias[h].quant++;
            }
        }
        superContador++;
    }
    cout << contador << "  " << superContador << endl;

    for(int i = 0; i < contador - 1; i++){
        vetCategorias[i].freq = (vetCategorias[i].quant/((float)(superContador - 1)))*100.0;
        cout << "Categoria: " << vetCategorias[i].nome << " /Quantidade: " << vetCategorias[i].quant << " /Frequencia: " << vetCategorias[i].freq << "%"<< endl;
    }


    return;

}

void leitura(userIds* vetConj){
    fstream leitura("games_detailed_info.csv");

     if(leitura.is_open()) // leitura do arquivo "games_detailed_info.csv"
    {
        int j = 0;
        string str, strAux;
        getline(leitura, str); // getline para passar pela primeira linha de referência
        for (j; j < 17062; j++)  // Passagem dos ids para o vetor auxiliar vetConj
        {
            getline(leitura, str, ',');
            vetConj[j].id = stoi(str);
            for (int k = 0; k < 16; k++){
                getline(leitura, str, ',');
            }
            getline(leitura, str, ',');
            if (str[0] == '"' && !procuraVirgula(str)) {
                getline(leitura, str, ']');
                getline(leitura, str, ',');
            }
            getline(leitura, str, ',');
            getline(leitura, str, ',');
            getline(leitura, str, ',');
            getline(leitura, str, ',');
            if (str[0] == '"' && !procuraVirgula(str)) {
                getline(leitura, str, ']');
                getline(leitura, str, ',');
            }
            getline(leitura, str, ',');
            if (str[0] == '"' && !procuraVirgula(str)) {
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
                if (denovo(str)) {
                    getline(leitura, str, '"');
                    getline(leitura, str, ',');
                }
                if (str[0] == '"' && !procuraVirgula(str)) {
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

int main() {
    fstream saida("fuck.txt", ios::app);
    userIds* vetConj = new userIds[17063];
    leitura(vetConj);

    cout << "Saiu do leitura" << endl;

    frequencia(vetConj, 17063);

    delete [] vetConj;

}
