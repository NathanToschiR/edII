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

int randomLarge(int max)  // Funcao que nos permite pegar um numero aleatorio entre 0 e 1013081
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

// -------------------------------------------------------------- QUICKSORT RECURSIVO ---------------------------------------------------------------------

void auxQuickSort(int *vet, int p, int n, int *comp, int* troca) // p é o inicio e n o numero de elementos em cada chamada recursiva do QuickSort 
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
    if (n > 2) // Se n = 1 nao é necessario nenhuma ação
    {
        int r = vet[p + n - 1]; // pivo
        int i = p;
        for (int j = p; j < p + n - 1; j++)
        {
            if (vet[j] <= r)
            {
                if (j != i) // Podemos ter i = j e isso causa problemas na troca
                {
                    trocar(&vet[i], &vet[j]);
                    (*troca)++;
                }
                i++;
            }
        }
        *comp = *comp + n - 1;    // O numero de comparaçoes a cada chamada recursiva depende apenas do numero de elementos atual (n - 1 comparacoes)
        vet[p + n - 1] = vet[i];    // Coloca pivo na sua devida posicao
        vet[i] = r;
        (*troca)++;
        auxQuickSort(vet, p, i - p, comp, troca);
        auxQuickSort(vet, i+1, p+n-i-1, comp, troca);
    }
}

void quickSort(int *vet, int n, unsigned int *vetdados) {
    int comp = 0;
    int troca = 0;
    auxQuickSort(vet, 0, n, &comp, &troca);
    cout << "\nquickSort Trocas: " << troca;
    cout << "\nquickSort Comparacoes: " << comp << "\n";
    vetdados[0] = troca + vetdados[0];
    vetdados[1] = comp + vetdados[1];
}

// ----------------------------------------------------------------- QUICKSORT MEDIANA ---------------------------------------------------------------------

int* bubblesortMediana(int* vet, int n, int* troca, int* comp) { // Funciona para k = 3 e k = 5
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

void retornaMediana3(int* a, int* b, int* c, int* troca, int* comp) { // Retorna a mediana para o QuickSort mediana com k = 3
    int vetHelp[3] = {*a, *b, *c};                                    // e coloca este elemento no final do vetor, para que este seja o pivo
    int* i = bubblesortMediana(vetHelp, 3, troca, comp);
    if (*i != *c)
        trocar(i, c);
}

void auxQuickSortMediana3(int *vet, int p, int n, int *comp, int* troca) {
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
        retornaMediana3(&vet[p], &vet[p + ((n - 1 - p)/2)], &vet[p + n - 1], troca, comp);
        int r = vet[p + n - 1];  // Pivo, que agora é a mediana retornada
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
        auxQuickSortMediana3(vet, p, i - p, comp, troca);
        auxQuickSortMediana3(vet, i+1, p+n-i-1, comp, troca);
    }
}

void retornaMediana5(int* a, int* b, int* c, int* d, int* e, int* troca, int* comp){ // Retorna a mediana para o QuickSort mediana com k = 5
    int vetHelp[5] = {*a, *b, *c, *d, *e};                                           // e coloca este elemento no final do vetor, para que este seja o pivo
    int* i = bubblesortMediana(vetHelp, 5, troca, comp);
    if (*i != *c)
        trocar(i, c);
}

void auxQuickSortMediana5(int *vet, int p, int n, int *comp, int* troca)
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
        retornaMediana5(&vet[p], &vet[(3*p + n - 2)/4], &vet[(p + n - 1)/2], &vet[(p + 3*p - 3)/4], &vet[p + n - 1], troca, comp);
        int r = vet[p + n - 1];  // Pivo, que agora é a mediana retornada
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
        auxQuickSortMediana5(vet, p, i - p, comp, troca);
        auxQuickSortMediana5(vet, i+1, p+n-i-1, comp, troca);
    }
}

void quickSortMediana(int *vet, int n, unsigned int *vetdados, int k) {
    int comp = 0;
    int troca = 0;
    if(k == 3){
        auxQuickSortMediana3(vet, 0, n, &comp, &troca);
    }else{
        auxQuickSortMediana5(vet, 0, n, &comp, &troca);
    }
    cout << "\nquickSort Trocas: " << troca;
    cout << "\nquickSort Comparacoes: " << comp << "\n";
    vetdados[0] = vetdados[0] + troca;
    vetdados[1] = vetdados[1] + comp;
}

// -------------------------------------------------------------- QUICKSORT COM INSERTION ------------------------------------------------------------------

int insertionSortQuick(int *vet, int n, int* troca)
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

