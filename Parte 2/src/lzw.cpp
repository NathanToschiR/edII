#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> codificacaoLZW(string sequencia)
{
    if(sequencia != "")
    {
        string str, c;
        vector<string> dic;
        vector<int> codificacao;
        vector<string>::iterator it;
        vector<string>::iterator it2;

        int i = 0;
        int cont = 0;
        string strAux;

        for(i ; i < 256 ; i++)
        {
            strAux = i;
            dic.push_back(strAux);
        }

        str = sequencia[0];
        cont++;
        while(cont <= sequencia.length())
        {
            c = sequencia[cont];
            it = find(dic.begin(), dic.end(), str+c);
            it2 = find(dic.begin(), dic.end(), str);

            if(find(dic.begin(), dic.end(), str+c) != dic.end()) // ou seja, encontrou str+c no dic
            {
                str = str+c;
            }
            else
            {
                strAux = str + c;
                codificacao.push_back(std::distance(dic.begin(), it2)); // posicao da str no dicionario
                dic.push_back(strAux);
                str = c;
            }
            cont++;
        }

        return codificacao;
    }
    else
    {
        cout << "ERRO: SEQUENCIA VAZIA" << endl;
        exit(1);
    }
}

/*int main()
{
    string str("bananabanabofana");
    vector<int> cod = codificacaoLZW(str);

    for(int i = 0 ; i < cod.size() ; i++)
    {
        cout << cod[i] << " ";
    }

    return 0;
}*/