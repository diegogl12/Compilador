#include <iostream>
#include <string>
#include <stdio.h>

#define ERRO_lexico -1
#define ERRO_sintatico -2

#define tk_numero 1
#define tk_numeroreal 2
#define tk_variavel 3
#define tk_atribuir 4
#define tk_diferente 5
#define tk_igual 6
#define tk_menorque 7
#define tk_maiorque 8
#define tk_menorigual 9
#define tk_maiorigual 10
#define tk_vezes 11
#define tk_divisao 12
#define tk_soma 13
#define tk_subtracao 14
#define tk_abreparenteses 15
#define tk_fechaparenteses 16
#define tk_pontovirgula 17
#define tk_end 18
#define tk_begin 19
#define tk_print 20
#define tk_if 21
#define tk_else 22
#define tk_then 23
#define tk_read 24
#define tk_write 25
#define tk_for 26
#define tk_to 27
#define tk_do 28
#define tk_var 29
#define tk_const 30
#define tk_real 31
#define tk_integer 32
#define tk_virgula 33
#define tk_ponto 34
#define tk_doispontos 35
#define tk_abrechaves 36
#define tk_fechachaves 37
#define tk_EOF 38

#define MAXreservadas 15

using namespace std;

FILE *arquivo;

char reservadas[MAXreservadas][10] = {"end","begin","print","if","else","then","read","write","for","to","do","var","const","real","integer"};

string lexema;
int token;

int contador_linha=1;

bool teste_erro = false;

void next_token();
void reconhece(int tk);
void erro(int sinal);

void program();
void constantes();
void lista_de_const();
void lista_de_const2();
void def_const();
void def_const2();
void variaveis();
void listas_de_ident();
void listas_de_ident2();
void def_listas_ident();
void def_listas_ident2();
void lista_de_ident();
void lista_de_ident2();
void bloco();
void comando();
void comandos();
void else_opc();
void expressao();
void expressao2();
void termo();
void termo2();
void fator();
void expr_relacional();
void op_rel();
void lista_arg();
void lista_arg2();

int main()
{
    arquivo = fopen("codigo.txt","r");

    next_token();
    program();

    if(!teste_erro)
        cout << "\t=== Compilou sem erros ===" << endl;

    fclose(arquivo);
    return 0;
}

void program()
{
    if(token == tk_const || token == tk_var || token == tk_begin)
    {
        constantes();
        variaveis();
        bloco();
        reconhece(tk_ponto);
        reconhece(tk_EOF);
    }
    else
        erro(ERRO_sintatico);
}

void constantes()
{
    if(token == tk_const)
    {
        reconhece(tk_const);
        lista_de_const();
    }

    else if(token == tk_var || token == tk_begin);

    else
        erro(ERRO_sintatico);
}

void lista_de_const()
{
    if(token == tk_variavel)
    {
        def_const();
        lista_de_const2();
    }
    else
        erro(ERRO_sintatico);
}

void lista_de_const2()
{
    if(token == tk_variavel)
    {
       lista_de_const();
    }
    else if(token == tk_var || token == tk_begin);
    else
        erro(ERRO_sintatico);
}

void def_const()
{
    if(token == tk_variavel)
    {
        reconhece(tk_variavel);
        reconhece(tk_igual);
        def_const2();
    }
    else
        erro(ERRO_sintatico);
}

void def_const2()
{
    if(token == tk_numero)
    {
        reconhece(tk_numero);
        reconhece(tk_pontovirgula);
    }
    else if(token == tk_numeroreal)
    {
        reconhece(tk_numeroreal);
        reconhece(tk_pontovirgula);
    }
    else
        erro(ERRO_sintatico);
}

void variaveis()
{
    if(token == tk_var)
    {
        reconhece(tk_var);
        listas_de_ident();
        reconhece(tk_pontovirgula);
    }

    else if(token == tk_variavel || token == tk_begin || token == tk_end || token == tk_read || token == tk_write || token == tk_if || token == tk_for);

    else
        erro(ERRO_sintatico);
}

