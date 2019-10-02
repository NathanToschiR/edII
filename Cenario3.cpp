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

// ---------------------------------------------------------------------- COUNTINGSORT ----------------------------------------------------------------------

void countingSort(int* vet, int n)
{
    int vetOcorrencias[13170075]; // 272409 maior ID do arquivo
    int* vetAux = new int[n];

    for(int i = 0 ; i < 13170075 ; i++)
    {
        vetOcorrencias[i] = 0; 
    } // zerando todas as ocorrencias no vetor de ocorrencias

    for(int i = 0 ; i < n ; i++)
    {
        (vetOcorrencias[vet[i]])++; 
    } // vou na posicao do vetOcorrencias referente ao ID do vet e incremento 1 na ocorrencia dele

    for(int i = 1 ; i < 13170075 ; i++)
    {
        vetOcorrencias[i] += vetOcorrencias[i-1]; 
    } // somo as ocorrencias para saber quantos elementos sao menores ou iguais ao elemento i

    for(int i = n ; i >= 0 ; i--)
    {
        vetAux[vetOcorrencias[vet[i]]-1] = vet[i]; // vet[i]-1 pois o vetor vai do indice 0 a n-1
        vetOcorrencias[vet[i]]--; // decremeneto um na ocorrencia do elemento pois ja inseri ele no vetAux
    }

    for(int i = 0 ; i < n ; i++)
    {
        vet[i] = vetAux[i];
    }

    delete [] vetAux;
}

// --------------------------------------------------------------------INSERTIONSORT -----------------------------------------------------------------------

void insertionSort(int *vet, int n, unsigned int *vetdados) {
    int comp = 0;
    int troca = 0;
    for(int i = 1; i < n ; i++)
    {
        for(int j = i - 1; j >= 0 ; j--)
        {
            comp++;
            if(vet[j] > vet[j+1])
            {
                troca++;
                trocar(&vet[j], &vet[j + 1]);
            }
            else
                break;
        }
    }
    cout << "\nquickSort Trocas: " << troca;
    cout << "\nquickSort Comparacoes: " << comp << "\n";
    vetdados[0] = troca + vetdados[0];
    vetdados[1] = comp + vetdados[1];
}

// --------------------------------------------------------------------- MERGESORT -------------------------------------------------------------------------

void Intercala(int *vet, int inicio, int meio, int fim, int *vet1, int* comp) {
    int i = inicio;
    int j = meio + 1;
    int k = 0;
    while (i < meio + 1 && j <= fim){
        (*comp)++;
        if (vet[i] < vet[j]){
            vet1[k] = vet[i];
            i++;
        }
        else{
            vet1[k] = vet[j];
            j++;
        }
        k++;
    }
    if (i == meio + 1) {
        for (j; j <= fim; j++) {
            vet1[k] = vet[j];
            k++;
        }
    }
    else {
        for (i; i < meio + 1; i++) {
            vet1[k] = vet[i];
            k++;
        }
    }
    i = inicio;
    for (k = 0; k <= fim - inicio; k++) {
        vet[i] = vet1[k];
        i++;
    }
}

void auxMergeSort(int *vet, int inicio, int fim, int *vet1, int* comp) {
    if (inicio < fim)
    {
        int meio;
        meio = (inicio + fim)/2;
        auxMergeSort(vet, inicio, meio, vet1, comp);
        auxMergeSort(vet, meio + 1, fim, vet1, comp);
        Intercala(vet, inicio, meio, fim, vet1, comp);
    }
}

void MergeSort(int *vet, int n, unsigned int* vetdados) {
    int comp = 0;
    int vet1[n];
    auxMergeSort(vet, 0, n - 1, vet1, &comp);
    cout << "\nquickSort Comparacoes: " << comp << "\n";
    vetdados[1] = comp + vetdados[1];
}

// ---------------------------------------------------------------------- HEAPSORT -------------------------------------------------------------------------

void heapify(int* vet, int i, int n, int* comp, int* troca) { // Passamos o inteiro n para que não comparemos elementos com indices maiores que n.
  int l = (2*i) + 1;
  int r = (2*i) + 2;
  int maior = i;
  if (l < n) { // If para que não apliquemos este passo em um nó folha.
    (*comp)++;
    if (vet[i] < vet[l])
        maior = l;
  }
  if (r < n) { // If para que não apliquemos este passo em um nó folha.
    (*comp)++;
    if (vet[maior] < vet[r])
        maior = r;
  }
  if (maior != i) {
    (*troca)++;
    trocar(&vet[i], &vet[maior]);
    heapify(vet, maior, n, comp, troca);
  }
}

void BuildMaxHeap(int* vet, int n, int* comp, int* troca) {
  int i = (n/2) - 1;
  for (i; i >= 0; i--) {
    heapify(vet, i, n, comp, troca);
  }
}

