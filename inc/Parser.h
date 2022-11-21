#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "Expr.h"

#include <vector>

class Parser 
{
    std::vector<Token> mTokens;
    int mPos;

public:
    Parser(const std::vector<Token>& tokens);
    ExprPtr parse();

private:
    ExprPtr program();
    ExprPtr expression();
    ExprPtr equality();
    ExprPtr comparison();
    ExprPtr sum();
    ExprPtr product();
    ExprPtr unary();
    ExprPtr primary();


    bool match(std::initializer_list<TokenType> types);
    bool match(TokenType type);
    const Token& current() const;
    const Token& previous() const;
    Token consume(TokenType token, const std::string& error);    
    bool end() const;
    bool check(const TokenType& type) const;
    Token advance();
};

#endif