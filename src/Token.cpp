#include"Token.h"

#include <vector>

Token::Token(
    int line,
    TokenType type,
    lexeme_t lexeme,
    literal_t literal
) : 
    mLine(line), 
    mTokenType(type), 
    mLexeme(lexeme), 
    mLiteral(literal) { }


std::string Token::toString() const
{
    return std::to_string(this->mTokenType) + " " + this->mLexeme;
}

const literal_t Token::literal() const
{
    return mLiteral;
}

const TokenType& Token::tokenType() const
{
    return mTokenType;
}

std::ostream& operator<<(std::ostream& out, const Token& token)
{
    out << token.toString();
    return out;
}



