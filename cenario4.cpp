#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "No.h"

using namespace std;

// ------------------------------------------------------------ FUNCOES AUXILIARES ------------------------------------------------------------------

struct userId{
    string user;
    int id;
};

struct userIdCoalescido{
    string user;
    int id[2]; // id[0] é o valor do id e id[1] é a flag da próxima posicao(0 ~ N)/posicao vazia (-2)/fim do percurso(-1)
};

int random(int min, int max)
{
    int num;
    srand(time(NULL));
    num = (rand()%(max-min));

    return num;
}  // Funcao para pegar um numero aleatorio entre min e max

int randomLarge(int max)
{
    int num;
    num = ((rand() * rand()) % max);

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
} // funcao para contornar os problemas na leitura do arquivo "bgg-13m-reviews.csv"

void inicializarHash(userId* hash, int N)
{
    for(int i = 0 ; i < N ; i++)
    {
        hash[i].id = -1;
    }
}

int primoAnterior(int valor)
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
            valor--;
            candidatoADivisor = 2;
        } // se nao for primo, pego o valor logo anterior ao valor inserido como argumento e faco o testes desde o inicio
          // para checar se esse sim eh primo
        candidatoADivisor++;
    }
    return valor;
} // funçao que retorna o valor primo anterior ao valor passado como argumento

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
} // funçao que retorna o valor primo anterior ao valor passado como argumento

// -------------------------------------------------- HASH ENCADEAMENTO COALESCIDO ------------------------------------------------------------------------

void inicializarHashCoalescido(userIdCoalescido* hash, int N) // N é o tamanho
{
    for(int i = 0 ; i < N ; i++)
    {
        hash[i].id[1] = -2; // posicao do proximo (-2 significa posicao vazia)
        hash[i].id[0] = 0;  // valor do id
    }
}

void inserirEncadeamentoCoalescido(userId* vet, int nVet, unsigned long* vetDados)
{
    int N = primoPosterior(nVet);
    userIdCoalescido* hash = new userIdCoalescido [N];
    inicializarHashCoalescido(hash, N);
    unsigned long user; // variavel que armazena a string user como um valor inteiro

    for(int i = 0 ; i < nVet ; i++)
    {
        for(int z = 0 ; z < vet[i].user.length() ; z++)
        {
            user = vet[i].user[z] + user;
        } // tratamento da string para inteiro (código ASCII) para tambem funcionar como chave de ordenaçao
        unsigned long chave = user + vet[i].id;
        int posicao = chave % N;
        int posicaoAnterior;
        int j = N-1; // tamanho no vetor
        unsigned long compar = 0; // acumulador do numero de comparacoes

        if(hash[posicao].id[1] >= -1)
        {
            posicaoAnterior = posicao;
            while(hash[posicao].id[1] != -1)
            {
                posicao = hash[posicao].id[1];
                posicaoAnterior = posicao;
                compar++;
            } // enquanto nao chegarmos ao fim do "percurso" atualizamos o valor da posicao com o valor
            if(hash[posicao].id[1] != -2)
            {
                posicao = j;
                while (hash[posicao].id[1] != -2)
                {
                    posicao--;
                    compar++;
                    if(posicao < 0)
                    {
                        cout << "\nERRO: POSICAO INVALIDA, VALOR " << vet[i].id << " (HASH CHEIA)\n";
                        exit(1);
                    }
                }
                hash[posicaoAnterior].id[1] = posicao;
            }
        }
        hash[posicao].id[0] = vet[i].id;
        hash[posicao].user = vet[i].user;

        hash[posicao].id[1] = -1;
        vetDados[0] = vetDados[0] + compar; // atualizamos as comparacoes do vetDados
    }

    double memoriaUtilizada = N/256;
    vetDados[1] = vetDados[1] + memoriaUtilizada; // atualizamos a memoria do vetDados

    // como int tem 32 bits e N é o numero de elementos int que tem no vetor, N*32 é a quantidade
    // de bits que o vetor ocupa, como 1 byte = 8 bits, N*32/8 = N*4 é a quantidade de bytes que o vetor ocupa
    // N*4/1024 = N/256 é a quantidade em kilobytes que o vetor ocupa

    delete [] hash;
}

// -------------------------------------------------- HASH ENDERECAMENTO LINEAR ------------------------------------------------------------------------

void inserirEnderecamentoLinear(userId* vet, int nVet, unsigned long* vetDados)
{
    int N = primoPosterior(nVet);
    userId* hash = new userId [N];
    inicializarHash(hash, N);
    unsigned long user; // variavel que armazena a string user como um valor inteiro

    for(int i = 0 ; i < nVet ; i++)
    {
        for(int z = 0 ; z < vet[i].user.length() ; z++)
        {
            user = vet[i].user[z] + user;
        } // tratamento da string para inteiro (código ASCII) para tambem funcionar como chave de ordenaçao

        unsigned long chave = vet[i].id + user;
        int posicao = chave % N;
        unsigned long j = 1;
        unsigned long compar = 0;

        if(hash[posicao].id == -1)
            compar++;
        else
        {
            while(hash[posicao].id != -1)
            {
                posicao = (chave + j) % N;
                j++;
                compar++;
            }
        }

        hash[posicao].id = vet[i].id;
        hash[posicao].user = vet[i].user;
        vetDados[0] = vetDados[0] + compar;
    }
    double memoriaUtilizada = N/256;
    vetDados[1] = vetDados[1] + memoriaUtilizada;

    delete [] hash;
}
// -------------------------------------------------- HASH ENDERECAMENTO DUPLO HASH ------------------------------------------------

