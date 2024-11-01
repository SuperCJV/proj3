#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <cctype>

#include "stack.h"

using namespace std;
using namespace cop4530;

// Check if a string is an operator
bool isOperator(const string& op){
    return op == "+" || op == "-" || op == "*" || op == "/";
}

// Returns the precedence level of an operator
int precedence(const string& op){
    if(op == "+" || op == "-"){
        return 1;
    }else if(op == "*" || op == "/"){
        return 2;   // Higher int means higher precedence
    }else{
        return 0;   // Return 0 otherwise
    }
}

// Infix to postfix conversion
string infixToPostfix(const string& infix){
    Stack<string> operators;
    stringstream postfix_result;    // Included in <sstream> that allows input/output operations on strings
    istringstream tokens(infix);    // Included in <sstream> that allows strings to be read token by token
    string token;   // Will pull single string from string line

    while (tokens >> token){    // Reads the infix notation token by token until the end is reached
        if(isdigit(token[0]) || isalpha(token[0])) {    // Checks if token is an a letter or a number
            postfix_result << token << " "; // Operands are outputted into the result
        } else if(token == "("){  // RULE #1
            operators.push(token);  // if "(", push it into the operator stack
        } else if(token == ")"){
            while(!operators.empty() && operators.top() != "("){ // RULE #3
                postfix_result << operators.top() << " "; // Top of stack is outputted into the result
                operators.pop(); // Pop stack until "(" at the top
            }
            if(operators.empty()) {
                cerr << "Error: Mismatched parentheses. \n"; // If stack is empty without "(" then report error
                return "";
            }
            operators.pop(); // Pop stack discarding parenthesis
        } else if(isOperator(token)) { // RULE #2
            while(!operators.empty() && precedence(operators.top()) >= precedence(token) && operators.top() != "("){
                postfix_result << operators.top() << " ";   // Top of stack is outputted into the result
                operators.pop();    // Pop stack until the following conditions are met:
                                        // i. Stack is empty
                                        // ii. "(" at the top
                                        // iii. Lower precedence operator is at the top
            }
            operators.push(token);  // Push operator into operator stack
        } else {
            cerr << "Error: Invalid token \"" << token << "\" .\n";
            return "";
        }
    }

    while(!operators.empty()){  // RULE #4
        if(operators.top() == "("){
            cerr<<"Error: Mismatched parentheses.\n";   // IF last input processed was "(", report error
            return "";
        }
        postfix_result << operators.top() << " "; // Otherwise, output the top of the stack
        operators.pop();    // Pop operator stack until its empty
    }

    return postfix_result.str();    // Return the postfix notation
}

// Postfix expression evaluation
double evaluatePostfix(const string& postfix){
    Stack<double> operands; // Will deal with floats and ints
    istringstream tokens(postfix);  // Included in <sstream> that allows strings to be read token by token
    string token;   // Will pull single string from string line

    while (tokens >> token){    // Reads the infix notation token by token until the end is reached
        if(isdigit(token[0])){
            operands.push(stod(token)); // Push numeric values into operand stack
        } else if(isOperator(token)){
            if(operands.size() < 2){    // If operator has fewer than 2 elements, report error
                cerr << "Error: Insufficient operands.\n";
                return 0;
            }
            
            // When operator is read from input, remove two values from the operands stack
            double right = operands.top(); 
            operands.pop();
            double left = operands.top();
            operands.pop();

            // Apply the operators to them and push the result into the operands stack
            if(token == "+"){
                operands.push(left + right);
            }else if(token == "-"){
                operands.push(left - right);
            }else if(token == "*"){
                operands.push(left * right);
            }else if(token == "/"){
                if(right == 0){
                    cerr << "Error: Division by zero.\n";   // Check for division by 0
                    return 0;
                }
                operands.push(left / right);
            }
        } else {
            cerr << "Warning: Non-numeric operand \"" << token << "\" found.\n"; // If stack has more than one opearnd, report error
            return 0;
        }
    }
    // If operand stack is empty, return 0
    // Else, return the top value (the result)
    return operands.empty() ? 0 : operands.top();
}

int main() {
    string infix_input;
    cout<< "Enter infix expression or 'exit' to quit: \n";
    while(getline(cin, infix_input)){
        if(infix_input == "exit"){  // Quit program if the input = "exit"
            break;
        }

        string postfix = infixToPostfix(infix_input);
        if(!postfix.empty()){
            cout<< "Postfix" << postfix << "\n";

            // "The program should only evaluate the computed postfix expressions that contain only numeric operands"
            if (postfix.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos) {
                // If no alphabetic characters are found, evaluate and print result
                double result = evaluatePostfix(postfix);
                cout << "Result: " << result << "\n";
            } else {
                // If postfix contains any alphabetic characters, it will print as-is
                cout << "Result: " << postfix << "\n";
            }

        }

        cout<< "Enter infix expression or 'exit' to quit: \n";  // Re-prompt the user
    }
    
    return 0;
}