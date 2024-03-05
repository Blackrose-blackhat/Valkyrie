#pragma once
#include "ast_node.h"
#include <memory>
#include "lexer.cpp"
class BinaryOperatorNode : public ASTNode
{
public:
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    Token op;

    BinaryOperatorNode(std::unique_ptr<ASTNode> left, Token op, std::unique_ptr<ASTNode> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}
};