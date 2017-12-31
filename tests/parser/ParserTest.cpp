//
// Created by stephen on 2017/12/31.
//

#include "catch.h"
#include "Lexer.h"
#include "Parser.h"

TEST_CASE( "SimpleTest of  'code == 5'", "[single-file]" ){
    Lexer lexer("code == 5");
    Parser parser(lexer);
    Expression* expr = parser.parse();
    InfixExpression* infixExpression= dynamic_cast<InfixExpression*>(expr);
    REQUIRE(infixExpression != NULL);
    Identifier* identifier = dynamic_cast<Identifier*>(infixExpression->left);
    IntegerLiteral* integerLiteral = dynamic_cast<IntegerLiteral*>(infixExpression->right);
    REQUIRE(identifier != NULL);
    REQUIRE(integerLiteral != NULL);
    delete expr;
}

TEST_CASE("SimpleTest of  'code == 5 && name=='stephen''", "[single-file]" ){
    Lexer lexer("code == 5 && name == 'stephen'");
    Parser parser(lexer);
    Expression* expr = parser.parse();
    InfixExpression* infixExpression= dynamic_cast<InfixExpression*>(expr);
    REQUIRE(infixExpression != NULL);
    REQUIRE(infixExpression->token.type == AND);

    InfixExpression* left = dynamic_cast<InfixExpression*>(infixExpression->left);
    InfixExpression* right = dynamic_cast<InfixExpression*>(infixExpression->right);
    REQUIRE(left != NULL);
    REQUIRE(right != NULL);
    delete expr;
}


TEST_CASE("SimpleTest of  '(code == 5) && (name=='s' || name == 'j')", "[single-file]" ){
    Lexer lexer("(code == 5) && (name == 's' || name == 'j')");
    Parser parser(lexer);
    Expression* expr = parser.parse();
    InfixExpression* infixExpression= dynamic_cast<InfixExpression*>(expr);
    REQUIRE(infixExpression != NULL);
    REQUIRE(infixExpression->token.type == AND);

    InfixExpression* left = dynamic_cast<InfixExpression*>(infixExpression->left);
    InfixExpression* right = dynamic_cast<InfixExpression*>(infixExpression->right);
    REQUIRE(left != NULL);
    REQUIRE(right != NULL);

    REQUIRE(right->token.type == OR);
    delete expr;
}

TEST_CASE("SimpleTest of  '((code == 5) && (name=='s' || name == 'j'))", "[single-file]" ){
    Lexer lexer("((code == 5) && (name == 's' || name == 'j'))");
    Parser parser(lexer);
    Expression* expr = parser.parse();
    InfixExpression* infixExpression= dynamic_cast<InfixExpression*>(expr);
    REQUIRE(infixExpression != NULL);
    REQUIRE(infixExpression->token.type == AND);

    InfixExpression* left = dynamic_cast<InfixExpression*>(infixExpression->left);
    InfixExpression* right = dynamic_cast<InfixExpression*>(infixExpression->right);
    REQUIRE(left != NULL);
    REQUIRE(right != NULL);

    REQUIRE(right->token.type == OR);
    delete expr;
}
