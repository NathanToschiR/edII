#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <chrono>

using namespace std;

// ------------------------------------------------------------ FUNCOES AUXILIARES ------------------------------------------------------------------

struct userId {
    string user;
    int id;
} ;

int random(int min, int max)
{
    int num;
    srand(time(NULL));
    num = (rand()%(max-min));

    return num;
}

int randomLarge(int max)  // Funcao que nos permite pegar um numero aleatorio entre 0 e 506541
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

void trocarStruct(userId* a, userId* b)
{
    userId aux;
    aux = *a;
    *a = *b;
    *b = aux;
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

// ------------------------------------- CENARIO 1 - PARTE 1 - TIPO DE DADOS: VETOR DE INTEIROS (ID) ------------------------------------------------------------------

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
        *comp = *comp + n - 1;    // O numero de comparaçoes a cada chamada recursiva depende apenas do numero de elementos atual (n - 1 comparacoes)
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

void medias11(int grupo, int *vetDados, int *vetConj){ // Grupo representa o N (1000, 5000, 10000, 500000, 100000 e 500000)
    int r;
    int c = 0;
    cout << "Grupo: " << grupo << endl;
    int vet[grupo];

    for(int i = 0; i < 5; i++){              //ele deve fazer isso 5 vezes, como pedido, para coletar a media
        c = 0;
        while(c < grupo) {                 //preenche o vetor com valores aleatorios referente a entrada
            r = randomLarge(506541 - c);                  // Para nao haver repeticoes no vetor que iremos ordenar (vetAux), quando geramos um numero
            vet[c] = vetConj[r];                        // aleatorio, passamos o elemento correspondente a essa posicao para vetAux e trocamos este elemento,
            trocar(&vetConj[r], &vetConj[506541 - c]);    // no vetConj, com o ultimo elemento do vetor e geramos um numero aleatorio entre 0 e 1013082 - c,
            c++;                                          // para q nao coletemos o mesmo valor uma outra vez
        }
        cout << endl;
        auto t1 = std::chrono::high_resolution_clock::now();    //comeca a contar

        quickSort(vet, grupo, vetDados);

        auto t2 = std::chrono::high_resolution_clock::now();    //termina de contar
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        vetDados[2] = vetDados[2] + duration;
        cout << "\n";
    }

    vetDados[0] = vetDados[0]/5.0;  //divide todos por 5 para fazer a m�dia
    vetDados[1] = vetDados[1]/5.0;
    vetDados[2] = vetDados[2]/5.0;

    return;
}

void analisaCenario11(int *vetregistro){

    fstream entrada("entrada.txt");
    fstream saida("saida.txt", ios::app);

    string enes, conj;
    int k = 0;

    getline(entrada, conj);                     //le o numero de conjuntos que serao gerados a partir do arquivo de entrada
    int numGrupos = stoi(conj);
    cout << "\nConjunto: " << numGrupos << endl;
    int N[numGrupos];

    getline(entrada, enes);             //cria um vetor com a quantidade que cada conjunto deverá ter (N[0] = 1000, N[1] = 5000, ...)
    while(numGrupos > 0){
        N[k] = stoi(enes);
        numGrupos--;
        k++;
        getline(entrada, enes);
    }

    int x;
    int vetDados[3]; // Vetor que armazena as metricas (numero de comparacoes e trocas, tempo)
    int i, j;

    saida << "Cenario11\n";

    for(i = 0; i < k; i++){          //para cada conjunto, a analise sera feita
        for(j = 0; j < 3; j++){
            vetDados[j] = 0;         //zera o vetor de dados
        }
        medias11(N[i], vetDados, vetregistro);   //lança na funcao que retornarao as medias
        saida << "Medias do conjunto de " << N[i] << " dados - Trocas: " << vetDados[0] << ", Comparacoes: "
        << vetDados[1] << " e Tempo: " << (double)vetDados[2]/1000 << "\n";  //imprime no arquivo de saida
    }

    saida << endl;
    return;
}

void cenario11()
{
    fstream leitura("bgg-13m-reviews.csv");
    int* vetConj = new int[506542];

    if(leitura.is_open()) // leitura do arquivo "bgg-13m-reviews.csv"
    {
        int j = 0;
        int aleatorio;
        string str;
        getline(leitura, str); // getline para passar pela primeira linha de referência
        for (j; j < 506541; j++)
        {
            aleatorio = random(0, 25);
            for (int k = 0; k < 26; k++) {
                if (k == aleatorio) {
                    getline(leitura, str, ',');
                    vetConj[j] = stoi(str);
                }
                else
                    getline(leitura, str);
            }
        }
        aleatorio = random(0, 7);
        for (int k = 0; k < aleatorio; k++)
        {
            getline(leitura, str);  // joga as linhas fora (antes da linha sortida de cada bloco)
        }
        getline(leitura, str, ',');
        vetConj[j] = stoi(str);


        analisaCenario11(vetConj);
    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    delete [] vetConj;

    leitura.close();
}

// ------------------------------------- CENARIO 1 - PARTE 2 - TIPO DE DADOS: VETOR DE STRUCTS (USER, RATING, ID) ------------------------------------------------------

void auxQuickSortStruct(userId *vet, int p, int n, int *comp, int* troca)
{
    if (n == 2)
    {
        if (vet[p].id > vet[p + 1].id)
        {
            trocar(&vet[p].id, &vet[p+1].id);
            (*troca)++;
        }
        (*comp)++;
    }
    if (n > 2)
    {
        int r = vet[p + n - 1].id;
        int i = p;
        for (int j = p; j < p + n - 1; j++)
        {
            if (vet[j].id <= r)
            {
                if (j != i)
                {
                    trocar(&vet[i].id, &vet[j].id);
                    (*troca)++;
                }
                i++;
            }
        }
        *comp = *comp + n - 1;
        vet[p + n - 1].id = vet[i].id;
        vet[i].id = r;
        (*troca)++;
        auxQuickSortStruct(vet, p, i - p, comp, troca);
        auxQuickSortStruct(vet, i+1, p+n-i-1, comp, troca);
    }
}

void quickSortStruct(userId *vet, int n, int *vetdados) {
    int comp = 0;
    int troca = 0;
    auxQuickSortStruct(vet, 0, n, &comp, &troca);
    cout << "\nquickSort Trocas: " << troca;
    cout << "\nquickSort Comparacoes: " << comp << "\n";
    vetdados[0] = troca + vetdados[0];
    vetdados[1] = comp + vetdados[1];
}

void medias12(int grupo, int *vetDados, userId *vetConj){
    int r;
    int c = 0;
    cout << "Grupo: " << grupo << endl;
    userId* vetStruct = new userId [grupo];

    for(int i = 0; i < 5; i++){              //ele deve fazer isso 5 vezes, como pedido
        c = 0;
        while(c < grupo) {                 //preenche o vetor com valores aleatorios referente a entrada
            r = randomLarge(506541 - c);                  // Para nao haver repeticoes no vetor que iremos ordenar (vetAux), quando geramos um numero
            vetStruct[c] = vetConj[r];                  // aleatorio, passamos o elemento correspondente a essa posicao para vetAux e trocamos este elemento,
            trocarStruct(&vetConj[r], &vetConj[506541 - c]);    // no vetConj, com o ultimo elemento do vetor e geramos um numero aleatorio entre 0 e 1013082 - c,
            c++;                                          // para q nao coletemos o mesmo valor uma outra vez
        }
        auto t1 = std::chrono::high_resolution_clock::now();    //comeca a contar o tempo
        quickSortStruct(vetStruct, c, vetDados);
        auto t2 = std::chrono::high_resolution_clock::now();    //termina de contar
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        vetDados[2] = vetDados[2] + duration;
        cout << "\n";
    }

    vetDados[0] = vetDados[0]/5.0;  //divide todos por 5 para fazer a media
    vetDados[1] = vetDados[1]/5.0;
    vetDados[2] = vetDados[2]/5.0;

    delete [] vetStruct;

    return;
}

void PreencheVetArc(fstream* leitura, userId* vetorStruct, int i) // Preenche o vet vetConj com os Ids e os users
{
    string str;
    getline(*leitura, str, ',');
    vetorStruct[i].id = stoi(str);
    getline(*leitura, str, ',');
    vetorStruct[i].user = str;
    if (checagem(str))   // Ha users que possuem virgula, logo devemos checar se esse é o caso e passar o resto do nome para o user da Struct,
    {                    // caso contrario o getline para na virgula no meio do nome nao pega ele por completo
        getline(*leitura, str, ',');
        vetorStruct[i].user = vetorStruct[i].user + str;
    }
    getline(*leitura, str);
}

void analisaCenario12(userId *vetregistro) {

    fstream entrada("entrada.txt");
    fstream saida("saida.txt", ios::app);

    string enes, conj;
    int k = 0;

    getline(entrada, conj);                     //le o numero de conjuntos que serao gerados a partir do arquivo de entrada
    int numGrupos = stoi(conj);
    cout << "\nConjunto: " << numGrupos << endl;
    int N[numGrupos];

    getline(entrada, enes);             //cria um vetor com a quantidade que cada conjunto deverá ter (N[0] = 1000, N[1] = 5000, ...)
    while(numGrupos > 0){
        N[k] = stoi(enes);
        numGrupos--;
        k++;
        getline(entrada, enes);
    }

    int x;
    int vetDados[3]; // Vetor que armazena as metricas (numero de comparacoes e trocas, tempo)
    int i, j;

    saida << "Cenario12\n";

    for(i = 0; i < k; i++){          //para cada conjunto, a analise sera feita
        for(j = 0; j < 3; j++){
            vetDados[j] = 0;         //zera o vetor de dados
        }
        medias12(N[i], vetDados, vetregistro);   //lança na funcao que retornarao as medias
        saida << "Medias do conjunto de " << N[i] << " dados - Trocas: " << vetDados[0] << ", Comparacoes: "
        << vetDados[1] << " e Tempo: " << (double)vetDados[2]/1000 << "\n";  //imprime no arquivo de saida
    }

    saida << endl;
    return;
}

void cenario12()
{
    fstream leitura("bgg-13m-reviews.csv");
    userId* vetorStruct = new userId[506542];

    if(leitura.is_open()) // leitura do arquivo "bgg-13m-reviews.csv"
    {
        int j = 0;
        int aleatorio;
        string str;
        getline(leitura, str); // getline para passar pela primeira linha de referência

        for (j; j < 506541; j++)
        {
            aleatorio = random(0, 25);
            for (int k = 0; k < 26; k++) {
                if (k == aleatorio) {
                    PreencheVetArc(&leitura, vetorStruct, j);
                }
                else
                    getline(leitura, str);
            }
        }
        aleatorio = random(0, 7);
        for (int k = 0; k < aleatorio; k++)
        {
            getline(leitura, str);  // joga as linhas fora (antes da linha sortida de cada bloco)
        }
        PreencheVetArc(&leitura, vetorStruct, j);

        analisaCenario12(vetorStruct);

        delete [] vetorStruct;

    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    leitura.close();
}

int main()
{
    srand(time(NULL));
    cout << "Escolha o cenario para ser testado.\n Digite '1' para a parte 1 do cenario 1, ou '2' para a parte 2\n";
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
