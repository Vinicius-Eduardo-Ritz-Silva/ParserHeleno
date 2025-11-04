#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(vector<Token> tokens)
{
    this->tokens = tokens;
    posicao_atual = 0;
    if (tokens.size != 0)
    {
        token_atual = tokens[0];
    }
}

void Parser::analisar()
{
    cout << "Processando E()" << endl;
    E();
}

//E -> T E'
void Parser::E()
{
    T();
    ELinha();
}

//E' -> "+" T E' | e
void Parser::ELinha()
{
    if(token_atual.getTipo() == TipoDeToken::OPERADOR_ARITMETICO && token_atual.getLexema() == "+")
    {

    }
    else
    {

    }
}

//T -> IDENTIFICADOR | NUMERO_INTEIRO
void Parser::T()
{

}
