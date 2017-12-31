//
// Created by stephen on 2017/12/30.
//
#include <type_traits>
#include "Lexer.h"


Lexer::Lexer(const std::string &input) {
    this->input = input;
    this->inputLength = input.length();
    this->readPosition = 0;
    this->position = -1;
    this->readChar();
}

Token Lexer::nextToken() {

    this->skipWhiteSpace();
    Token token;
    switch (this->ch) {
        case '=': {
            if (this->peekChar() == '=') {
                this->readChar();
                assignToken(TokenEnum::EQ, "==", token);
            }
            else{
                assignToken(TokenEnum::ILLEGAL, "=", token);
            }

            break;
        }
        case '+':
            assignToken(TokenEnum::PLUS, "+", token);
            break;
        case '-':
            assignToken(TokenEnum::MINUS, "-", token);
            break;
        case '!':
            if (this->peekChar() == '=') {
                this->readChar();
                assignToken(TokenEnum::NOT_EQ, "!=", token);
            } else {
                assignToken(TokenEnum::BANG, "!", token);
            }
            break;

        case '/':
            assignToken(TokenEnum::DIVIDE, "/", token);
            break;

        case '*':
            assignToken(TokenEnum::MULTIPLY, "*", token);
            break;

        case '<':
            if (this->peekChar() == '=') {
                this->readChar();
                assignToken(TokenEnum::LE, "<=", token);
            } else {
                assignToken(TokenEnum::LT, "<", token);
            }
            break;
        case '>':
            if (this->peekChar() == '=') {
                this->readChar();
                assignToken(TokenEnum::GE, ">=", token);
            } else {
                assignToken(TokenEnum::GT, ">", token);
            }
            break;
        case '\'':
            assignToken(TokenEnum::STRING, this->readString(), token);
            break;

        case '(':
            assignToken(TokenEnum::LPAREN, "(", token);
            break;
        case ')':
            assignToken(TokenEnum::RPAREN, ")", token);
            break;
        case '&':
            if (this->peekChar() == '&') {
                this->readChar();
                assignToken(TokenEnum::AND, "&&", token);
            }
            else{
                assignToken(TokenEnum::ILLEGAL, "&", token);
            }
            break;
        case '|':
            if (this->peekChar() == '|') {
                this->readChar();
                assignToken(TokenEnum::OR, "||", token);
            }
            else{
                assignToken(TokenEnum::ILLEGAL, "|", token);
            }
            break;
        case 0:
            assignToken(TokenEnum::EOF_L, "", token);
            break;
        default:
            if (isLetter(this->ch)) {
                assignToken(TokenEnum::IDENT, this->readIdentify(), token);
                return token;
            } else if (isDigit(this->ch)) {
                assignToken(TokenEnum::INT, this->readNumber(), token);
                return token;
            } else {
                char charArray[1];
                charArray[0] = this->ch;
                assignToken(TokenEnum::ILLEGAL, charArray, token);
            }
            break;
    }

    this->readChar();
    return token;
}

void Lexer::readChar() {
    if (this->readPosition >= this->inputLength) {
        this->ch = 0;
    } else {
        this->ch = this->input[this->readPosition];
    }

    this->position = this->readPosition;
    this->readPosition++;
}

std::string Lexer::readString() {
    int oldPosition = this->position + 1;
    while (true) {
        if (this->ch == '\\') {
            this->readChar();
        }
        this->readChar();
        if (this->ch == '\'') {
            break;
        }
    }

    return this->input.substr(oldPosition, this->position - oldPosition);
}

std::string Lexer::readIdentify() {
    int oldPosition = this->position;
    while (isLetter(this->ch) || isDigit(this->ch)) {
        this->readChar();
    }
    return this->input.substr(oldPosition, this->position - oldPosition);
}

std::string Lexer::readNumber() {
    int oldPosition = this->position;

    while (isDigit(this->ch)) {
        this->readChar();
    }
    return this->input.substr(oldPosition, this->position - oldPosition);
}

char Lexer::peekChar() {
    if (this->readPosition >= this->inputLength) {
        return 0;
    } else {
        return this->input[this->readPosition];
    }
}

void Lexer::skipWhiteSpace() {
    while (this->ch == ' ' || this->ch == '\t' || this->ch == '\n' || this->ch == '\r') {
        this->readChar();
    }
}

bool Lexer::isDigit(char ch) {
    return '0' <= ch && ch <= '9';
}

bool Lexer::isLetter(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

void Lexer::assignToken(TokenEnum tokenEnum, const std::string &literal, Token &token) {
    token.type = tokenEnum;
    token.literal = literal;
}
