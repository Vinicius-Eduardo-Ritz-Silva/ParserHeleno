#include "Lexer.h"
#include <stdexcept>

Lexer::Lexer(string codigo)
{
    this->codigo = codigo;
}

void Lexer::q0(){
    char c = codigo[i];
    if (isEspaco(c)){
        i++;
    }
    else if (isDigito(c)){
        lexema += c;
        i++;

        if (i < codigo.size() && codigo[i] == '.') {
            lexema += '.';
            i++;
            estado_atual = 5;
        } else {
            estado_atual = 1;
            if(i == codigo.size()){
                tokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO,lexema));
            }
        }
    }
    else if (isLetra(c)){
        lexema += c;
        estado_atual = 2;
        i++;
        if(i == codigo.size()){

            if (isPalavraChave(lexema))
                tokens.push_back(Token(TipoDeToken::PALAVRA_CHAVE, lexema));
            else
                tokens.push_back(Token(TipoDeToken::IDENTIFICADOR, lexema));
        }
    }
    else if (isPontuacao(c)) {
        lexema += c;
        estado_atual = 7;
    }
    else if (isAspas(c)) {
        lexema += c;
        i++;
        estado_atual = 8;
    }
    else if (isApostrofo(c)) {
        lexema += c;
        i++;
        estado_atual = 9;
    }
    else if (isOperadorAritmetico(c)) {
        lexema += c;

        if (i + 1 < codigo.size() && (codigo[i + 1] == '=' || codigo[i + 1] == c)) {
            i++;
            lexema += codigo[i];
            estado_atual = 6;
        } else {
            estado_atual = 4;
        }
    }
    else if (isOperadorComparacao(c)) {
        lexema += c;

        if (i + 1 < codigo.size() && codigo[i + 1] == '=') {
            i++;
            lexema += codigo[i];
            estado_atual = 6;
        } else {
            estado_atual = 6;
        }
    }
    else if (isBarra(c)) {

        if (i + 1 < codigo.size() && codigo[i + 1] == '/') {
            i += 2;
            estado_atual = 10;
        } else if (i + 1 < codigo.size() && codigo[i + 1] == '*') {
            i += 2;
            estado_atual = 11;
        } else {
            lexema += c;
            estado_atual = 4;
        }
    }
    else{
        string msg = "Caractere invalido: ";
        msg += c;
        throw runtime_error(msg);
    }
}

void Lexer::q1(){
    char c = codigo[i];
    if (isDigito(c)){
        lexema += c;
        i++;
    }
    else {
        tokens.push_back(Token(TipoDeToken::NUMERO_INTEIRO, lexema));
        lexema = "";
        estado_atual = 0;
    }
}

void Lexer::q2(){
    char c = codigo[i];
    if (isLetra(c)){
        lexema += c;
        i++;
    }
    else {
        tokens.push_back(Token(TipoDeToken::IDENTIFICADOR, lexema));
        lexema = "";
        estado_atual = 0;
    }
}

void Lexer::q3(){
    char c = codigo[i];
    if (c == lexema[0]){
        lexema += c;
        tokens.push_back(Token(TipoDeToken::OPERADOR_LOGICO, lexema));
        lexema = "";
        estado_atual = 0;
        i++;
    }
    else {
        string msg = "Operador Logico incompleto, esperado '";
        msg += lexema[0];
        msg += "'mas encontrado '";
        msg += c;
        msg += "'";
        throw runtime_error(msg);
    }
}

void Lexer::q4(){
    tokens.push_back(Token(TipoDeToken::OPERADOR_ARITMETICO, lexema));
    lexema = "";
    estado_atual = 0;
    i++;
}

// q5: números reais
void Lexer::q5() {
    // Continua lendo dígitos após o ponto
    while (i < codigo.size() && isDigito(codigo[i])) {
        lexema += codigo[i];
        i++;
    }
    tokens.push_back(Token(TipoDeToken::NUMERO_REAL, lexema));
    lexema = "";
    estado_atual = 0;
}

// q6: operadores compostos e de comparação
void Lexer::q6() {
    // Assume que lexema já contém o operador
    if (lexema == "++") {
        tokens.push_back(Token(TipoDeToken::OPERADOR_INCREMENTO, lexema));
    } else if (lexema == "--") {
        tokens.push_back(Token(TipoDeToken::OPERADOR_DECREMENTO, lexema));
    } else if (lexema == "+=" || lexema == "-=" || lexema == "*=" || lexema == "/=") {
        tokens.push_back(Token(TipoDeToken::OPERADOR_COMPOSTO, lexema));
    } else if (lexema == "==" || lexema == "!=" || lexema == "<=" || lexema == ">=") {
        tokens.push_back(Token(TipoDeToken::OPERADOR_COMPARACAO, lexema));
    } else if (lexema == "=" || lexema == "<" || lexema == ">" || lexema == "!") {
        tokens.push_back(Token(TipoDeToken::OPERADOR_COMPARACAO, lexema));
    } else {
        tokens.push_back(Token(TipoDeToken::DESCONHECIDO, lexema));
    }
    lexema = "";
    estado_atual = 0;
    i++;
}

