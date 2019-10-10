#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct userId {
    int idJogo;
    int id;
    string categoria;
} ;

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
            /*str.erase(std::remove(str.begin(), str.end(), '['), str.end());
            str.erase(std::remove(str.begin(), str.end(), ']'), str.end());
            str.erase(std::remove(str.begin(), str.end(), '"'), str.end());
            str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
*/
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

    cout << "Saiu do leitura";

   // frequencia(vetConj);

    for(int i = 0; i < 17063; i++){
        cout << vetConj[i].categoria << " ";
    }

    delete [] vetConj;

}
