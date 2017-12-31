//
// Created by stephen on 2017/12/30.
//

#ifndef SIMPLEINTERPRETER_LEXER_H
#define SIMPLEINTERPRETER_LEXER_H

#include <string>
#include <memory>
#include <Token.h>

class Lexer{
public:
    Lexer(const std::string& input);

    Token nextToken();
private:
    void readChar();
    std::string readString();
    std::string readIdentify();
    std::string readNumber();
    char peekChar();
    void skipWhiteSpace();
    bool isDigit(char ch);
    bool isLetter(char ch);
    void assignToken(TokenEnum tokenEnum, const std::string& literal, Token& token);

private:
    std::string input;
    int inputLength;
    int position;
    int readPosition;
    char ch;
};
#endif //SIMPLEINTERPRETER_LEXER_H
