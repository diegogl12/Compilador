#include <iostream>
#include <string>
#include <stdio.h>
#include <tuple>
#include <vector>

using namespace std;

vector< string > declaracao_id; /// tuple< nome_variavel, tipo_variavel>
char tipo;

void declarar_id(string nome)
{
    declaracao_id.push_back(nome);
}

void apaga_vetor_declaracao()
{
    declaracao_id.clear();
}

int tamanho_vetor()
{
    return declaracao_id.size();
}
