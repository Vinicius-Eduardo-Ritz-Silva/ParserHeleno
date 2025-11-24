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
    while(token_atual.getTipo() != TipoDeToken::DESCONHECIDO) {
        Statement();
    }
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
    else if(token_atual.getTipo() == TipoDeToken::NUMERO_INTEIRO){
        cout << "Expandindo F --> NUMERO_INTEIRO" << endl;
        cout << "   Consumindo: " << token_atual.print() << endl;
        avancar();
    }
    else if(token_atual.getLexema() == "("){
        cout << "Expandindo F --> ( E )" << endl;
        cout << "   Consumindo: " << token_atual.print() << endl;
        avancar();
        E();
        if(token_atual.getLexema() == ")"){
            cout << "   Consumindo: " << token_atual.print() << endl;
            avancar();
        }
        else{
            erro("Esperado ')' mas encontrou: " + token_atual.print());
        }
    }
    else{
        erro("Aguardando IDENTIFICADOR, NUMERO_INTEIRO ou '(', mas encontrou: " + token_atual.print());
    }
}

void Parser::Statement() {
    if (token_atual.getLexema() == "if") {
        IfStatement();
    } else if (token_atual.getLexema() == "while") {
        WhileStatement();
    } else if (token_atual.getLexema() == "for") {
        ForStatement();
    } else if (token_atual.getLexema() == "{") {
        Block();
    } else {
        E();
        if (token_atual.getLexema() == ";") {
            cout << "   Consumindo: " << token_atual.print() << endl;
            avancar();
        } else {
            erro("Esperado ';' apos expressao, mas encontrou: " + token_atual.print());
        }
    }
}

void Parser::Block() {
    cout << "Expandindo Block --> { StatementList }" << endl;
    if (token_atual.getLexema() == "{") {
        cout << "   Consumindo: " << token_atual.print() << endl;
        avancar();
        
        while (token_atual.getLexema() != "}" && token_atual.getTipo() != TipoDeToken::DESCONHECIDO) {
            Statement();
        }

        if (token_atual.getLexema() == "}") {
            cout << "   Consumindo: " << token_atual.print() << endl;
            avancar();
        } else {
            erro("Esperado '}' ao final do bloco.");
        }
    } else {
        erro("Esperado '{' no inicio do bloco.");
    }
}

void Parser::IfStatement() {
    cout << "Expandindo IfStatement --> if ( E ) Statement" << endl;
    cout << "   Consumindo: " << token_atual.print() << endl; // if
    avancar();

    if (token_atual.getLexema() == "(") {
        cout << "   Consumindo: " << token_atual.print() << endl;
        avancar();
        E();
        if (token_atual.getLexema() == ")") {
            cout << "   Consumindo: " << token_atual.print() << endl;
            avancar();
            Statement();
            
            if (token_atual.getLexema() == "else") {
                cout << "Expandindo ElsePart --> else Statement" << endl;
                cout << "   Consumindo: " << token_atual.print() << endl;
                avancar();
                Statement();
            }
        } else {
            erro("Esperado ')' apos condicao do if.");
        }
    } else {
        erro("Esperado '(' apos if.");
    }
}

void Parser::WhileStatement() {
    cout << "Expandindo WhileStatement --> while ( E ) Statement" << endl;
    cout << "   Consumindo: " << token_atual.print() << endl; // while
    avancar();

    if (token_atual.getLexema() == "(") {
        cout << "   Consumindo: " << token_atual.print() << endl;
        avancar();
        E();
        if (token_atual.getLexema() == ")") {
            cout << "   Consumindo: " << token_atual.print() << endl;
            avancar();
            Statement();
        } else {
            erro("Esperado ')' apos condicao do while.");
        }
    } else {
        erro("Esperado '(' apos while.");
    }
}

void Parser::ForStatement() {
    cout << "Expandindo ForStatement --> for ( ... ) Statement" << endl;
    cout << "   Consumindo: " << token_atual.print() << endl; // for
    avancar();

    if (token_atual.getLexema() == "(") {
        cout << "   Consumindo: " << token_atual.print() << endl;
        avancar();
        
        if (token_atual.getLexema() != ";") {
            E(); 
        }
        if (token_atual.getLexema() == ";") {
            cout << "   Consumindo: " << token_atual.print() << endl;
            avancar();
        } else {
             erro("Esperado ';' apos inicializacao do for.");
        }

        if (token_atual.getLexema() != ";") {
            E();
        }
        if (token_atual.getLexema() == ";") {
            cout << "   Consumindo: " << token_atual.print() << endl;
            avancar();
        } else {
             erro("Esperado ';' apos condicao do for.");
        }

        if (token_atual.getLexema() != ")") {
            E();
        }
        
        if (token_atual.getLexema() == ")") {
            cout << "   Consumindo: " << token_atual.print() << endl;
            avancar();
            Statement();
        } else {
            erro("Esperado ')' apos incremento do for.");
        }
    } else {
        erro("Esperado '(' apos for.");
    }
}
