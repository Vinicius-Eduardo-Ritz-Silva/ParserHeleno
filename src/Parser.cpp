/*
E  -> T E'
E' -> + T E’ | - T E’ | e
T -> F T'
T' -> * F T' | / F T' | e
F  -> IDENTIFICADOR | NUMERO_INTEIRO
*/

#include "Parser.h"
#include <iostream>

using namespace std;

Parser::Parser(vector<Token> tokens)
{
    this->tokens = tokens;
    posicao_atual = 0;
    if (tokens.size() != 0){
        token_atual = tokens[0];
    }
}

//avança para o próximo token da lista, se ainda existirem tokens
void Parser::avancar(){
    posicao_atual++;
    if(posicao_atual < tokens.size()){
        token_atual = tokens[posicao_atual];
    }
    else{
        token_atual =
        Token(TipoDeToken::DESCONHECIDO,"");
    }
}

//monta e lança mensagem de erro
void Parser::erro(string msg){
    string erro_completo =
    "Erro Sintatico: " + msg +
    " | Token atual: " + token_atual.print();
    throw runtime_error(erro_completo);
}

void Parser::analisar()
{
    E();
}

//E  -> T E'
void Parser::E(){
    cout << "Expandindo E -> T E'" << endl;
    T();
    ELinha();
}

//E' -> + T E' | - T E' | e
void Parser::ELinha(){
    if(token_atual.getTipo() ==
       TipoDeToken::OPERADOR_ARITMETICO &&
       token_atual.getLexema() == "+"){
        cout << "Expandindo E' --> + T E'" << endl;
        cout << "   Consumindo: " << token_atual.print() << endl;
        avancar(); //consumiu o operador aritmetico '+'
        T();
        ELinha();
    }
    else{
        if(token_atual.getTipo() ==
           TipoDeToken::OPERADOR_ARITMETICO &&
           token_atual.getLexema() == "-"){
            cout << "Expandindo E' --> - T E'" << endl;
            cout << "   Consumindo: " << token_atual.print() << endl;
            avancar(); //consumiu o operador aritmetico '-'
            T();
            ELinha();
        }
        else{
        //cadeia vazia: nao faz nada
        cout << "Expandindo E' --> e (cadeia vazia)" << endl;
        }
    }
}

//T -> F T'
void Parser::T(){
    cout << "Expandindo T -> F T'" << endl;
    F();
    TLinha();
}

//T' -> * F T' | / F T' | e
void Parser::TLinha(){
    if(token_atual.getTipo() ==
       TipoDeToken::OPERADOR_ARITMETICO &&
       token_atual.getLexema() == "*"){
        cout << "Expandindo T' --> * F T'" << endl;
        cout << "   Consumindo: " << token_atual.print() << endl;
        avancar(); //consumiu o operador aritmetico '*'
        F();
        TLinha();
    }
    else{
        if(token_atual.getTipo() ==
           TipoDeToken::OPERADOR_ARITMETICO &&
           token_atual.getLexema() == "/"){
            cout << "Expandindo T' --> / F T'" << endl;
            cout << "   Consumindo: " << token_atual.print() << endl;
            avancar(); //consumiu o operador aritmetico '/'
            F();
            TLinha();
        }
        else{
            //cadeia vazia: nao faz nada
            cout << "Expandindo T' --> e (cadeia vazia)" << endl;
        }
    }
}

//F  -> IDENTIFICADOR | NUMERO_INTEIRO
void Parser::F(){
    if(token_atual.getTipo() == TipoDeToken::IDENTIFICADOR){
        cout << "Expandindo F --> IDENTIFICADOR" << endl;
        cout << "   Consumindo: " << token_atual.print() << endl;
        avancar();
    }
    else {
        if(token_atual.getTipo() == TipoDeToken::NUMERO_INTEIRO){
            cout << "Expandindo F --> NUMERO_INTEIRO" << endl;
            cout << "   Consumindo: " << token_atual.print() << endl;
            avancar();
        }
        else{
            erro("Aguardando IDENTIFICADOR ou NUMERO_INTEIRO, mas encontrou: " + token_atual.print());
        }
    }
}