void inserirDoubleHashing(userId* vet, int nVet, unsigned long* vetDados)
{
    int N = primoPosterior(nVet);
    userId* hash = new userId [N];
    inicializarHash(hash, N);
    unsigned long user; // variavel que armazena a string user como um valor inteiro

    for(int i = 0 ; i < nVet ; i++)
    {
        for(int z = 0 ; z < vet[i].user.length() ; z++)
        {
            user = vet[i].user[z] + user;
        } // tratamento da string para inteiro (código ASCII) para tambem funcionar como chave de ordenaçao
        unsigned long chave = user + vet[i].id;
        unsigned int posicao =  chave % N;
        unsigned long colisoes = 0;
        int primoAnt = primoAnterior(nVet);
        unsigned long compar = 0;

        while(hash[posicao].id != -1)
        {
            compar++;
            colisoes++;
            posicao = ((chave % N) + (colisoes*(primoAnt - (chave % primoAnt)))) % N;
        } // colisoes

        hash[posicao].id = vet[i].id;
        hash[posicao].user = vet[i].user;
        vetDados[0] = vetDados[0] + compar;
    }
    double memoriaUtilizada = N/256;
    vetDados[1] = vetDados[1] + memoriaUtilizada;

    delete [] hash;
}
// -------------------------------------------------- HASH ENDERECAMENTO QUADRATICO ------------------------------------------------------------------------

void inserirQuadratico(userId* vet, int nVet, unsigned long* vetDados)
{
    int N = primoPosterior(nVet);
    userId* hash = new userId[N];
    inicializarHash(hash, N);
    int user; // variavel que armazena a string user como um valor inteiro

    for(int i = 0; i < nVet; i++)
    {
        for(int z = 0 ; z < vet[i].user.length() ; z++)
        {
            user = vet[i].user[z] + user;
        } // tratamento da string para inteiro (código ASCII) para tambem funcionar como chave de ordenaçao
        unsigned long chave = vet[i].id + user;
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
        hash[posicao].id = vet[i].id;
        hash[posicao].user = vet[i].user;
        vetDados[0] = vetDados[0] + compar;
    }
    double memoriaUtilizada = N/256;
    vetDados[1] = vetDados[1] + memoriaUtilizada;

    delete [] hash;
}

// -------------------------------------------------- HASH ENDERECAMENTO SEPARADO ------------------------------------------------------

void auxInserirSeparado(No* no, int id, string user, unsigned long* vetDados){
    static unsigned long compaar = 0;
    if((no->getId() != -1) && (no->getProx() == NULL))     //se o nó na posição não estiver vazio e não tiver um próximo nó preenchido
    {
        No* novono = new No;           //cria o próximo nó e insere o valor
        novono->setId(id);
        no->setProx(novono);
        compaar++;
    } else if(no->getId() != -1 && no->getProx() != NULL)       //se o nó não estiver vazio e seu próximo está preenchido, vai até o próximo e repete
    {
        auxInserirSeparado(no->getProx(), id, user, vetDados);
        compaar++;
    }else{               //se o nó estiver vazio, preenche o mesmo com os valores
        no->setId(id);
        no->setUser(user);
        vetDados[0] = vetDados[0] + compaar;   //soma no vetor de dados para calculo da media
    }
}

void inserirSeparado(userId* vet, int nVet, unsigned long* vetDados){
    int N = primoPosterior(nVet);  //encontra o primo posterior
    No *hash = new No[N];          //cria o hash, que é um vetor de nós de com o tamanho igual ao primo posterior
    unsigned long posicao, user;

    for(int i = 0; i < nVet; i++){         //for que irá inserir todos os elementos do vetor de tamanho nVet, um dos tamanho de conjunto informados no arquivo entrada.txt
        for(int z = 0 ; z < vet[i].user.length() ; z++)
        {
            user = vet[i].user[z] + user;
        }
        posicao = (user + vet[i].id) % N;       //calcula onde ele será inserido no hash
        auxInserirSeparado(&hash[posicao], vet[i].id, vet[i].user, vetDados);        //insere no hash
    }
    double memoriaUtilizada = N/256;            //cálculo da memória
    vetDados[1] = vetDados[1] + memoriaUtilizada;   //o cálculo da memória é inserida no vetor de dados para o calculo de media posterior
    delete [] hash;
}

