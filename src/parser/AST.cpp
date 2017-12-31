//
// Created by stephen on 2017/12/30.
//

#include <sstream>
#include "AST.h"

Expression::~Expression() {

}

InfixExpression::InfixExpression(const Token &token, const std::string &oper, Expression *left, Expression *right)
        : token(token), oper(oper), left(left), right(right) {

}

std::string InfixExpression::tokenLiteral() {
    return this->token.literal;
}

std::string InfixExpression::toString() {
    std::ostringstream stringStream;
    stringStream<<"(";
    stringStream<<this->left->toString();
    stringStream<<" " << this->oper << " ";
    stringStream<<this->right->toString();
    stringStream<<")";
    return stringStream.str();
}

InfixExpression::~InfixExpression() {
    if (left != NULL) {
        delete left;
        left = NULL;
    }

    if (right != NULL) {
        delete right;
        right = NULL;
    }


}

IntegerLiteral::IntegerLiteral(Token token, int value)
        : token(token), value(value) {

}

std::string IntegerLiteral::tokenLiteral() {
    return this->token.literal;
}

std::string IntegerLiteral::toString() {
    return this->token.literal;
}

IntegerLiteral::~IntegerLiteral() {

}

std::string PrefixExpression::tokenLiteral() {
    return this->token.literal;
}

std::string PrefixExpression::toString() {
    std::ostringstream stringStream;
    stringStream<<"(";
    stringStream<<this->oper;
    stringStream<<this->right->toString();
    stringStream<<")";
    return stringStream.str();
}

PrefixExpression::~PrefixExpression() {
    if (this->right == NULL) {
        delete this->right;
        right = NULL;
    }
}

PrefixExpression::PrefixExpression(Token token, const std::string &oper, Expression *pExpression)
        : token(token), oper(oper), right(pExpression) {

}

std::string StringLiteral::tokenLiteral() {
    return this->token.literal;
}

std::string StringLiteral::toString() {
    return this->token.literal;
}

StringLiteral::~StringLiteral() {

}

StringLiteral::StringLiteral(Token token, const std::string &value)
        : token(token), value(value) {

}


std::string Identifier::tokenLiteral() {
    return this->token.literal;
}

std::string Identifier::toString() {
    return this->value;
}

Identifier::~Identifier() {

}

Identifier::Identifier(Token token, const std::string &literal)
        : token(token), value(literal) {

}


