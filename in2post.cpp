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
    string token;

    while (tokens >> token){
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
    Stack<double> operands;
    istringstream tokens(postfix);
    string token;

    while (tokens >> token){
        
    }
}

int main() {
    string expression;
    getline(cin, expression);
    cout<<"String is: "<<expression<<endl;
    
    return 0;
}