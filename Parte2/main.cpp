#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

struct userId {
    int idJogo;
    int id;
    string categoria;
} ;

struct categorias {
    string nome;
    float quant;
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

void frequencia(userId* vetConj, int tamanho){
    string vetCategorias[tamanho];
    int i;

    for(i = 0; i < tamanho; i++){
        vetCategorias[i] = vetConj[i].categoria;
    }

    categorias vetCat[tamanho];
    int j = 0;

    for(i = 0; i < tamanho; i++){
        if(!estaNoVetor(vetCat, vetCategorias[i], tamanho)){
            vetCat[j].nome = vetCategorias[i];
            j++;
        }
    }


    for(int k = 0; k < j; k++){
        for(i = 0; i < tamanho; i++){
            if(vetCategorias[i] == vetCat[k].nome){
                vetCat[k].quant++;
            }
        }
        vetCat[k].freq = (vetCat[k].quant/((float)(tamanho)))*100.0;

    }

    for(i = 0; i < j; i++){

        cout << "Categoria: " << vetCat[i].nome << " /Quantidade: " << vetCat[i].quant << " /Frequencia: " << vetCat[i].freq << "%"<< endl;

    }

    return;

}

void leitura(userId* vetConj){
    fstream leitura("games_detailed_info.csv");

     if(leitura.is_open()) // leitura do arquivo "bgg-13m-reviews.csv"
    {
        int j = 0;
        int aleatorio;
        string str;
        getline(leitura, str); // getline para passar pela primeira linha de referência
        for (j; j < 17062; j++)  // Passagem dos ids para o vetor auxiliar vetConj
        {
            getline(leitura, str, ',');
            vetConj[j].id = stoi(str);
            cout << vetConj[j].id << "  ";
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
                getline(leitura, str,']');
                getline(leitura, str, ','); // ver aq
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
            cout << str << "  ";
            if (j == 2704)
                vetConj[j].idJogo = 132497;
            if (j == 10833)
                vetConj[j].idJogo = 84913;
            if (j != 2704 && j != 10833)
                vetConj[j].idJogo = stoi(str);
            getline(leitura, str);
            cout << endl;
        }
    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    leitura.close();

}

int main() {
    //fstream saida("fuck.txt", ios::app);
    userId* vetConj = new userId[17063];
    leitura(vetConj);

   cout << "Saiu do leitura" << endl;

   frequencia(vetConj, 17063);

    delete [] vetConj;

}
