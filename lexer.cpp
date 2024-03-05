#pragma once

#include <iostream>
#include <string>
#include <vector>

// defining the different types of tokens that our lexer will tokenize
enum class TokenType
{
    // this is like we are defining our data types of this language
    INTEGER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    END,
    IDENTIFIER,
    PRINT
};

// making a structure token to accept different types of data
struct Token
{
    // inititalizes type to only be of type => TokenType as above
    TokenType type;
    std::string value;
};

// created a class Lexer
class Lexer
{
public:
    // constructor to initialze and takes a single string input
    // it then copies the input string to the input data member of the Lexer class
    Lexer(std::string input) : input(input), currentPos(0) {}

    Token getNextToken()
    {
        if (currentPos + 5 <= input.length() && input.substr(currentPos, 5) == "print")
        {
            currentPos += 5; // Move the current position past the "print" keyword
            return Token{TokenType::PRINT, "print"};
        }

        // for now we are ignoring the whitespaces
        while (currentPos < input.size() && std::isspace(input[currentPos]))
        {
            ++currentPos; // Skip whitespace
        }
        // the end of input string
        if (currentPos == input.size())
        {
            return Token{TokenType::END, ""};
        }

        // copying the inputted file over currentChat getting from currentPos
        char currentChar = input[currentPos];

        // check if the currentChar is a digit
        if (std::isdigit(currentChar))
        {
            // if it is a digit then we will keep on adding the digits to the value string until we encounter any non-digit character or reach the end of the input string
            std::string value;
            while (currentPos < input.size() && std::isdigit(input[currentPos]))
            {
                value += input[currentPos];
                currentPos++;
            }
            return Token{TokenType::INTEGER, value};
        }
        // check if the currentChar is a letter
        if (std::isalpha(currentChar))
        {
            // if it is a letter then we will keep on adding the letters to the value string until we encounter any non-letter character or reach the end of the input string
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
    // contains the input string that lexer will tokenize
    std::string input;
    // keeps track of current position in the input string
    size_t currentPos;
};
