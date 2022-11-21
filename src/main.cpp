#include "Lexer.h"

#include <iostream>

int main() 
{
    std::string dua = 
    "(1 + 2) * 3";

    Lexer l(dua);
    l.scanTokens();
    auto tokens =  l.getTokens();

    Parser p(tokens);
    p.parse();
}   
