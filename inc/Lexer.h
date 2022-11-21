#ifndef LEXER_H
#define LEXER_H

#include "Token.h"

#include <string>
#include <vector>
#include <unordered_map>

typedef std::unordered_map<std::string, TokenType> keyword_map_t;

class Lexer 
{

private:
    std::string mSource;
    std::vector<Token> mTokens;

    int mFrom;
    int mPos;
    int mLine;

public:
    Lexer(std::string source);
    void scanTokens();
    std::vector<Token> getTokens() const;

private: 
    void scanToken();
    void addToken(TokenType type);
    void addToken(TokenType type, literal_t literal);

    void consumeString();
    void consumeNumber();
    void consumeIdentifier();

    inline char advance();
    inline std::string current() const;
    inline char peek() const;
    inline bool matchPeek(char expected);
    inline bool end() const;
    // inline std::string currentToken() const;
    inline bool isAlpha(char c) const;

    inline keyword_map_t getKeywordsMap() const;
};

#endif // LEXER_H
