#include <iostream>
#include <string>
#include <stdio.h>
#include <tuple>
#include <vector>

using namespace std;

vector< tuple<string,char,char,int,bool> > analisador_escopo; /// tuple< nome_variavel, var/constante, tipo_variavel, bloco, situação(true || false) >
int bloco_atual = 0;
char getConst = '0';

void inicia_id(string nome, char var_cons)
{
    tuple<string,char,char,int,bool> auxiliar(nome,var_cons,'T',bloco_atual,true);

    analisador_escopo.push_back(auxiliar);
}

void define_tipo(char tipo)
{
    for(vector< tuple<string,char,char,int,bool> > :: iterator it = analisador_escopo.begin(); it != analisador_escopo.end(); ++it)
    {
        if(get<2>(*it) == 'T')
            get<2>(*it) = tipo;
    }
}
void atualiza_situacao()
{
    for(vector< tuple<string,char,char,int,bool> > :: iterator it = analisador_escopo.begin(); it != analisador_escopo.end(); ++it)
    {
        if(get<3>(*it) > bloco_atual)
            get<4>(*it) = false;
    }
}

bool teste_existencia(string nome)
{
    for(vector< tuple<string,char,char,int,bool> > :: iterator it = analisador_escopo.begin(); it != analisador_escopo.end(); ++it)
    {
        if(get<0>(*it) == nome)
            return true;
    }

    return false;
}

bool teste_escopo(string nome)
{
    for(vector< tuple<string,char,char,int,bool> > :: iterator it = analisador_escopo.begin(); it != analisador_escopo.end(); ++it)
    {
        if(get<0>(*it) == nome && get<3>(*it) <= bloco_atual && get<4>(*it) == true)
            return true;
    }

    return false;
}

//analisador_semantico_tipo

bool verifica_const(string nome)
{
    for(vector< tuple<string,char,char,int,bool> > :: iterator it = analisador_escopo.begin(); it != analisador_escopo.end(); ++it)
    {
        if(get<0>(*it) == nome && get<1>(*it) == getConst && get<4>(*it) == true)
            return true;
    }
    return false;
}

char get_tipo(string nome)
{
    for(vector< tuple<string,char,char,int,bool> > :: iterator it = analisador_escopo.begin(); it != analisador_escopo.end(); ++it)
    {
        if(get<0>(*it) == nome && get<4>(*it) == true)
        {
            return get<2>(*it);
        }
    }

    return '0';
}

bool teste_tipo(string nome, char tipo)
{
    for(vector< tuple<string,char,char,int,bool> > :: iterator it = analisador_escopo.begin(); it != analisador_escopo.end(); ++it)
    {
        if(get<0>(*it) == nome && get<2>(*it) == tipo && get<4>(*it) == true)
        {
            return true;
        }
    }

    return false;
}

char compara_tipo(char tipo1, char tipo2)
{
    if((tipo1 == 'i' || tipo1 == 'I') && (tipo2 == 'i') || (tipo2 == 'I'))
    {
        if(tipo1 == 'I' || tipo2 == 'I')
            return 'I';
        return 'i';
    }
    else if(((tipo1 == 'i' || tipo1  == 'I') && tipo2 == 'f') || (tipo1 == 'f' && (tipo2 == 'i' || tipo2  == 'I')))
        return 'I'; ///SE UM INTEIRO RECEBE FLOAT DARÁ ERRO WARNING
    else if(tipo1 == '0' || tipo2 == '0')
    {
        if(tipo2 == '0')
            return tipo1;
        else
            return tipo2;
    }
    else
        return 'f';

}
