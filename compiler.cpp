#include<string>
#include "./parser.cpp"
using namespace std;
class Compiler {
public:
    string compile(const ASTNode& node) {
        // For now, we only know how to compile NumberNodes
        if (const NumberNode* numberNode = dynamic_cast<const NumberNode*>(&node)) {
            return compileNumberNode(*numberNode);
        }
        else if (const BinaryOperatorNode* binaryOperatorNode = dynamic_cast<const BinaryOperatorNode*>(&node) )
        {
            return compilerBinaryOperatorNode(*binaryOperatorNode);
        }

        throw runtime_error("Unsupported node type");
    }

private:
    string compileNumberNode(const NumberNode& node) {
        // A NumberNode gets compiled to a JavaScript number
        return node.token.value;
    }

    string compilerBinaryOperatorNode(const BinaryOperatorNode& node) 
    {
        string left = compile(*node.left);
        string right = compile(*node.right);
        string op;

        switch (node.op.type)
        {
        case TokenType::PLUS:
            op = "+";
            break;
        case TokenType::MINUS:
            op = "-";
            break;
        case TokenType::MULTIPLY:
            op = "*";
            break;
        case TokenType::DIVIDE:
            op= "/";
            break;
        default:
            break;
        }
        return "(" + left + " " + op + " " + right + ")";
    }
};