#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>
#include <cctype>

#include "stack.h"

using namespace cop4530;

// Checks if a string is an operator
bool isOperator(const std::string& op) {
    return op == "+" || op == "-" || op == "*" || op == "/";
}

// Returns precedence level of an operator
int precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

// Converts infix expression to postfix expression
std::string infixToPostfix(const std::string& infix) {
    std::stack<std::string> operators;
    std::stringstream result;
    std::istringstream tokens(infix);
    std::string token;

    while (tokens >> token) {
        if (std::isdigit(token[0]) || std::isalpha(token[0])) {
            result << token << " ";
        }
        else if (token == "(") {
            operators.push(token);
        }
        else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                result << operators.top() << " ";
                operators.pop();
            }
            if (operators.empty()) {
                std::cerr << "Error: Mismatched parentheses.\n";
                return "";
            }
            operators.pop(); // Remove '(' from stack
        }
        else if (isOperator(token)) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(token) && operators.top() != "(") {
                result << operators.top() << " ";
                operators.pop();
            }
            operators.push(token);
        }
        else {
            std::cerr << "Error: Invalid token \"" << token << "\".\n";
            return "";
        }
    }
    // Pop remaining operators from the stack
    while (!operators.empty()) {
        if (operators.top() == "(") {
            std::cerr << "Error: Mismatched parentheses.\n";
            return "";
        }
        result << operators.top() << " ";
        operators.pop();
    }
    return result.str();
}

// Evaluates postfix expression if it contains only numeric operands
double evaluatePostfix(const std::string& postfix) {
    std::stack<double> operands;
    std::istringstream tokens(postfix);
    std::string token;

    while (tokens >> token) {
        if (std::isdigit(token[0])) {
            operands.push(std::stod(token));
        }
        else if (isOperator(token)) {
            if (operands.size() < 2) {
                std::cerr << "Error: Insufficient operands.\n";
                return 0;
            }
            double right = operands.top(); operands.pop();
            double left = operands.top(); operands.pop();

            if (token == "+") operands.push(left + right);
            else if (token == "-") operands.push(left - right);
            else if (token == "*") operands.push(left * right);
            else if (token == "/") {
                if (right == 0) {
                    std::cerr << "Error: Division by zero.\n";
                    return 0;
                }
                operands.push(left / right);
            }
        }
        else {
            std::cerr << "Warning: Non-numeric operand \"" << token << "\" found.\n";
            return 0;
        }
    }
    return operands.empty() ? 0 : operands.top();
}

int main() {
    std::string input;
    std::cout << "Enter infix expression (or 'exit' to quit): ";
    while (std::getline(std::cin, input)) {
        if (input == "exit") break;

        std::string postfix = infixToPostfix(input);
        if (!postfix.empty()) {
            std::cout << "Postfix: " << postfix << "\n";

            if (postfix.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos) {
                double result = evaluatePostfix(postfix);
                std::cout << "Result: " << result << "\n";
            } else {
                std::cout << "Result: " << postfix << "\n";
            }
        }
        std::cout << "\nEnter infix expression (or 'exit' to quit): ";
    }
    return 0;
}
