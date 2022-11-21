#include "Parser.h"
#include "Token.h"
#include "Expr.h"

#include <vector>
#include <memory>
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : mTokens(tokens), mPos(0) { }

ExprPtr Parser::parse() 
{
    return program();
}

ExprPtr Parser::program()
{
    return expression();
}

ExprPtr Parser::expression()
{
	auto result = equality();
	return result;
}

ExprPtr Parser::equality()
{
    ExprPtr left = comparison();

    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL }))
    {
        const TokenType op = previous().tokenType();
        ExprPtr right = comparison();
        left = std::make_shared<Binary>(left, op, right);
    }

    return left;
}

ExprPtr Parser::comparison()
{
    ExprPtr left = sum();
    while (match({ TokenType::LESS, TokenType::LESS_EQUAL,
                 TokenType::GREATER, TokenType::GREATER_EQUAL }))
    {
        const TokenType op = previous().tokenType();
        ExprPtr right = sum();
        left = std::make_shared<Binary>(left, op, right);
    }

    return left;
}

ExprPtr Parser::sum()
{
    ExprPtr left = product();

    while(match({TokenType::PLUS, TokenType::MINUS}))
    {
        const TokenType op = previous().tokenType();
        ExprPtr right = product();
        left = std::make_shared<Binary>(left, op, right);
    }

    return left;
}

ExprPtr Parser::product()
{
    ExprPtr left = unary();

    while(match({TokenType::STAR, TokenType::SLASH}))
    {
        const TokenType op = previous().tokenType();
        ExprPtr right = unary();
        left = std::make_shared<Binary>(left, op, right);
    }

    return left;
}


ExprPtr Parser::unary()
{
    if (match({TokenType::BANG, TokenType::MINUS}))
    {
        const TokenType op = previous().tokenType();
        ExprPtr right = sum();
        ExprPtr expr = std::make_shared<Unary>(op, right);

        return expr;
    }

    return primary();
}

ExprPtr Parser::primary()
{
    if (match(TokenType::TRUE)) 
        return std::make_shared<Literal>(true);
    if (match(TokenType::FALSE))
        return std::make_shared<Literal>(false);

    if (match(TokenType::STRING)){
        return std::make_shared<Literal>(std::get<std::string>(previous().literal()));
    }

    if (match(TokenType::NUMBER)){
        return std::make_shared<Literal>(std::get<int>(previous().literal()));
    }
    
    if (match(TokenType::LEFT_PAREN)) {
        ExprPtr expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_shared<Grouping>(expr);
    }

    std::cout << "error parsing\n";

    return nullptr;
}   

bool Parser::match(std::initializer_list<TokenType> types)
{
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }

    return false;

}

bool Parser::match(TokenType type)
{
    return match({type});
}

Token Parser::advance() 
{
    if (!end()) mPos++;
    return previous();
  }

const Token& Parser::current() const
{
    return mTokens.at(mPos);
}

const Token& Parser::previous() const
{
    return mTokens.at(mPos - 1);
}

Token Parser::consume(TokenType token, const std::string& error)
{
    if (check(token)) return advance();
    
    std::cout << error << std::endl;
}

bool Parser::end() const
{
    return current().tokenType() == TokenType::EOFLITERAL;
}

bool Parser::check(const TokenType& type) const
{
    if (end()) return false;
    return type == current().tokenType();
}