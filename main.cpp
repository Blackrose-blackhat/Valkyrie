#include <iostream>
#include "./lexer.cpp"
#include "./parser.h"
#include "compiler.cpp"
using namespace std;
int main()
{
    std::string input;
    std::cout << "Enter input: ";
    std::getline(std::cin, input);

    Lexer lexer(input);
    Parser parser(lexer);
    Compiler compiler;
    try
    {
        auto ast = parser.parse();
        std::string js = compiler.compile(*ast);
        std::cout << "Generated JavaScript: " << js << std::endl;
        
    }
    catch (const std::exception &e)
    {
        std::cout<<"Compilation failed!"<<std::endl;
        std::cerr << e.what() << '\n';
    }

    return 0;
}