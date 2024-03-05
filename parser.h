#pragma once
#include "./lexer.cpp"
#include "number_node.h"
#include <memory>

class Parser
{
private:
    Lexer lexer;
    Token currentToken;

    std::unique_ptr<ASTNode> parseNumber();
    std::unique_ptr<ASTNode> parseExpression();

public:
    explicit Parser(Lexer lexer);

    std::unique_ptr<ASTNode> parse();
};