#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

struct userRatingId {
    char user;
    int rating;
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
    // gerando um número aleatório entre um intervalo de 1 a 17066 (número total de ID)
    int num;
    srand(time(NULL));
    num = (rand()%(max-min));

    return num;
}

bool TaFodaAq(string str) {
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

void cenario1()
{
    fstream leitura("bgg-13m-reviews.csv");
    fstream entrada("entrada.txt");
    fstream saida("saida.txt");

    //while(!entrada.eof()) // enquanto não termina de ler todo o arquivo "entrada.txt"
    //{
        //string strN;
        //getline(entrada, strN); // pega o valor de N dentro do arquivo de entrada e joga para a string strN
        //int qntdID = stoi(strN);
        int qntdID = 600000;
        int* vetArq = new int[qntdID];

        //for(int cont = 0 ; cont < 5 ; cont++) // 5 conjuntos pra cada valor de N
        //{
            if(leitura.is_open()) // leitura do arquivo "bgg-13m-reviews.csv"
            {
                int i = 0;
                int cont = 0;
                string str;
                getline(leitura, str); // getline para passar pela primeira linha de referência

                while(i < 600000)
                {
                    getline(leitura, str, ',');
                    getline(leitura, str, ',');
                    if (TaFodaAq(str))
                        getline(leitura, str, ',');
                    getline(leitura, str, ',');
                    getline(leitura, str, ',');
                    if(str[0] == '"')
                    {
                        if (TaFodaAq(str)) {
                            getline(leitura, str, '"');
                            getline(leitura, str, ',');
                            if (TaFodaAq(str)) {
                                while (TaFodaAq(str)) {
                                    getline(leitura, str, '"');
                                    getline(leitura, str, ',');
                                }
                            }
                        }
                    } 

                    getline(leitura, str, ',');
                    int ID = stoi(str); // -std=c++11
                    getline(leitura, str);
                    str.clear();
                    cout << "ID " << cont << ": " << ID << "\n";
                    vetArq[cont] = ID;
                    cont++;
                    i++;
                }
                cout << "its done\n";
                delete [] vetArq; 
            } else {
                cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
            }
            leitura.close();
        //}
    //}
}

int main()
{
    cenario1();
    return 0;
}
