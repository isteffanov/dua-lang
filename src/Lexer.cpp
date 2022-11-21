#include "Lexer.h"

#include<iostream>
#include<vector>
#include<regex>

Lexer::Lexer(std::string source) 
{
    this->mSource = source;
    this->mTokens = std::vector<Token>();
    this->mFrom = 0;
    this->mPos = 0;
    this->mLine = 1;
}

std::vector<Token> Lexer::getTokens() const
{
    return this->mTokens;
}

void Lexer::scanTokens() 
{
    while (!end()) 
    {
        scanToken();
    } 
    addToken(TokenType::EOFLITERAL);
}

void Lexer::scanToken() 
{
    char point = advance();

    switch (point)
    {
    case '(': addToken(TokenType::LEFT_PAREN); break;
    case ')': addToken(TokenType::RIGHT_PAREN); break;
    case '{': addToken(TokenType::LEFT_BRACE); break;
    case '}': addToken(TokenType::RIGHT_BRACE); break;
    case ',': addToken(TokenType::COMMA); break;
    case '.': addToken(TokenType::DOT); break;
    case '-': addToken(TokenType::MINUS); break;
    case '+': addToken(TokenType::PLUS); break;
    case ';': addToken(TokenType::SEMICOLON); break;
    case '/': addToken(TokenType::SLASH); break;
    case '*': addToken(TokenType::STAR); break;

    case '!': addToken(matchPeek('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
    case '=': addToken(matchPeek('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
    case '>': addToken(matchPeek('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
    case '<': addToken(matchPeek('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;

    case ' ':
    case '\t':
    case '\r':
        break;
    case '\n':
        mLine++;
        break;

    default:
        if (point == '"') 
        {
            consumeString();
        }
        else if (isdigit(point))
        {
            consumeNumber();
        }
        else if (isalpha(point))
        {
            consumeIdentifier();
        }
        else
        {
            //TODO: 
            std::cout << "error scanning" << std::endl;
        }
    }

    this->mFrom = this->mPos;
}

void Lexer::addToken(TokenType type) {
    addToken(type, {});
}

void Lexer::addToken(TokenType type, literal_t literal)
{
    std::string lexeme = current();
    mTokens.push_back(Token(this->mLine, type, lexeme, literal));
}

void Lexer::consumeString() 
{
    while (peek() != '"' && !end()) 
    {
        if (peek() == '\n') mLine++;
        advance();
    }

    if (end()) 
    {
        //TODO: error
        return;
    }

    advance();
    
    std::string string = current();
    string = string.substr(1, string.length() - 2);
    addToken(TokenType::STRING, string);
}

void Lexer::consumeNumber() 
{
    std::smatch match;
    std::regex integerRe("[0-9]+");
    std::regex floatRe("[0-9]+.[0-9]+");

    std::string rest = this->mSource.substr(this->mFrom);
    
    if (std::regex_search(rest, match, integerRe)) 
    {
        addToken(TokenType::NUMBER, std::stoi(match[0].str()) + 1);

    }
    else if (std::regex_search(rest, match, floatRe)) 
    {
        addToken(TokenType::NUMBER, std::stof(match[0].str()));
    }
    else
    {
        //throw exception
        std::cout << "no number\n";
    }
}

void Lexer::consumeIdentifier()
{
    while (isAlpha(peek()))
        advance();

    std::string identifier = current();
    keyword_map_t keywords = getKeywordsMap();

    if (keywords.find(identifier) == keywords.end()) 
    {
        addToken(TokenType::IDENTIFIER, identifier);
    }
    else
    {
        addToken(keywords.at(identifier));
    }

    std::cout << peek() << std::endl;
}

inline char Lexer::advance()
{
    //TODO handle out_of_range possible exception   
    return this->mSource.at(this->mPos++);
}

inline std::string Lexer::current() const
{
    return this->mSource.substr(this->mFrom, this->mPos - this->mFrom);
}


inline char Lexer::peek() const
{
    return this->mSource.at(this->mPos);

}

inline bool Lexer::matchPeek(char expected)
{
    if (end()) return false;
    if (mSource.at(this->mPos) != expected) return false;

    this->mPos++;
    return true;
}

inline bool Lexer::end() const
{
    return this->mPos >= this->mSource.length();
}

inline bool Lexer::isAlpha(char c) const
{
    return  ('a' <= c && c <= 'z') ||
            ('A' <= c && c <= 'Z') ||
            c == '_';
}

inline keyword_map_t Lexer::getKeywordsMap() const
{
    keyword_map_t keywords;
    keywords.emplace("and", TokenType::AND);
    keywords.emplace("class", TokenType::CLASS);
    keywords.emplace("def", TokenType::DEF);
    keywords.emplace("else", TokenType::ELSE);
    keywords.emplace("false", TokenType::FALSE);
    keywords.emplace("for", TokenType::FOR);
    keywords.emplace("if", TokenType::IF);
    keywords.emplace("nil", TokenType::NIL);
    keywords.emplace("or", TokenType::OR);
    keywords.emplace("print", TokenType::PRINT);
    keywords.emplace("return", TokenType::RETURN);
    keywords.emplace("super", TokenType::SUPER);
    keywords.emplace("this", TokenType::THIS);
    keywords.emplace("true", TokenType::TRUE);
    keywords.emplace("var", TokenType::VAR);
    keywords.emplace("while", TokenType::WHILE);

    return keywords;
}