// q7: pontuação
void Lexer::q7() {
    tokens.push_back(Token(TipoDeToken::PONTUACAO, lexema));
    lexema = "";
    estado_atual = 0;
    i++;
}

// q8: string literal
void Lexer::q8() {
    while (i < codigo.size() && codigo[i] != '"') {
        // Permite escape de aspas
        if (codigo[i] == '\\' && i + 1 < codigo.size() && codigo[i + 1] == '"') {
            lexema += codigo[i];
            i++;
        }
        lexema += codigo[i];
        i++;
    }
    if (i < codigo.size() && codigo[i] == '"') {
        lexema += codigo[i];
        i++;
        tokens.push_back(Token(TipoDeToken::STRING_LITERAL, lexema));
    } else {
        tokens.push_back(Token(TipoDeToken::DESCONHECIDO, lexema));
    }
    lexema = "";
    estado_atual = 0;
}

// q9: caractere literal
void Lexer::q9() {
    // Aceita apenas um caractere entre aspas simples
    if (i < codigo.size()) {
        lexema += codigo[i];
        i++;
        if (i < codigo.size() && codigo[i] == '\'') {
            lexema += codigo[i];
            i++;
            tokens.push_back(Token(TipoDeToken::CARACTERE_LITERAL, lexema));
        } else {
            tokens.push_back(Token(TipoDeToken::DESCONHECIDO, lexema));
        }
    }
    lexema = "";
    estado_atual = 0;
}

// q10: comentário de linha
void Lexer::q10() {
    while (i < codigo.size() && codigo[i] != '\n') {
        lexema += codigo[i];
        i++;
    }
    tokens.push_back(Token(TipoDeToken::COMENTARIO_LINHA, lexema));
    lexema = "";
    estado_atual = 0;
    if (i < codigo.size() && codigo[i] == '\n') i++;
}

// q11: comentário de bloco
void Lexer::q11() {
    while (i + 1 < codigo.size() && !(codigo[i] == '*' && codigo[i + 1] == '/')) {
        lexema += codigo[i];
        i++;
    }
    if (i + 1 < codigo.size()) {
        // Consome '*/'
        i += 2;
        tokens.push_back(Token(TipoDeToken::COMENTARIO_BLOCO, lexema));
    } else {
        tokens.push_back(Token(TipoDeToken::DESCONHECIDO, lexema));
    }
    lexema = "";
    estado_atual = 0;
}


void Lexer::inicializar(){
    i = 0;
    estado_atual = 0;
    tokens.clear();
    lexema = "";
}

vector<Token>Lexer::Analisar(){
    inicializar();
    while (i < codigo.size()){
        switch(estado_atual){
            case 0: q0(); break;
            case 1: q1(); break;
            case 2: q2(); break;
            case 3: q3(); break;
            case 4: q4(); break;
            case 5: q5(); break;
            case 6: q6(); break;
            case 7: q7(); break;
            case 8: q8(); break;
            case 9: q9(); break;
            case 10: q10(); break;
            case 11: q11(); break;
            default: throw runtime_error("Estado invalido");
        }
    }
    return tokens;
}

bool Lexer::isEspaco(char c){
    return c == ' ' || c == '/t' ||
           c == '/r' || c == '/n';
}

bool Lexer::isDigito(char c){
    return c >= '0' && c <= '9';
}

bool Lexer::isLetra(char c){
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z');
}

bool Lexer::isPontuacao(char c) {
    return c == ';' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}';
}

bool Lexer::isOperadorAritmetico(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool Lexer::isOperadorComparacao(char c) {
    return c == '=' || c == '!' || c == '<' || c == '>';
}

bool Lexer::isOperadorAtribuicao(char c) {
    return c == '=';
}

bool Lexer::isAspas(char c) {
    return c == '"';
}

bool Lexer::isApostrofo(char c) {
    return c == '\'';
}

bool Lexer::isBarra(char c) {
    return c == '/';
}

bool Lexer::isPalavraChave(const string& lexema) {
    static const vector<string> palavras = {
        "if", "else", "while", "for", "return", "int", "float", "char", "void", "main"
    };
    for (const auto& palavra : palavras) {
        if (lexema == palavra) return true;
    }
    return false;
}
