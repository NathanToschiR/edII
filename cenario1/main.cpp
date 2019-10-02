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

// ------------------------------------- CENARIO 1 - PARTE 1 - TIPO DE DADOS: VETOR DE INTEIROS (ID) ------------------------------------------------------------------

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

void medias11(int grupo, int *vetDados, int *vetConj){
    int r;
    int c = 0;
    cout << "Grupo: " << grupo << endl;
    int teste[grupo];

    for(int i = 0; i < 5; i++){              //ele deve fazer isso 5 vezes, como pedido
        c = 0;
        while(c < grupo) {                 //preenche o vetor com valores aleatorios referente a entrada
            r = randomLarge(506542);
            teste[c] = vetConj[r];
            c++;
        }
        cout << endl;
        auto t1 = std::chrono::high_resolution_clock::now();    //comeca a contar
        quickSort(teste, grupo, vetDados);
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

void analisaCenario11(int *vetregistro){

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

    int x;
    int vetData[3];
    int i, j;

    saida << "Cenario11\n";

    for(i = 0; i < k; i++){          //para cada conjunto, a analise sera feita
        for(j = 0; j < 3; j++){
            vetData[j] = 0;         //zera o vetor de dados
        }
        medias11(N[i], vetData, vetregistro);   //lança na funcao que retornarao as medias
        saida << "Medias do conjunto de " << N[i] << " dados - Trocas: " << vetData[0] << ", Comparacoes: "
        << vetData[1] << " e Tempo: " << (double)vetData[2]/1000 << "\n";  //imprime no arquivo
    }

    saida << endl;
    return;
}

void cenario11()
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


        analisaCenario11(vetArc);
    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    delete [] vetArc;

    leitura.close();
}

// ------------------------------------- CENARIO 1 - PARTE 2 - TIPO DE DADOS: VETOR DE STRUCTS (USER, RATING, ID) ------------------------------------------------------

void auxQuickSortStruct(userRatingId *vet, int p, int n, int *comp, int* troca)
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

void quickSortStruct(userRatingId *vet, int n, int *vetdados) {
    int comp = 0;
    int troca = 0;
    auxQuickSortStruct(vet, 0, n, &comp, &troca);
    cout << "\nquickSort Trocas: " << troca;
    cout << "\nquickSort Comparacoes: " << comp << "\n";
    vetdados[0] = troca + vetdados[0];
    vetdados[1] = comp + vetdados[1];
}

void medias12(int grupo, int *vetDados, userRatingId *vetConj){
    int r;
    int c = 0;
    cout << "Grupo: " << grupo << endl;
    userRatingId* testestruct = new userRatingId [grupo];

    for(int i = 0; i < 5; i++){              //ele deve fazer isso 5 vezes, como pedido
        c = 0;
        while(c < grupo){
            r = randomLarge(506542);
            testestruct[c] = vetConj[r];
            c++;
        }
        auto t1 = std::chrono::high_resolution_clock::now();    //comeca a contar o tempo
        quickSortStruct(testestruct, c, vetDados);
        auto t2 = std::chrono::high_resolution_clock::now();    //termina de contar
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        vetDados[2] = vetDados[2] + duration;
        cout << "\n";
    }

    vetDados[0] = vetDados[0]/5.0;  //divide todos por 5 para fazer a media
    vetDados[1] = vetDados[1]/5.0;
    vetDados[2] = vetDados[2]/5.0;

    delete [] testestruct;

    return;
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

void analisaCenario12(userRatingId *vetregistro){

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

    int x;
    int vetData[3];
    int i, j;

    saida << "Cenario12\n";

    for(i = 0; i < k; i++){          //para cada conjunto, a analise sera feita
        for(j = 0; j < 3; j++){
            vetData[j] = 0;         //zera o vetor de dados
        }
        medias12(N[i], vetData, vetregistro);   //lança na funcao que retornarao as medias
        saida << "Medias do conjunto de " << N[i] << " dados - Trocas: " << vetData[0] << ", Comparacoes: "
        << vetData[1] << " e Tempo: " << (double)vetData[2]/1000 << "\n";  //imprime no arquivo
    }

    saida << endl;
    return;
}

void cenario12()
{
    fstream leitura("bgg-13m-reviews.csv");
    userRatingId* vetorStruct = new userRatingId[506542];

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
