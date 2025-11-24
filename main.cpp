#include <iostream>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main()
{
    try
    {
        string codigo = "if (x) { 10 + 2; } else { while (z) { for (i; i; i) { (1 + 2) * 3; } } }";

        cout << endl << "Iniciando analise Lexica..." << endl << endl;
        Lexer lexer(codigo);
        vector<Token> listaDeTokens = lexer.Analisar();
        for(auto token : listaDeTokens){
            cout << "Token: " << token.getLexema() << " (" << Token::tipoParaString(token.getTipo()) << ") " << endl;
        }
        cout << endl << "Analise Lexica concluida com sucesso!" << endl << endl;

        cout << endl << "Iniciando analise Sintatica..." << endl << endl;
        Parser parser(listaDeTokens);
        parser.analisar();
        cout << endl << "Analise Sintatica concluida com sucesso!" << endl << endl;
    }
    catch(exception &e)
    {
        cout << "Erro: " << e.what() << endl;
    }
    return 0;
}
