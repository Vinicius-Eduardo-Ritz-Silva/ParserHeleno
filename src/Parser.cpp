#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(vector<Token> tokens)
{
    this->tokens = tokens;
    posicao_atual = 0;
    if (tokens.size() != 0)
    {
        token_atual = tokens[0];
    }
}

void Parser::avancar(){
    posicao_atual++;
    if(posicao_atual<tokens.size()){
        token_atual = tokens[posicao_atual];
    } else {
        token_atual = TipoDeToken.DESCONHECIDO;
    }
}

void Parser::erro(string msg){
    string erro_completo = "Erro Sintatico: " + msg + " | Token atual: " + token_atual.print();
    throw runtime_error(erro_completo);
}

void Parser::analisar()
{
    cout << "Processando E()" << endl;
    E();
}

//E -> T E'
void Parser::E()
{
    cout << "Expandindo E -> T E'" << endl;
    T();
    ELinha();
}

//E' -> + T E' | - T E' | e
void Parser::ELinha()
{
    if(token_atual.getTipo() == TipoDeToken::OPERADOR_ARITMETICO && token_atual.getLexema() == "+")
    {
        cout << "Expandindo E' --> + T E'" << endl;
        cout << "Consumindo: " << token_atual.print() << endl;
        avancar();
        T();
        ELinha();
    }
    else{
        if(token_atual.getTipo() == TipoDeToken::OPERADOR_ARITMETICO && token_atual.getLexema() == "-"){
            cout << "Expandindo E' --> - T E'" << endl;
            cout << "Consumindo: " << token_atual.print() << endl;
            avancar();
            T();
            ELinha();
        } else{
            cout << "Expandindo E' --> Cadeia Vazia" << endl;
        }
    }
}

//T -> F T'
void Parser::T()
{
    cout << "Expandindo T -> F T'" << endl;
    F();
    TLinha();
}

//T' -> * F T' | / F T' | e
void Parser::TLinha(){
    if(token_atual.getTipo() == TipoDeToken::OPERADOR_ARITMETICO && token_atual.getLexema() == "*")
    {
        cout << "Expandindo T' --> * F T'" << endl;
        cout << "Consumindo: " << token_atual.print() << endl;
        avancar();
        F();
        TElinha();
    }
    else{
        if(token_atual.getTipo() == TipoDeToken::OPERADOR_ARITMETICO && token_atual.getLexema() == "/"){
            cout << "Expandindo T' --> / F T'" << endl;
            cout << "Consumindo: " << token_atual.print() << endl;
            avancar();
            F();
            TLinha();
        } else{
            cout << "Expandindo T' --> Cadeia Vazia" << endl;
        }
    }
}

//F -> IDENTIFICADOR | NUMERO_INTEIRO
void Parser::F(){
    if(token_atual.getTipo() == TipoDeToken::IDENTIFICADOR){
        cout << "Expandido T --> IDENTIFICADOR" << endl;
        cout << "Consumindo: " << token_atual << endl;
        avancar();
    } else {
        if(token_atual.getTipo() == TipoDeToken::NUMERO_INTEIRO){
            cout << "Expandido T --> NUMERO_INTEIRO" << endl;
            cout << "Consumindo: " << token_atual << endl;
            avancar();
        } else {
            erro("Aguardando IDENTIFICADOR ou NUMERO_INTEIRO");
        }
}
