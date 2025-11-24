#include <iostream>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main()
{
    try
    {
        string codigo = "10 + 4 * x";

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