void listas_de_ident()
{
    if(token == tk_variavel)
    {
       def_listas_ident();
       listas_de_ident2();
    }
    else
        erro(ERRO_sintatico);
}

void listas_de_ident2()
{
    if(token == tk_virgula)
    {
        reconhece(tk_virgula);
        listas_de_ident();
    }

    else if(token == tk_pontovirgula);

    else
        erro(ERRO_sintatico);
}

void def_listas_ident()
{
    if(token == tk_variavel)
    {
        lista_de_ident();
        reconhece(tk_doispontos);
        def_listas_ident2();
    }

    else
        erro(ERRO_sintatico);
}

void def_listas_ident2()
{
    if(token == tk_integer)
    {
        reconhece(tk_integer);
    }

    else if(token == tk_real)
    {
        reconhece(tk_real);
    }

    else
        erro(ERRO_sintatico);
}

void lista_de_ident()
{
    if(token == tk_variavel)
    {
        reconhece(tk_variavel);
        lista_de_ident2();
    }

    else
        erro(ERRO_sintatico);
}

void lista_de_ident2()
{
    if(token == tk_virgula)
    {
        reconhece(tk_virgula);
        reconhece(tk_variavel);
    }

    else if(token == tk_doispontos);

    else
        erro(ERRO_sintatico);
}

void bloco()
{
    if(token == tk_begin)
    {
        reconhece(tk_begin);
        variaveis();
        comandos();
        reconhece(tk_end);
    }

    else
        erro(ERRO_sintatico);
}

void comandos()
{
    if(token == tk_variavel || token == tk_read || token == tk_write || token == tk_if || token == tk_for)
    {
        comando();
        reconhece(tk_pontovirgula);
        comandos();
    }

    else if(token == tk_end);

    else
        erro(ERRO_sintatico);
}

void comando()
{
    if(token == tk_variavel)
    {
        reconhece(tk_variavel);
        reconhece(tk_atribuir);
        expressao();
    }

    else if(token == tk_read)
    {
        reconhece(tk_read);
        reconhece(tk_abreparenteses);
        lista_arg();
        reconhece(tk_fechaparenteses);
    }

    else if(token == tk_write)
    {
        reconhece(tk_write);
        reconhece(tk_abreparenteses);
        lista_arg();
        reconhece(tk_fechaparenteses);
    }

    else if(token == tk_if)
    {
        reconhece(tk_if);
        expr_relacional();
        reconhece(tk_then);
        bloco();
        else_opc();
    }

    else if(token == tk_for)
    {
        reconhece(tk_for);
        reconhece(tk_variavel);
        reconhece(tk_igual);
        expressao();
        reconhece(tk_to);
        expressao();
        reconhece(tk_do);
        bloco();
    }

    else
        erro(ERRO_sintatico);

}

void else_opc()
{
    if(token == tk_else)
    {
        reconhece(tk_else);
        bloco();
    }

    else if(token == tk_pontovirgula);

    else
        erro(ERRO_sintatico);
}

void expressao()
{
    if(token == tk_variavel || token == tk_numero || token == tk_numeroreal || token == tk_abreparenteses)
    {
       termo();
       expressao2();
    }

    else
        erro(ERRO_sintatico);
}

void expressao2()
{
    if(token == tk_soma)
    {
        reconhece(tk_soma);
        expressao();
    }

    else if(token == tk_subtracao)
    {
        reconhece(tk_subtracao);
        expressao();
    }

    else if(token == tk_igual || token == tk_diferente || token == tk_menorque || token == tk_maiorque || token == tk_menorigual || token == tk_maiorigual || token == tk_fechaparenteses || token == tk_pontovirgula || token
             == tk_to || token == tk_do || token == tk_then);

    else
        erro(ERRO_sintatico);
}

void termo()
{
    if(token == tk_variavel || token == tk_numero || token == tk_numeroreal || token
        == tk_abreparenteses)
    {
        fator();
        termo2();
    }

    else
        erro(ERRO_sintatico);
}

