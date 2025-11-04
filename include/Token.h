#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TipoDeToken.h"

using namespace std;
class Token
{
    public:
        Token(TipoDeToken tipo,
              string lexema):
                tipo(tipo),
                lexema(lexema){}

        TipoDeToken getTipo(){
            return tipo;
        }

        string getLexema(){
            return lexema;
        }

        static string tipoParaString(TipoDeToken tipo){
            switch(tipo)
            {
                case TipoDeToken::NUMERO_INTEIRO : return "NUMERO_INTEIRO";
                case TipoDeToken::NUMERO_REAL : return "NUMERO_REAL";
                case TipoDeToken::IDENTIFICADOR : return "IDENTIFICADOR";
                case TipoDeToken::PALAVRA_CHAVE : return "PALAVRA_CHAVE";
                case TipoDeToken::OPERADOR_ARITMETICO : return "OPERADOR_ARITMETICO";
                case TipoDeToken::OPERADOR_LOGICO: return "OPERADOR_LOGICO";
                case TipoDeToken::OPERADOR_COMPARACAO: return "OPERADOR_COMPARACAO";
                case TipoDeToken::OPERADOR_ATRIBUICAO: return "OPERADOR_ATRIBUICAO";
                case TipoDeToken::OPERADOR_INCREMENTO: return "OPERADOR_INCREMENTO";
                case TipoDeToken::OPERADOR_DECREMENTO: return "OPERADOR_DECREMENTO";
                case TipoDeToken::OPERADOR_COMPOSTO: return "OPERADOR_COMPOSTO";
                case TipoDeToken::STRING_LITERAL: return "STRING_LITERAL";
                case TipoDeToken::CARACTERE_LITERAL: return "CARACTERE_LITERAL";
                case TipoDeToken::COMENTARIO_LINHA: return "COMENTARIO_LINHA";
                case TipoDeToken::COMENTARIO_BLOCO: return "COMENTARIO_BLOCO";
                case TipoDeToken::PONTUACAO: return "PONTUACAO";
                case TipoDeToken::DESCONHECIDO: return "DESCONHECIDO";
                default: return "DESCONHECIDO";
            }
        }

    private:
        string lexema;
        TipoDeToken tipo;
};


#endif // TOKEN_H
