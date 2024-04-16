#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "stack.h" // Include the custom Stack class

// Helper function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Helper function to get the precedence of an operator
int getPrecedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    return 0;
}

// Helper function to convert infix expression to postfix expression
std::string infixToPostfix(const std::string& infix) {
    std::stringstream postfix;
    cop4530::Stack<char> operatorStack; // Use the custom Stack class

    for (char c : infix) {
        if (std::isspace(c))
            continue;

        if (std::isalnum(c)) {
            postfix << c;
        } else if (c == '(') {
            operatorStack.push(c);
        } else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix << operatorStack.top();
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == '(') {
                operatorStack.pop();
            } else {
                // Mismatched parentheses
                return "";
            }
        } else if (isOperator(c)) {
            while (!operatorStack.empty() && operatorStack.top() != '(' &&
                   getPrecedence(c) <= getPrecedence(operatorStack.top())) {
                postfix << operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);
        } else {
            // Invalid character
            return "";
        }
    }

    while (!operatorStack.empty()) {
        if (operatorStack.top() == '(') {
            // Mismatched parentheses
            return "";
        }
        postfix << operatorStack.top();
        operatorStack.pop();
    }

    return postfix.str();
}

// Helper function to evaluate a postfix expression
double evaluatePostfix(const std::string& postfix) {
    cop4530::Stack<double> operandStack; // Use the custom Stack class

    for (char c : postfix) {
        if (std::isdigit(c)) {
            operandStack.push(c - '0');
        } else if (isOperator(c)) {
            if (operandStack.size() < 2) {
                // Insufficient operands
                return 0.0;
            }
            double operand2 = operandStack.top();
            operandStack.pop();
            double operand1 = operandStack.top();
            operandStack.pop();
            double result;
            switch (c) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        // Division by zero
                        return 0.0;
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    // Invalid operator
                    return 0.0;
            }
            operandStack.push(result);
        } else {
            // Invalid character
            return 0.0;
        }
    }

    if (operandStack.size() != 1) {
        // Invalid expression
        return 0.0;
    }

    return operandStack.top();
}

int main() {
    // Create a stack of integers
    cop4530::Stack<int> stack;

    // Push some elements onto the stack
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // Print the stack
    std::cout << "Stack: " << stack << std::endl;

    // Check if the stack is empty
    std::cout << "Is the stack empty? " << (stack.empty() ? "Yes" : "No") << std::endl;

    // Get the size of the stack
    std::cout << "Size of the stack: " << stack.size() << std::endl;

    // Access and modify the top element
    int& topElement = stack.top();
    topElement *= 2;

    // Print the modified top element
    std::cout << "Modified top element: " << topElement << std::endl;

    // Pop an element from the stack
    stack.pop();

    // Print the stack after popping an element
    std::cout << "Stack after popping an element: " << stack << std::endl;

    // Clear the stack
    stack.clear();

    // Print the stack after clearing
    std::cout << "Stack after clearing: " << stack << std::endl;

    // Check if the stack is empty again
    std::cout << "Is the stack empty now? " << (stack.empty() ? "Yes" : "No") << std::endl;

    // Test infix to postfix conversion and evaluation
    std::string infixExpression = "(3 + 4) * 2 + 10 * (c / 5)";
    std::cout << "Infix expression: " << infixExpression << std::endl;

    std::string postfixExpression = infixToPostfix(infixExpression);
    if (!postfixExpression.empty()) {
        std::cout << "Postfix expression: " << postfixExpression << std::endl;
        evaluatePostfix(postfixExpression);
    }

    // Prompt the user to enter an expression
    std::string expression;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, expression);

    std::string infixNotation = expression;
    std::string postfixNotation = infixToPostfix(expression);

    std::cout << "The Infix Notation is: " << infixNotation << std::endl;
    std::cout << "The Postfix Notation is: " << postfixNotation << std::endl;

    double result = evaluatePostfix(postfixNotation);

    if (result == 0.0) {
        std::cout << "Error - Invalid expression or division by zero" << std::endl;
    } else {
        std::cout << "Result: " << result << std::endl;
    }

    return 0;
}