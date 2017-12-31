//
// Created by stephen on 2017/12/30.
//

#include "Parser.h"
#include <sstream>

Parser::Parser(Lexer &lexer) : lexer(lexer) {
    this->nextToken();
    this->nextToken();

    priorityMap.insert(std::make_pair(TokenEnum::AND, AND));
    priorityMap.insert(std::make_pair(TokenEnum::OR, AND));
    priorityMap.insert(std::make_pair(TokenEnum::EQ, EQUALS));
    priorityMap.insert(std::make_pair(TokenEnum::NOT_EQ, EQUALS));
    priorityMap.insert(std::make_pair(TokenEnum::LT, COMPARE));
    priorityMap.insert(std::make_pair(TokenEnum::GT, COMPARE));
    priorityMap.insert(std::make_pair(TokenEnum::LE, COMPARE));
    priorityMap.insert(std::make_pair(TokenEnum::GE, COMPARE));
    priorityMap.insert(std::make_pair(TokenEnum::PLUS, SUM));
    priorityMap.insert(std::make_pair(TokenEnum::MINUS, SUM));
    priorityMap.insert(std::make_pair(TokenEnum::DIVIDE, PRODUCT));
    priorityMap.insert(std::make_pair(TokenEnum::MULTIPLY, PRODUCT));

    prefixMap.insert(std::make_pair(TokenEnum::IDENT, &Parser::parseIdentifier));
    prefixMap.insert(std::make_pair(TokenEnum::INT, &Parser::parseIntegerLiteral));
    prefixMap.insert(std::make_pair(TokenEnum::BANG, &Parser::parsePrefixExpression));
    prefixMap.insert(std::make_pair(TokenEnum::MINUS, &Parser::parsePrefixExpression));
    prefixMap.insert(std::make_pair(TokenEnum::LPAREN, &Parser::parseGroupedExpression));
    prefixMap.insert(std::make_pair(TokenEnum::STRING, &Parser::parserStringLiteral));

    infixMap.insert(std::make_pair(TokenEnum::PLUS, &Parser::parseInfixExpression));
    infixMap.insert(std::make_pair(TokenEnum::MINUS, &Parser::parseInfixExpression));
    infixMap.insert(std::make_pair(TokenEnum::DIVIDE, &Parser::parseInfixExpression));
    infixMap.insert(std::make_pair(TokenEnum::MULTIPLY, &Parser::parseInfixExpression));
    infixMap.insert(std::make_pair(TokenEnum::EQ, &Parser::parseInfixExpression));
    infixMap.insert(std::make_pair(TokenEnum::NOT_EQ, &Parser::parseInfixExpression));
    infixMap.insert(std::make_pair(TokenEnum::LT, &Parser::parseInfixExpression));
    infixMap.insert(std::make_pair(TokenEnum::GT, &Parser::parseInfixExpression));
    infixMap.insert(std::make_pair(TokenEnum::LE, &Parser::parseInfixExpression));
    infixMap.insert(std::make_pair(TokenEnum::GE, &Parser::parseInfixExpression));
    infixMap.insert(std::make_pair(TokenEnum::AND, &Parser::parseInfixExpression));
    infixMap.insert(std::make_pair(TokenEnum::OR, &Parser::parseInfixExpression));
}

const std::vector<std::string> &Parser::errorList() {
    return errors;
}

Expression *Parser::parse() {
    Expression* expr = parseExpression(LOWEST);
    this->nextToken();
    while (this->curToken.type != EOF_L)
    {
        expr = parseInfixExpression(expr);
        this->nextToken();
    }
    return expr;
}

void Parser::peekErrors(TokenEnum tokenType) {
    std::ostringstream stringStream;
    stringStream << "expected next token to be " << tokenType << ", got " << this->peekToken.type << " instead";
    this->errors.push_back(stringStream.str());
}

void Parser::nextToken() {
    this->curToken = this->peekToken;
    this->peekToken = this->lexer.nextToken();
}

Expression *Parser::parseIntegerLiteral() {
    int value = atoi(this->curToken.literal.c_str());
    return new IntegerLiteral(this->curToken, value);
}

Expression *Parser::parseInfixExpression(Expression *left) {
    Token token = this->curToken;
    std::string oper = this->curToken.literal;

    int precedence = this->curPrecedence();
    this->nextToken();
    Expression *right = this->parseExpression(precedence);
    return new InfixExpression(token, oper, left, right);
}


Expression *Parser::parseGroupedExpression() {
    this->nextToken();
    Expression* expr = this->parseExpression(LOWEST);

    if (!this->expectedPeek(TokenEnum::RPAREN)){
        return NULL;
    }

    return expr;
}

Expression *Parser::parsePrefixExpression() {

    Token curToken = this->curToken;
    std::string oper = this->curToken.literal;

    this->nextToken();
    Expression* right = this->parseExpression(PREFIX);

    return new PrefixExpression(curToken, oper, right);
}

Expression *Parser::parseExpression(int precedence) {
    std::map<TokenEnum, ParseFunction>::iterator itr = prefixMap.find(this->curToken.type);
    if (itr == prefixMap.end()) {
        this->noPrefixParseFunctionError(this->curToken.type);
        return NULL;
    }

    Expression *expr = (this->*(itr->second))();
    while (precedence < this->peekPrecedence()) {
        std::map<TokenEnum, InfixParseFunction >::iterator infixItr = infixMap.find(this->peekToken.type);
        if (infixItr == infixMap.end())
        {
            return expr;
        }

        this->nextToken();
        expr = (this->*(infixItr->second))(expr);
    }

    return expr;
}

Expression *Parser::parseIdentifier() {
    return new Identifier(this->curToken, this->curToken.literal);
}

Expression *Parser::parserStringLiteral() {
    return new StringLiteral(this->curToken, this->curToken.literal);
}

int Parser::curPrecedence() {
    std::map<TokenEnum, PRIORITY>::iterator itr = priorityMap.find(this->curToken.type);
    if (itr != priorityMap.end()) {
        return itr->second;
    }

    return LOWEST;
}

void Parser::noPrefixParseFunctionError(TokenEnum anEnum) {
    std::ostringstream stringStream;
    stringStream << "no prefix parse function for " << anEnum << "found";
    this->errors.push_back(stringStream.str());
}

int Parser::peekPrecedence() {
    std::map<TokenEnum, PRIORITY>::iterator itr = priorityMap.find(this->peekToken.type);
    if (itr != priorityMap.end()) {
        return itr->second;
    }

    return LOWEST;
}

bool Parser::expectedPeek(TokenEnum t) {
    if (this->peekToken.type == t) {
        this->nextToken();
        return true;
    } else {
        this->peekError(t);
        return false;
    }
}

void Parser::peekError(TokenEnum t) {
    std::ostringstream stringStream;
    stringStream << "expected next token to be " << t << " got "<<this->peekToken.type;
    this->errors.push_back(stringStream.str());
}
