#include <iostream>
#include "include/lexer.cpp"
#include "include/parser.cpp"


int main() {
    std::string input;
    std::cout << "Enter input: ";
    std::getline(std::cin, input);
    
    Lexer lexer(input);
    Parser parser(lexer);
    
    try {
        auto ast = parser.parse();
        std::cout << "Parsing successful!" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Parsing failed: " << e.what() << std::endl;
    }
    
    return 0;
}