void termo2()
{
    if(token == tk_soma || token == tk_subtracao || token == tk_igual || token == tk_diferente || token == tk_menorque || token == tk_maiorque || token == tk_menorigual || token == tk_maiorigual || token == tk_fechaparenteses || token == tk_pontovirgula || token
             == tk_to || token == tk_do || token == tk_then);

    else if(token == tk_vezes)
    {
        reconhece(tk_vezes);
        termo();
    }

    else if(token == tk_divisao)
    {
        reconhece(tk_divisao);
        termo();
    }

    else
        erro(ERRO_sintatico);
}

void fator()
{
    if(token == tk_variavel)
        reconhece(tk_variavel);

    else if(token == tk_numero)
        reconhece(tk_numero);

    else if(token == tk_numeroreal)
        reconhece(tk_numeroreal);

    else if(token == tk_abreparenteses)
    {
        reconhece(tk_abreparenteses);
        expressao();
        reconhece(tk_fechaparenteses);
    }

    else
        erro(ERRO_sintatico);
}

void expr_relacional ()
{
    if(token == tk_variavel || token == tk_numero || token == tk_numeroreal || token == tk_abreparenteses)
    {
        expressao();
        op_rel();
        expressao();
    }

    else
         erro(ERRO_sintatico);
}

void op_rel()
{
    if(token == tk_igual)
        reconhece(tk_igual);

    else if(token == tk_diferente)
        reconhece(tk_diferente);

    else if(token == tk_menorque)
        reconhece(tk_menorque);

    else if(token == tk_maiorque)
        reconhece(tk_maiorque);

    else if(token == tk_menorigual)
        reconhece(tk_menorigual);

    else if(token == tk_maiorigual)
        reconhece(tk_maiorigual);

    else
         erro(ERRO_sintatico);
}

void lista_arg()
{
    if(token == tk_variavel)
    {
        reconhece(tk_variavel);
        lista_arg2();
    }

    else
         erro(ERRO_sintatico);
}

void lista_arg2()
{
    if(token == tk_virgula)
    {
        reconhece(tk_virgula);
        lista_arg();
    }

    else if(token == tk_fechaparenteses);

    else
        erro(ERRO_sintatico);
}