void HeapSort(int* vet, int n, unsigned int *vetdados) {
    int troca = 0;
    int comp = 0;
    BuildMaxHeap(vet, n, &comp, &troca);
    for (int i = n - 1; i >= 2; i--) {
        trocar(&vet[0], &vet[i]);
        BuildMaxHeap(vet, i, &comp, &troca);
    }
    trocar(&vet[0], &vet[1]);
    troca = troca + n - 1;
    cout << "\nquickSort Trocas: " << troca;
    cout << "\nquickSort Comparacoes: " << comp << "\n";
    vetdados[0] = troca + vetdados[0];
    vetdados[1] = comp + vetdados[1];
}

// -------------------------------------------------------------- QUICKSORT COM INSERTION ------------------------------------------------------------------

int insertionSortQuick(int *vet, int n, int* troca)
{
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

void auxQuickSortInsertion(int *vet, int p, int n, int m, int *comp, int* troca)
{
    if (n <= m)
        (*comp) = (*comp) + insertionSortQuick(vet, n, troca);
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
        auxQuickSortInsertion(vet, p, i - p, m, comp, troca);
        auxQuickSortInsertion(vet, i+1, p+n-i-1, m, comp, troca);
    }
}

void quickSortInsertion(int *vet, int n, unsigned int *vetdados, int m) {
    int comp = 0;
    int troca = 0;
    auxQuickSortInsertion(vet, 0, n, m, &comp, &troca);
    cout << "\nquickSort Trocas: " << troca;
    cout << "\nquickSort Comparacoes: " << comp << "\n";
    vetdados[0] = troca + vetdados[0];
    vetdados[1] = comp + vetdados[1];
}

// ---------------------------------------------------------------------- LEITURA E CHAMADA ----------------------------------------------------------------

void medias2(int grupo, unsigned int *vetDados, int *vetConj, int q, int* vetAux){

    cout << "Entrou no media" << endl;
    int r;
    int c = 0;
    cout << "Grupo: " << grupo << endl;

    for(int i = 0; i < 5; i++){              //ele deve fazer isso 5 vezes, como pedido
        cout << "Entrou no For " << i+1 << " do media" << endl;
        c = 0;
        while(c < grupo) {                 //preenche o vetor com valores aleatorios referente a entrada
            r = randomLarge(506542);
            vetAux[c] = vetConj[r];
            trocar(&vetConj[r], &vetConj[506542 - c]);
            c++;
        }
        cout << endl;
        auto t1 = std::chrono::high_resolution_clock::now();    //comeca a contar

        switch (q) {
            case 1:
                quickSortInsertion(vetAux, grupo, vetDados, 100);
                break;
            case 2:
                insertionSort(vetAux, grupo, vetDados);
                break;
            case 3:
                MergeSort(vetAux, grupo, vetDados);
                break;
            case 4:
                HeapSort(vetAux, grupo, vetDados);
                break;
            case 5:
                countingSort(vetAux, grupo);
                break;
        }

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

void analisaCenario3(int *vetregistro, int q, int* vetAux){

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
    unsigned int vetData[3];
    int i, j;

    saida << "Cenario 3\n";

    switch (q) {
        case 1:
            saida << "QuickSort" << endl;
            break;
        case 2:
            saida << "InsetionSort" << endl;
            break;
        case 3:
            saida << "MergeSort" << endl;
            break;
        case 4:
            saida << "HeapSort" << endl;
            break;
        case 5:
            break;
    }

    for(i = 0; i < k; i++){          //para cada conjunto, a analise sera feita
        cout << "\nFor numero " << i << endl;
        for(j = 0; j < 3; j++){
            vetData[j] = 0;         //zera o vetor de dados
        }
        medias2(N[i], vetData, vetregistro, q, vetAux);   //lança na funcao que retornarao as medias
        cout << "saiu do media";
        saida << "Medias do conjunto de " << N[i] << " dados - Trocas: " << vetData[0] << ", Comparacoes: " 
        << vetData[1] << " e Tempo: " << (double)vetData[2]/1000 << "\n";  //imprime no arquivo
    }

    saida << endl;
    return;
}

void cenario3(int q, int* vetAux)
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


        analisaCenario3(vetArc, q, vetAux);
    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    delete [] vetArc;

    leitura.close();
}

int main()
{
    srand(time(NULL));
    int* vetAux = new int[500000];
    cout << "Escolha qual Algoritmo de Ordenacao sera testado.\n Digite '1' para o quicksort recursivo,'2' para o InsertionSort, '3' para o MergeSort, '4' para o HeapSort ou '5' para CountingSort\n";
    int x, y;

    cin >> x;

    switch ( x )
    {
        case 1:
            cenario3(1, vetAux);
            break;
        case 2:
            cenario3(2, vetAux);
            break;
        case 3:
            cenario3(3, vetAux);
            break;
        case 4:
            cenario3(4, vetAux);
            break;
        case 5:
            cenario3(5,vetAux);
            break;
        default:
            cout << "Valor invalido!" << endl;
            break;
    }


    cout <<"\n\nACABOU!!!" << endl;
    delete [] vetAux;
    return 0;
}
