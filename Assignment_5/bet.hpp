#ifndef BET_HPP
#define BET_HPP

#include "bet.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>

// Public member functions implementation

// Default constructor
template <typename T>
BET<T>::BET() : root(nullptr) {}

// One-parameter constructor
template <typename T>
BET<T>::BET(const std::string& postfix) : root(nullptr) {
    buildFromPostfix(postfix);
}

// Copy constructor
template <typename T>
BET<T>::BET(const BET& other) : root(clone(other.root)) {}

// Destructor
template <typename T>
BET<T>::~BET() {
    makeEmpty(root);
}

// Assignment operator
template <typename T>
const BET<T>& BET<T>::operator=(const BET& other) {
    if (this != &other) {
        makeEmpty(root);
        root = clone(other.root);
    }
    return *this;
}

// Check if the tree is empty
template <typename T>
bool BET<T>::empty() const {
    return root == nullptr;
}

// Private member functions implementation

// Helper function to recursively delete all nodes
template <typename T>
void BET<T>::makeEmpty(BinaryNode*& t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

// Helper function to recursively clone the tree
template <typename T>
typename BET<T>::BinaryNode* BET<T>::clone(BinaryNode* t) const {
    if (t == nullptr) return nullptr;
    return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

// Helper function to build the binary expression tree from the postfix expression
template <typename T>
bool BET<T>::buildFromPostfix(const std::string& postfix) {
    std::stack<BinaryNode*> nodeStack;
    std::istringstream iss(postfix);
    std::string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (nodeStack.size() < 2) {
                makeEmpty(root);
                std::cerr << "Invalid postfix expression: insufficient operands\n";
                return false;
            }
            BinaryNode* operand2 = nodeStack.top();
            nodeStack.pop();
            BinaryNode* operand1 = nodeStack.top();
            nodeStack.pop();

            BinaryNode* newNode = new BinaryNode(token);
            newNode->left = operand1;
            newNode->right = operand2;
            nodeStack.push(newNode);
        } else {
            nodeStack.push(new BinaryNode(token));
        }
    }

    if (nodeStack.size() != 1) {
        makeEmpty(root);
        std::cerr << "Invalid postfix expression: too many operands\n";
        return false;
    }

    root = nodeStack.top();
    nodeStack.pop();
    return true;
}


// Helper function to print the infix expression
template <typename T>
void BET<T>::printInfixExpression(BinaryNode* n) const {
    if (n != nullptr) {
        bool needParentheses = false;

        if (n->left != nullptr && (n->element == "*" || n->element == "/")) {
            needParentheses = true;
        }

        if (n->left != nullptr) {
            if (needParentheses) std::cout << "(";
            printInfixExpression(n->left);
            if (needParentheses) std::cout << ")";
        }

        std::cout << n->element << " ";

        needParentheses = false;

        if (n->right != nullptr && (n->element == "*" || n->element == "/" || n->element == "+" || n->element == "-")) {
            needParentheses = true;
        }

        if (n->right != nullptr) {
            if (needParentheses) std::cout << "(";
            printInfixExpression(n->right);
            if (needParentheses) std::cout << ")";
        }
    }
}

// Helper function to print the postfix expression
template <typename T>
void BET<T>::printPostfixExpression(BinaryNode* n) const {
    if (n != nullptr) {
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        std::cout << n->element << " ";
    }
}

// Helper function to calculate the size of the tree
template <typename T>
size_t BET<T>::size(BinaryNode* t) const {
    if (t == nullptr) return 0;
    return 1 + size(t->left) + size(t->right);
}

// Helper function to calculate the number of leaf nodes in the tree
template <typename T>
size_t BET<T>::leaf_nodes(BinaryNode* t) const {
    if (t == nullptr) return 0;
    if (t->left == nullptr && t->right == nullptr) return 1;
    return leaf_nodes(t->left) + leaf_nodes(t->right);
}

// Public member functions implementation

// Print the infix expression
template <typename T>
void BET<T>::printInfixExpression() const {
    printInfixExpression(root);
    std::cout << std::endl;
}

// Print the postfix expression
template <typename T>
void BET<T>::printPostfixExpression() const {
    printPostfixExpression(root);
    std::cout << std::endl;
}

// Get the size of the tree
template <typename T>
size_t BET<T>::size() const {
    return size(root);
}

// Get the number of leaf nodes in the tree
template <typename T>
size_t BET<T>::leaf_nodes() const {
    return leaf_nodes(root);
}

#endif