// ---------------------------------------------------------- LEITURA E CHAMADA ----------------------------------------------------------------

void testeLeituraStruct(fstream* leitura, userId* vetorStruct, int i)
{
    string str;
    getline(*leitura, str, ','); // id da avaliacao
    vetorStruct[i].id = stoi(str);
    getline(*leitura, str, ',');
    vetorStruct[i].user = str;
    if (checagem(str))
    {
        getline(*leitura, str, ',');
        vetorStruct[i].user = vetorStruct[i].user + str;
    }
    getline(*leitura, str);
}


void medias4(int grupo, unsigned long *vetDados, userId *vetRegistro, int q, userId* vetAux)
{
    cout << "Entrou no media" << endl;
    int r;
    int c = 0;
    cout << "Grupo: " << grupo << endl;

    for(int i = 0; i < 5; i++){             //ele deve fazer isso 5 vezes, como pedido
        cout << "Entrou no For " << i+1 << " do media" << endl;
        c = 0;
        while(c < grupo) {                 //preenche o vetor com valores aleatorios referente a entrada
            r = randomLarge(506542 - c);
            vetAux[c].id = vetRegistro[r].id;
            vetAux[c].user = vetRegistro[r].user;
            trocarStruct(&vetRegistro[r], &vetRegistro[506542 - c]);
            c++;
        }
        cout << endl;

        switch (q) {
            case 1:
                inserirEnderecamentoLinear(vetAux, grupo, vetDados);
                break;
            case 2:
                inserirQuadratico(vetAux, grupo, vetDados);
                break;
            case 3:
                inserirDoubleHashing(vetAux, grupo, vetDados);
                break;
            case 4:
                inserirSeparado(vetAux, grupo, vetDados);
                break;
            case 5:
                inserirEncadeamentoCoalescido(vetAux, grupo, vetDados);
                break;
        }
    }

    cout << "\nSaiu do for analisa" << endl;
    vetDados[0] = vetDados[0]/5.0;  //divide todos por 5 para fazer a media
    vetDados[1] = vetDados[1]/5.0;
    cout << "vai sair do analisa" << endl;

    return;
}

void analisaCenario4(userId *vetRegistro, int q, userId* vetAux){

    fstream entrada("entraada.txt");
    fstream saida("saida.txt", ios::app);

    string enes, conj;
    int k = 0;

    getline(entrada, conj);             //descobre quantos conjuntos serão gerados
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
    unsigned long vetDados[2];
    int i, j;

    saida << "Cenario 4\n";

    switch (q) {
        case 1:
            saida << "Enderecamento - Sondagem Linear" << endl;
            break;
        case 2:
            saida << "Enderecamento - Sondagem Quadratica" << endl;
            break;
        case 3:
            saida << "Enderecamento - Duplo Hash" << endl;
            break;
        case 4:
            saida << "Encadeamento Separado" << endl;
            break;
        case 5:
            saida << "Encadeamento Coalescido (sem porao)" << endl;
            break;
    }

    for(i = 0; i < k; i++){  // para cada conjunto, a analise sera feita
        cout << "\nFor numero " << i << endl;
        for(j = 0; j < 2; j++){
            vetDados[j] = 0;         // zera o vetor de dados
        }
        medias4(N[i], vetDados, vetRegistro, q, vetAux);   // lança na funcao que retornarao as medias
        cout << "saiu do media";
        saida << "Medias do conjunto de " << N[i] << " dados - Comparacoes: " << vetDados[0] << ", Memoria utilizada: "
        << (double)vetDados[1] << " kb\n";  // imprime no arquivo
    }

    saida << endl;
    return;
}

void cenario4(int q, userId* vetAux)
{
    fstream leitura("bgg-13m-reviews.csv");
    userId* vetArc = new userId[506542]; // futuro vetRegistro

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
            testeLeituraStruct(&leitura, vetArc, j);
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
        testeLeituraStruct(&leitura, vetArc, j);


        analisaCenario4(vetArc, q, vetAux);
    } else {
        cout << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO .CSV";
    }

    delete [] vetArc;

    leitura.close();
}

int main()
{
    userId* vetAux = new userId[500000];
    cout << "Escolha qual Hash sera testada. Digite:\n'1' para Enderecamento - Sondagem Linear\n'2' para Enderecamento - Sondagem ";
    cout << "Quadratica\n'3' para Enderecamento - Duplo Hash\n'4' para Encadeamento Separado\n'5' para Encademento Coalescido (sem porao)\n";
    int x;

    cin >> x;

    switch ( x )
    {
        case 1:
            cenario4(1, vetAux);
            break;
        case 2:
            cenario4(2, vetAux);
            break;
        case 3:
            cenario4(3, vetAux);
            break;
        case 4:
            cenario4(4, vetAux);
            break;
        case 5:
            cenario4(5,vetAux);
            break;
        default:
            cout << "Valor invalido!" << endl;
            break;
    }


    cout <<"\n\nACABOU!!!" << endl;
    delete [] vetAux;
    return 0;
}
