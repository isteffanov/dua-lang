#ifndef EXPR_H
#define EXPR_H

#include "Token.h"

#include <memory>
#include <vector>

class Expr;
typedef std::shared_ptr<Expr> ExprPtr;

class Literal;
class Binary;
class Unary;
class Grouping;

class Expr : public ExprPtr
{
public:

    class Visitor {
    public:
        virtual void visit(Literal* expr) { }
        virtual void visit(Binary* expr) { }
        virtual void visit(Unary* expr) { }
        virtual void visit(Grouping* expr) { }


    }; //class Visitor<R>
    virtual void accept(Visitor& visitor) { }
    virtual ~Expr() {}

};

class Literal : public Expr 
{
public: 
    literal_t value;
    Literal(literal_t _value = {}): value(_value) {}
    virtual ~Literal() {}
    virtual void accept(Expr::Visitor& visitor) override {
        visitor.visit(this);
    }
};

class Binary : public Expr 
{
public:
    ExprPtr lhs;
    TokenType op;
    ExprPtr rhs;

    Binary(
        const ExprPtr& _lhs = nullptr,
        TokenType _op = TokenType::EOFLITERAL,
        const ExprPtr& _rhs = nullptr
    ) : lhs(_lhs), op(_op), rhs(_rhs) { }

    virtual ~Binary() {}
    virtual void accept(Expr::Visitor& visitor) override {
        visitor.visit(this);
    }
    
};

class Unary : public Expr
{
public:
    TokenType op;
    ExprPtr rhs;

    Unary(
        TokenType _op = TokenType::EOFLITERAL,
        const ExprPtr& _rhs = nullptr
    ) : op(_op), rhs(_rhs) { }

    virtual ~Unary() {}
    virtual void accept(Expr::Visitor& visitor) override {
        visitor.visit(this);
    }
    
};

class Grouping : public Expr 
{
public:
    ExprPtr expression;

    Grouping(
        const ExprPtr& _expression
    ) : expression(_expression) { }

    virtual ~Grouping() {}
    virtual void accept(Expr::Visitor& visitor) override {
        visitor.visit(this);
    }
    
};

#endif