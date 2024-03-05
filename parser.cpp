#include "./parser.h"
#include <stdexcept>
#include "binary_operator_node.h"
using namespace std;
std::unique_ptr<ASTNode> Parser::parseNumber()
{
    // Check if current token is an integer
    if (currentToken.type != TokenType::INTEGER)
    {
        // Throw error if not an integer
        throw std::runtime_error("Expected an integer");
    }

    // Create a unique pointer for ASTNode and initialize it as NumberNode
    auto node = std::make_unique<NumberNode>(currentToken);

    // Get next token from lexer
    currentToken = lexer.getNextToken();

    // Return unique_ptr with NumberNode
    return node;
}

unique_ptr<ASTNode> Parser::parseExpression()
{
    
}

std::unique_ptr<ASTNode> Parser::parseExpression()
{
    auto left = parseNumber();

    while (currentToken.type == TokenType::PLUS ||
           currentToken.type == TokenType::MINUS ||
           currentToken.type == TokenType::MULTIPLY ||
           currentToken.type == TokenType::DIVIDE)
    {
        Token op = currentToken;
        currentToken = lexer.getNextToken();
        auto right = parseNumber();
        left = std::make_unique<BinaryOperatorNode>(std::move(left), op, std::move(right));
    }

    return left;
}

Parser::Parser(Lexer lexer) : lexer(std::move(lexer)), currentToken(this->lexer.getNextToken()) {}

std::unique_ptr<ASTNode> Parser::parse()
{
    return parseExpression();
}