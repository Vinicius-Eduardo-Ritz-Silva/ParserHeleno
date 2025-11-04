#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"

using namespace std;

class Parser
{
    public:
        Parser(vector<Token> tokens);
        void analisar();

    private:
        vector<Token> tokens;
        void E(), ELinha(), T();
        int posicao_atual;
        Token token_atual;
};

#endif // PARSER_H
