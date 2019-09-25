#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <chrono>

using namespace std;

// ------------------------------------------------------------ FUNCOES AUXILIARES ------------------------------------------------------------------

struct userRatingId {
    string user;
    float rating;
    int id;
} ;

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

void trocar(int* a, int* b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
} // criada função troca para simplificar os códigos

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

// -------------------------------------------------------------- QUICKSORT RECURSIVO ---------------------------------------------------------------------

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
            if (vet[j] <= r)
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
        (*troca)++;
        auxQuickSort(vet, p, i - p, comp, troca);
        auxQuickSort(vet, i+1, p+n-i-1, comp, troca);
    }
}

void quickSort(int *vet, int n, int *vetdados) {
    int comp = 0;
    int troca = 0;
    auxQuickSort(vet, 0, n, &comp, &troca);
    cout << "\nquickSort Trocas: " << troca;
    cout << "\nquickSort Comparacoes: " << comp << "\n";
    vetdados[0] = troca + vetdados[0];
    vetdados[1] = comp + vetdados[1];
}

// ----------------------------------------------------------------- QUICKSORT MEDIANA ---------------------------------------------------------------------
int* bubblesortBom(int* vet, int n, int* troca, int* comp)
{
    for(int j = 0 ; j < n-1 ; j++)
    {
        bool teste = false;
        for(int i = 0 ; i < n-1-j; i++)
        {
            (*comp)++;
            if(vet[i] > vet[i+1])
            {
                trocar(&vet[i], &vet[i+1]);
                (*troca)++;
                teste = true;
            }
        }
        if(teste == false)
            break;
    }
    return &vet[(n-1)/2];
}

void TrocaTroca(int* a, int* b, int* c, int* troca, int* comp){
    int vetHelp[3] = {*a, *b, *c};
    int* i = bubblesortBom(vetHelp, 3, troca, comp);
    if (*i != *c)
        trocar(i, c);
}

void auxQuickSort(int *vet, int p, int n, int *comp, int* troca)
{
    if (n == 2)
    {
        (*comp)++;
        if (vet[p] > vet[p + 1])
        {
            trocar(&vet[p], &vet[p+1]);
            (*troca)++;
        }
    }
    if (n > 2)
    {
        TrocaTroca(&vet[p], &vet[p + ((n - 1 - p)/2)], &vet[p + n - 1], troca, comp);
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
        (*troca)++;
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
// -------------------------------------------------------------- QUICKSORT COM INSERTION ------------------------------------------------------------------

int insertionSort(int *vet, int n, int* troca)
{
    int aux;
    int compar = 0;
    for(int i = 1; i < n ; i++)
    {
        for(int j = i - 1; j >= 0 ; j--)
        {
            compar++;
            if(vet[j] > vet[j+1])
            {
                trocar(&vet[j], &vet[j+1]);
                (*troca)++;
            }
            else
                break;
        }
    }
    return compar;
}

void auxQuickSort(int *vet, int p, int n, int *comp, int* troca)
{
    if (n <= 10)
        insertionSort(vet, n, troca);
    else
    {
        int r = vet[p + n - 1];
        int i = p;
        for (int j = p; j < p + n - 1; j++)
        {
            if (vet[j] <= r)
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
        (*troca)++;
        auxQuickSort(vet, p, i - p, comp, troca);
        auxQuickSort(vet, i+1, p+n-i-1, comp, troca);
    }
}

void quickSort(int *vet, int n, int *vetdados) {
    int comp = 0;
    int troca = 0;
    auxQuickSort(vet, 0, n, &comp, &troca);
    cout << "\nquickSort Trocas: " << troca;
    cout << "\nquickSort Comparacoes: " << comp << "\n";
    vetdados[0] = troca + vetdados[0];
    vetdados[1] = comp + vetdados[1];
}

// ---------------------------------------------------------------------- LEITURA --------------------------------------------------------------------------

void medias11(int grupo, int *vetDados, int *vetConj){

    cout << "Entrou no media" << endl;
    int r;
    int c = 0;
    cout << "Grupo: " << grupo << endl;
    int teste[grupo];

    for(int i = 0; i < 5; i++){              //ele deve fazer isso 5 vezes, como pedido
        cout << "Entrou no For " << i+1 << " do media" << endl;
        c = 0;
        while(c++ < grupo) {                 //preenche o vetor com valores aleatorios referente a entrada
            r = randomLarge(506542);
            teste[c] = vetConj[r];
        }
        cout << endl;
        auto t1 = std::chrono::high_resolution_clock::now();    //comeca a contar
        quickSort(teste, grupo, vetDados);
        auto t2 = std::chrono::high_resolution_clock::now();    //termina de contar
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        vetDados[2] = vetDados[2] + duration;

    }

    cout << "\nSaiu do for analisa" << endl;
    vetDados[0] = vetDados[0]/5.0;  //divide todos por 5 para fazer a m�dia
    vetDados[1] = vetDados[1]/5.0;
    vetDados[2] = vetDados[2]/5.0;
    cout << "vai sair do analisa" << endl;

    return;
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

void analisaCenario21(int *vetregistro){

    fstream entrada("entrada.txt");
    fstream saida("saida.txt", ios::app);

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
    int vetData[3];
    int i, j;

    saida << "Cenario11\n";

    for(i = 0; i < k; i++){          //para cada conjunto, a analise sera feita
        cout << "\nFor numero " << i << endl;
        for(j = 0; j < 3; j++){
            vetData[j] = 0;         //zera o vetor de dados
        }
        medias11(N[i], vetData, vetregistro);   //lança na funcao que retornarao as medias
        cout << "saiu do media";
        saida << "Medias do conjunto de " << N[i] << " dados - Trocas: " << vetData[0] << ", Comparacoes: " 
        << vetData[1] << " e Tempo: " << (double)vetData[2]/1000 << "\n";  //imprime no arquivo
    }

    saida << endl;
    return;
}

void cenario2()
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


        analisaCenario21(vetArc);
    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    delete [] vetArc;

    leitura.close();
}

int main()
{
    srand(time(NULL));
    cout << "Escolha o cenario para ser testado.\n Digite '1' para o cenario 11, ou '2' para o cenario 12\n";
    int x;
    cin >> x;

    if(x == 1){
        cenario11();
    }else if(x == 2){
        cenario12();
    }else {
        cout << "cenario invalido" << endl;
    }

    cout <<"\n\nACABOU!!!" << endl;
    return 0;
}
