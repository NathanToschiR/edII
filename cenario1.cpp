#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>

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

void quickSort(int *vet, int n) {
    int comp = 0;
    int troca = 0;
    auxQuickSort(vet, 0, n, &comp, &troca);
    cout << "\nquickSort Trocas: " << troca;
    cout << "\nquickSort Comparacoes: " << comp << "\n";
}

int random(int min, int max)
{
    int num;
    srand(time(NULL));
    num = (rand()%(max-min));

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

void testeLeituraStruct(fstream* leitura, userRatingId* vetorStruct, int i)
{
    string str;
    getline(*leitura, str, ',');
    getline(*leitura, str, ',');
    vetorStruct[i].user = str;
    if (checagem(str))
    {
        getline(*leitura, str, ',');
        vetorStruct[i].user = vetorStruct[i].user + str;
    }
    getline(*leitura, str, ',');
    vetorStruct[i].rating = stof(str);

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
    vetorStruct[i].id = stoi(str);
    getline(*leitura, str);
}


void cenario11() 
{
    fstream leitura("bgg-13m-reviews.csv");
    fstream entrada("entrada.txt");
    fstream saida("saida.txt");
    int* vetArc = new int[506542];

    if(leitura.is_open()) // leitura do arquivo "bgg-13m-reviews.csv"
    {
        int j = 0;
        int aleatorio;
        string str;
        getline(leitura, str); // getline para passar pela primeira linha de referência
        for (j; j < 506541; j++) 
        {
            aleatorio = random(0, 26);
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
        delete [] vetArc; 

    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    leitura.close();
}

void cenario12()
{
    fstream leitura("bgg-13m-reviews.csv");
    fstream entrada("entrada.txt");
    fstream saida("saida.txt");
    userRatingId* vetorStruct = new userRatingId[506542];

    if(leitura.is_open()) // leitura do arquivo "bgg-13m-reviews.csv"
    {
        int j = 0;
        int aleatorio;
        string str;
        getline(leitura, str); // getline para passar pela primeira linha de referência

        for (j; j < 506541; j++) 
        {
            aleatorio = random(0, 26);
            for (int k = 0; k < aleatorio; k++) 
            {
                getline(leitura, str);  // joga as linhas fora (antes da linha sortida de cada bloco)
            }
            testeLeituraStruct(&leitura, vetorStruct, j);
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
        testeLeituraStruct(&leitura, vetorStruct, j);

        delete [] vetorStruct; 

    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    leitura.close();
}

int main()
{
    cenario12();
    return 0;
}