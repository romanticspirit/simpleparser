//
// Created by stephen on 2017/12/30.
//

#ifndef SIMPLEINTERPRETER_PARSER_H
#define SIMPLEINTERPRETER_PARSER_H

#include <vector>
#include <string>
#include <map>

#include "Lexer.h"
#include "AST.h"
#include "Token.h"

class Parser {
public:
    enum PRIORITY {LOWEST=0, AND, EQUALS, COMPARE, SUM, PRODUCT, PREFIX};
    Parser(Lexer& lexer);
    const std::vector<std::string>& errorList();
    Expression* parse ();
private:
    void peekErrors(TokenEnum tokenType);
    void nextToken();

    Expression* parseIntegerLiteral();
    Expression* parseInfixExpression(Expression* left);
    Expression* parseGroupedExpression();
    Expression* parsePrefixExpression();
    Expression* parserStringLiteral();
    Expression *parseExpression(int i);
    Expression* parseIdentifier();
    int curPrecedence();
    int peekPrecedence();
    bool expectedPeek(TokenEnum anEnum);
    void peekError(TokenEnum anEnum);
    void noPrefixParseFunctionError(TokenEnum anEnum);
private:
    Lexer& lexer;
    Token curToken;
    Token peekToken;
    std::vector<std::string> errors;
    typedef Expression* (Parser::*ParseFunction)();

    typedef Expression* (Parser::*InfixParseFunction)(Expression* left);
    std::map<TokenEnum, ParseFunction> prefixMap;
    std::map<TokenEnum, InfixParseFunction> infixMap;

    std::map<TokenEnum, PRIORITY> priorityMap;



};


#endif //SIMPLEINTERPRETER_PARSER_H
