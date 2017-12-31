//
// Created by stephen on 2017/12/30.
//

#ifndef SIMPLEINTERPRETER_AST_H
#define SIMPLEINTERPRETER_AST_H

#include <string>
#include "Token.h"

class Expression{
public:
    virtual  std::string tokenLiteral () =0;

    virtual ~Expression() = 0;

    virtual std::string toString() = 0;
};

struct InfixExpression : public Expression
{
    InfixExpression(const Token& token, const std::string& oper, Expression* left, Expression* right);
    virtual std::string tokenLiteral();
    virtual std::string toString();
    virtual ~InfixExpression();


    Token token;

    std::string oper;
    Expression* left;
    Expression* right;
};

class IntegerLiteral : public Expression{
public:
    IntegerLiteral(Token token, int value);
    virtual std::string tokenLiteral();
    virtual std::string toString();
    virtual ~IntegerLiteral();
private:
    Token token;
    int value;
};

class StringLiteral : public Expression{
public:
    StringLiteral(Token token, const std::string &value);

    virtual std::string tokenLiteral();
    virtual std::string toString();
    virtual ~StringLiteral();
private:
    Token token;
    std::string value;
};

class PrefixExpression : public Expression{
public:
    PrefixExpression(Token token, const std::string& oper, Expression *pExpression);

    virtual std::string tokenLiteral();
    virtual std::string toString();
    virtual ~PrefixExpression();
private:
    Token token;
    std::string oper;
    Expression* right;
};

class Identifier : public Expression{
public:
    Identifier(Token token, const std::string& literal);

    virtual std::string tokenLiteral();
    virtual std::string toString();
    virtual ~Identifier();
private:
    Token token;
    std::string value;
};

#endif //SIMPLEINTERPRETER_AST_H
