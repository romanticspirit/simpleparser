//
// Created by stephen on 2017/12/30.
//
#include "Lexer.h"
#include "catch.h"


TEST_CASE( "Lexer Next Token of '+()(-||'", "[single-file]" ) {
    std::string input = "+()(-||";
    Lexer lexer(input);
    Token tokenExpected[] = {
            {TokenEnum::PLUS, "+"},
            {TokenEnum::LPAREN, "("},
            {TokenEnum::RPAREN, ")"},
            {TokenEnum::LPAREN, "("},
            {TokenEnum::MINUS, "-"},
            {TokenEnum::OR, "||"},
    };

    for (int i = 0; i < sizeof(tokenExpected)/ sizeof(tokenExpected[0]); ++i)
    {
        Token token = lexer.nextToken();
        REQUIRE (token.type == tokenExpected[i].type);
        REQUIRE (token.literal == tokenExpected[i].literal);
    }
}

TEST_CASE("Lexer of  '(code == 5) && (name=='s' || name == 'j')", "[single-file]" ){
    std::string input = "(code == 5) && (name=='s' || name == 'j')";
    Lexer lexer(input);
    Token tokenExpected[] = {
            {TokenEnum::LPAREN, "("},
            {TokenEnum::IDENT, "code"},
            {TokenEnum::EQ, "=="},
            {TokenEnum::INT, "5"},
            {TokenEnum::RPAREN, ")"},
            {TokenEnum::AND, "&&"},
            {TokenEnum::LPAREN, "("},
            {TokenEnum::IDENT, "name"},
            {TokenEnum::EQ, "=="},
            {TokenEnum::STRING, "s"},
            {TokenEnum::OR, "||"},
            {TokenEnum::IDENT, "name"},
            {TokenEnum::EQ, "=="},
            {TokenEnum::STRING, "j"},
            {TokenEnum::RPAREN, ")"},

    };

    for (int i = 0; i < sizeof(tokenExpected)/ sizeof(tokenExpected[0]); ++i)
    {
        Token token = lexer.nextToken();
        REQUIRE (token.type == tokenExpected[i].type);
        REQUIRE (token.literal == tokenExpected[i].literal);
    }
}