void auxQuickSortInsertion(int *vet, int p, int n, int m, int *comp, int* troca)
{
    if (n <= m)    // Apenas mudamos o caso base para operarmos com o Insertion a partir do m escolhido
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

void medias2(int grupo, unsigned int *vetDados, int *vetConj, int q, int v, int* vetAux){
    int r;
    int c = 0;

    for(int i = 0; i < 5; i++){              //ele deve fazer isso 5 vezes, como pedido
        c = 0;
        while(c < grupo) {                 //preenche o vetor com valores aleatorios referente a entrada
            r = randomLarge(1013081 - c);                  // Para nao haver repeticoes no vetor que iremos ordenar (vetAux), quando geramos um numero
            vetAux[c] = vetConj[r];                        // aleatorio, passamos o elemento correspondente a essa posicao para vetAux e trocamos este elemento,
            trocar(&vetConj[r], &vetConj[1013081 - c]);    // no vetConj, com o ultimo elemento do vetor e geramos um numero aleatorio entre 0 e 1013082 - c,
            c++;                                           // para q nao coletemos o mesmo valor uma outra vez
        }
        cout << endl;
        auto t1 = std::chrono::high_resolution_clock::now();    //comeca a contar

        switch (q) {
            case 1:
                quickSort(vetAux, grupo, vetDados);
                break;
            case 2:
                quickSortMediana(vetAux, grupo, vetDados, v); // v para diferenciar k = 3 de k = 5
                break;
            case 3:
                quickSortInsertion(vetAux, grupo, vetDados, v); // v para diferenciar m = 10 de m = 100
                break;
        }

        auto t2 = std::chrono::high_resolution_clock::now();    //termina de contar
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        vetDados[2] = vetDados[2] + duration;

    }

    vetDados[0] = vetDados[0]/5.0;  //divide todos por 5 para fazer a media
    vetDados[1] = vetDados[1]/5.0;
    vetDados[2] = vetDados[2]/5.0;

    return;
}

void analisaCenario2(int *vetConj, int q, int v, int* vetAux){

    fstream entrada("entradaExperimental.txt");
    fstream saida("saidaExperimental.txt", ios::app);

    string enes, conj;
    int k = 0;

    getline(entrada, conj);                 //le o numero de conjuntos que serao gerados a partir do arquivo de entrada
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

    int x;
    unsigned int vetDados[3];    // Vetor que armazena as metricas (numero de comparacoes e trocas, tempo)
    int i, j;

    saida << "Cenario2\n";
    switch (q) {
        case 1:
            saida << "Quicksort Recursivo" << endl;
            break;
        case 2:
            saida << "Quicksort Mediana";
            if (v == 3)
                saida << " k = 3" << endl;
            else
                saida << " k = 5" << endl;
            break;
        case 3:
            saida << "Quicksort Insert";
            if (v == 10)
                saida << " m = 10" << endl;
            else
                saida << " m = 100" << endl;
            break;
    }

    for(i = 0; i < k; i++){          //para cada conjunto, a analise sera feita
        for(j = 0; j < 3; j++){
            vetDados[j] = 0;         //zera o vetor de dados
        }
        medias2(N[i], vetDados, vetConj, q, v, vetAux);   //lança na funcao que retornarao as medias
        saida << "Medias do conjunto de " << N[i] << " dados - Trocas: " << vetDados[0] << ", Comparacoes: " 
        << vetDados[1] << " e Tempo: " << (double)vetDados[2]/1000 << "\n";  //imprime no arquivo
    }

    saida << endl;
    return;
}

void cenario2(int q, int v, int* vetAux)
{
    fstream leitura("bgg-13m-reviews.csv");
    int* vetConj = new int[1013082];

    if(leitura.is_open()) // leitura do arquivo "bgg-13m-reviews.csv"
    {
        int j = 0;
        int aleatorio;
        string str;
        getline(leitura, str); // getline para passar pela primeira linha de referência
        for (j; j < 1013081; j++)  // Passagem dos ids para o vetor auxiliar vetConj, que agora terá 1013082 elementos
        {
            aleatorio = random(0, 12);
            for (int k = 0; k < 13; k++) {
                if (k == aleatorio) {      // Coleta o id da lina selecionada dentro do grupo
                    getline(leitura, str, ',');
                    vetConj[j] = stoi(str);
                }
                else
                    getline(leitura, str); // Joga fora as linhas que n foram selecionadas no grupo
            }
        }
        aleatorio = random(0, 7);
        for (int k = 0; k < aleatorio; k++)
        {
            getline(leitura, str);
        }
        getline(leitura, str, ',');  // Coleta o id da linha selecionada no ultimo grupo, de 8 linhas
        vetConj[j] = stoi(str);

        analisaCenario2(vetConj, q, v, vetAux);
    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    delete [] vetConj;

    leitura.close();
}

int main()
{
    srand(time(NULL));
    int* vetAux = new int[1000000];
    cout << "Escolha qual quicksort sera testado.\n Digite '1' para o quicksort recursivo,'2' para o quicksort mediana, ou '3' para o quicksort insertion\n";
    int x, y;

    cin >> x;

    switch ( x )
      {
         case 1:
            cenario2(1, 2, vetAux);
            break;
         case 2:
            cout << "Digite o valor de k (3 ou 5): " << endl;
            cin >> y;
            cenario2(2, y, vetAux);
            break;
         case 3:
            cout << "Digite o valor de n (10 ou 100): " << endl;
            cin >> y;
            cenario2(3, y, vetAux);
            break;
        default:
            cout << "Valor invalido!" << endl;
            break;
      }

    cout << "ACABOU!!!" << endl;
    delete [] vetAux;
    return 0;
}
