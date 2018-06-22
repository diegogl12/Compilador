#include <iostream>
#include <string>
#include <stdio.h>
#include <tuple>
#include <vector>

using namespace std;

vector< string > declaracao_id;
vector <char> declaracao_tipo;

void declarar_id(string nome)
{
    declaracao_id.push_back(nome);
}

void declarar_tipo(char tipo)
{
    declaracao_tipo.push_back(tipo);
}

void apaga_vetor_declaracao()
{
    declaracao_id.clear();
    declaracao_tipo.clear();
}

int tamanho_vetor()
{
    return declaracao_id.size();
}
