#include <iostream>
#include <string>
#include <stdio.h>
#include <tuple>
#include <vector>

using namespace std;

vector< tuple<string,char,char,int,bool> > analisador_escopo; /// tuple< nome_variavel, var/constante, tipo_variavel, bloco, situação(true || false) >
int bloco_atual = 0;

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
        if(get<0>(*it) == nome && get<4>(*it) == true)
            return false;
    }

    return true;
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

