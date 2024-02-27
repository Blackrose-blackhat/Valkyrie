#pragma once


#include <iostream>
#include <string>
#include <vector>

enum class TokenType
{
    INTEGER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    END,
    IDENTIFIER 
};

struct Token
{
    TokenType type;
    std::string value;
};

class Lexer
{
public:
    Lexer(std::string input) : input(input), currentPos(0) {}

    Token getNextToken()
    {
        while (currentPos < input.size() && std::isspace(input[currentPos]))
        {
            ++currentPos; // Skip whitespace
        }

        if (currentPos == input.size())
        {
            return Token{TokenType::END, ""};
        }

        char currentChar = input[currentPos];

        if (std::isdigit(currentChar))
        {
            std::string value;
            while (currentPos < input.size() && std::isdigit(input[currentPos]))
            {
                value += input[currentPos];
                currentPos++;
            }
            return Token{TokenType::INTEGER, value};
        }

        if (std::isalpha(currentChar))
        {
            std::string value;
            while (currentPos < input.size() && std::isalpha(input[currentPos]))
            {
                value += input[currentPos];
                currentPos++;
            }
            return Token{TokenType::IDENTIFIER, value}; // Changed from INTEGER to IDENTIFIER
        }

        switch (currentChar)
        {
        case '+':
            currentPos++;
            return Token{TokenType::PLUS, "+"};
        case '-':
            currentPos++;
            return Token{TokenType::MINUS, "-"};
        case '*':
            currentPos++;
            return Token{TokenType::MULTIPLY, "*"};
        case '/':
            currentPos++;
            return Token{TokenType::DIVIDE, "/"};
        case '(':
            currentPos++;
            return Token{TokenType::LPAREN, "("};
        case ')':
            currentPos++;
            return Token{TokenType::RPAREN, ")"};

        case ' ':
            currentPos++;
            return Token{TokenType::END, ""};
        default:
            throw std::runtime_error("Invalid character: " + std::string(1, currentChar));
        }
    }

private:
    std::string input;
    size_t currentPos;
};

int main()
{
    std::string input;
    std::cin >> input;
    Lexer lexer(input);

    std::vector<Token> tokens;
    Token token = lexer.getNextToken();
    while (token.type != TokenType::END)
    {
        tokens.push_back(token);
        token = lexer.getNextToken();
    }

    for (const auto &token : tokens)
    {
        std::cout << "Token Type: " << static_cast<int>(token.type) << ", Value: " << token.value << std::endl;
    }

    return 0;
}

