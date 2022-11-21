#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <ostream>

enum TokenType 
{
// Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

// One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

// Literals.
  IDENTIFIER, STRING, NUMBER,

// Keywords.
  AND, CLASS, DEF, ELSE, FALSE, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  EOFLITERAL
};

// std::vector<std::string> tokenTypeToStr({
//     "left_paren", "right_paren", "left_brace", "right_brace",
//     "comma", "dot", "minus", "plus", "semicolon", "slash", "star",

//     "bang", "bang_equal",
//     "equal", "equal_equal",
//     "greater", "greater_equal",
//     "less", "less_equal",

//     "identifier", "string", "number",

//     "and", "class", "def", "else", "false", "for", "if",
//     "nil", "or", "print", "return", "super", "this", 
//     "true", "var", "while"
// });

typedef std::variant<std::string, float, int> literal_t;
typedef std::string lexeme_t;

class Token 
{

private:
    const int mLine;
    const TokenType mTokenType;
    const lexeme_t mLexeme;
    const literal_t mLiteral;

public:
    Token(
        int line,
        TokenType type,
        std::string lexeme,
        literal_t literal
    );

    const literal_t literal() const;
    const TokenType& tokenType() const;
    std::string toString() const;


};

std::ostream& operator<<(std::ostream& out, const Token& token);

#endif