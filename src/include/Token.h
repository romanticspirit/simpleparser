#ifndef SIMPLEINTERPRETER_TOKEN_H
#define SIMPLEINTERPRETER_TOKEN_H

#include <string>

typedef std::string TokenType;

enum TokenEnum {
    ILLEGAL=0,
    EOF_L =1,

    IDENT =2,// add, foobar, x, y, ...
    INT =3,  // 1343456

    PLUS=4,
    MINUS=5,
    BANG=6,
    DIVIDE=7,
    MULTIPLY=8,

    LT=9,
    GT=10,

    EQ=11,
    NOT_EQ=12,
    GE=13,
    LE=14,

    AND=15,
    OR=16,

    LPAREN=17,
    RPAREN=18,
    STRING=19
};

struct Token{
    TokenEnum type;
    std::string literal;
};


#endif