void next_token()
{
    int sinal=1;
    char character;
    string auxiliar;

    while(sinal && character != EOF)
    {
        character = fgetc(arquivo);
        auxiliar.push_back(character);

        if(auxiliar[0] == EOF)
        {
            token  =  tk_EOF;
            lexema = "EOF";
            sinal = 0;
        }

        else if((sinal && auxiliar == "{") || sinal == 3)
        {
            if(auxiliar[0] != '}')
            {
                if(auxiliar[0] == '\n')
                    contador_linha++;
                auxiliar.erase();
                sinal = 3;
            }

            else
            {
                auxiliar.erase();
                sinal = 1;
            }

        }

        else if( (auxiliar == " " || auxiliar == "\n" || auxiliar == "\t") && sinal) ///TESTE VAZIO
        {
            if(auxiliar == "\n")
                contador_linha++;

            auxiliar.erase();
        }

        else if(sinal && auxiliar[0] >= '0' && auxiliar[0] <= '9') ///TESTE NUMERO
        {
            if(auxiliar[auxiliar.size() -1] >= '0' && auxiliar[auxiliar.size() - 1] <= '9');

            else if(auxiliar[auxiliar.size() -1] == '.')
                sinal = 2;
            else
            {
                token = (sinal == 2)? tk_numeroreal:tk_numero;

                if(auxiliar[auxiliar.size() - 1] != EOF)
                    fseek(arquivo,-1,SEEK_CUR);

                auxiliar.pop_back();
                lexema = auxiliar;

                sinal=0;
            }
        }

        else if((sinal==1 && auxiliar[0] >= 'a' && auxiliar[0] <= 'z') )///TESTE RESERVADAS E VARIÁVEIS
        {
            if(!((auxiliar[auxiliar.size()-1] >= '0' && auxiliar[auxiliar.size() - 1] <= '9') || (auxiliar[auxiliar.size() - 1] >= 'a' && auxiliar[auxiliar.size() - 1] <= 'z') ))
            {
                int i=0;

                if(auxiliar[auxiliar.size()-1] != EOF)
                    fseek(arquivo,-1,SEEK_CUR);

                auxiliar.pop_back();

                for(i=0; i<MAXreservadas; i++)
                    if(!auxiliar.compare(reservadas[i]))
                        break;

                if(i >= MAXreservadas)
                {
                    lexema = auxiliar;
                    token = tk_variavel;
                    sinal = 0;
                }
                else
                {
                    token = 18 + i;
                    lexema = auxiliar;
                    sinal = 0;
                }
            }
        }

        else if(sinal)///TESTE OPERADOR
            switch(auxiliar[0])
            {
                case '+':
                    token = tk_soma;
                    lexema = auxiliar;
                    sinal = 0;
                    break;
                case '-':
                    token = tk_subtracao;
                    lexema = auxiliar;
                    sinal = 0;
                    break;
                case '*':
                    token = tk_vezes;
                    lexema = auxiliar;
                    sinal = 0;
                    break;
                case '/':
                    token = tk_divisao;
                    lexema = auxiliar;
                    sinal = 0;
                    break;
                case '{':
                    token = tk_abrechaves;
                    lexema = auxiliar;
                    sinal = 0;
                    break;
                case '}':
                    token = tk_fechachaves;
                    lexema = auxiliar;
                    sinal = 0;
                    break;
                case ',':
                    token = tk_virgula;
                    lexema = auxiliar;
					sinal = 0;
                    break;
                case ';':
                    token = tk_pontovirgula;
                    lexema = auxiliar;
                    sinal = 0;
                    break;
                case '(':
                    token = tk_abreparenteses;
                    lexema = auxiliar;
                    sinal = 0;
                    break;
                case ')':
                    token = tk_fechaparenteses;
                    lexema = auxiliar;
                    sinal = 0;
                    break;
                case '>': if(sinal == 1 && auxiliar.size()==1);
                          else if(auxiliar == ">=") {sinal = 0; token = tk_maiorigual; lexema = auxiliar;}
                          else {sinal = 0; fseek(arquivo,-1,SEEK_CUR); token = tk_maiorque; auxiliar.pop_back(); lexema = auxiliar;}
                          break;
                case '<': if(sinal == 1 && auxiliar.size() == 1);
                          else if(auxiliar == "<=") {sinal = 0; token = tk_menorigual; lexema = auxiliar;}
                          else if(auxiliar == "<>") {sinal = 0; token = tk_diferente; lexema = auxiliar;}
                          else {sinal = 0; fseek(arquivo,-1,SEEK_CUR); token = tk_maiorque; auxiliar.pop_back(); lexema = auxiliar;}
                          break;
                case '=':
                    token = tk_igual;
                    lexema = auxiliar;
                    sinal = 0;
                    break;
                case ':': if(sinal == 1 && auxiliar.size()==1);
                          else if(auxiliar == ":=") {sinal = 0; token = tk_atribuir; lexema = auxiliar;}
                          else {sinal = 0; fseek(arquivo,-1,SEEK_CUR); token = tk_doispontos; auxiliar.pop_back(); lexema = auxiliar;}
                          break;
                case '.':
                    token = tk_ponto;
                    lexema = auxiliar;
                    sinal = 0;
                    break;
                default:
                    lexema = auxiliar;
                    token = -1;
                    sinal = 0;
                    erro(ERRO_lexico);

            }
    }
}

void reconhece(int tk)
{
    if(token!=tk)
        erro(ERRO_sintatico);

    next_token();
}

void erro(int sinal)
{
    switch(sinal)
    {
        case ERRO_lexico: cout << "::::: LINHA " << contador_linha << ": LEXEMA <" << lexema << "> NAO RECONHECIDO! \t:::::" << endl;
            break;
        case ERRO_sintatico: cout << "::::: LINHA " << contador_linha << ": SIMBOLO <" << lexema << "> NAO ESPERADO! \t:::::" << endl;
    }

    teste_erro = true;

    next_token();
}
