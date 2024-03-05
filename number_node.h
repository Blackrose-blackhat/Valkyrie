#pragma once

#include "ast_node.h"
#include "./lexer.cpp"
#include <utility>

class NumberNode : public ASTNode
{
public:
    Token token;

    explicit NumberNode(Token token) : token(std::move(token)) {}
};