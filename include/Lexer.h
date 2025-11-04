#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

using namespace std;

class Lexer
{
    public:
        Lexer(string codigo);
        vector<Token> Analisar();

    private:
        string codigo, lexema;
        void inicializar(), q0(), q1(), q2(), q3(), q4();
        void q5(); // números reais
        void q6(); // operadores compostos
        void q7(); // pontuação
        void q8(); // strings literais
        void q9(); // caracteres
        void q10(); // comentário de linha
        void q11(); // comentário de bloco
        bool isEspaco(char c);
        bool isDigito(char c);
        bool isLetra(char c);
        bool isPontuacao(char c);
        bool isOperadorAritmetico(char c);
        bool isOperadorComparacao(char c);
        bool isOperadorAtribuicao(char c);
        bool isAspas(char c);
        bool isApostrofo(char c);
        bool isBarra(char c);
        bool isPalavraChave(const string& lexema);
        int i, estado_atual;
        vector<Token> tokens;
};

#endif // LEXER_H
