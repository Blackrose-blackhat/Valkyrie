#include "lexer.cpp"
#include <memory>
class ASTNode
{
public:
    virtual ~ASTNode() = default;
};

class NumberNode : public ASTNode
{
public:
    Token token;

    explicit NumberNode(Token token) : token(std::move(token)) {}
};

class Parser
{
private:
    Lexer lexer;
    Token currentToken;

    std::unique_ptr<ASTNode> parseNumber()
    {
        if (currentToken.type != TokenType::INTEGER)
        {
            throw std::runtime_error("Expected an integer");
        }

        auto node = std::make_unique<NumberNode>(currentToken);
        currentToken = lexer.getNextToken();
        return node;
    }

public:
    explicit Parser(Lexer lexer) : lexer(std::move(lexer)), currentToken(this->lexer.getNextToken()) {}

    std::unique_ptr<ASTNode> parse()
    {
        return parseNumber();
    }
};