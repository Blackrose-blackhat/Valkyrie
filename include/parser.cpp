#include "token.h"
class AST {
public:
    virtual ~AST() = default;
};

class BinOp : public AST {
public:
    Token token;
    std::unique_ptr<AST> left;
    std::unique_ptr<AST> right;

    BinOp(Token token, std::unique_ptr<AST> left, std::unique_ptr<AST> right)
        : token(std::move(token)), left(std::move(left)), right(std::move(right)) {}
};

class Num : public AST {
public:
    Token token;

    explicit Num(Token token) : token(std::move(token)) {}
};

class Parser {
public:
    explicit Parser(Lexer lexer) : lexer(std::move(lexer)), currentToken(this->lexer.getNextToken()) {}

    std::unique_ptr<AST> parse() {
        return expr();
    }

private:
    Lexer lexer;
    Token currentToken;

    void eat(TokenType tokenType) {
        if (currentToken.type == tokenType) {
            currentToken = lexer.getNextToken();
        } else {
            throw std::runtime_error("Token type mismatch");
        }
    }

    std::unique_ptr<AST> expr() {
        auto node = term();

        while (currentToken.type == TokenType::PLUS || currentToken.type == TokenType::MINUS) {
            Token token = currentToken;
            if (token.type == TokenType::PLUS) {
                eat(TokenType::PLUS);
            } else if (token.type == TokenType::MINUS) {
                eat(TokenType::MINUS);
            }

            node = std::make_unique<BinOp>(std::move(token), std::move(node), term());
        }

        return node;
    }

    std::unique_ptr<AST> term() {
        auto node = factor();

        while (currentToken.type == TokenType::MULTIPLY || currentToken.type == TokenType::DIVIDE) {
            Token token = currentToken;
            if (token.type == TokenType::MULTIPLY) {
                eat(TokenType::MULTIPLY);
            } else if (token.type == TokenType::DIVIDE) {
                eat(TokenType::DIVIDE);
            }

            node = std::make_unique<BinOp>(std::move(token), std::move(node), factor());
        }

        return node;
    }

    std::unique_ptr<AST> factor() {
        Token token = currentToken;
        if (token.type == TokenType::INTEGER) {
            eat(TokenType::INTEGER);
            return std::make_unique<Num>(std::move(token));
        } else if (token.type == TokenType::LPAREN) {
            eat(TokenType::LPAREN);
            auto node = expr();
            eat(TokenType::RPAREN);
            return node;
        }

        throw std::runtime_error("Invalid syntax");
    }
};