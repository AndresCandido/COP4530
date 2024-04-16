#ifndef BET_H
#define BET_H

#include <string>

template <typename T>
class BET {
private:
    struct BinaryNode {
        T element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const T& e, BinaryNode* l = nullptr, BinaryNode* r = nullptr)
            : element(e), left(l), right(r) {}
    };

    BinaryNode* root;

    void makeEmpty(BinaryNode*& t);
    BinaryNode* clone(BinaryNode* t) const;
    void printInfixExpression(BinaryNode* n) const;
    void printPostfixExpression(BinaryNode* n) const;
    size_t size(BinaryNode* t) const;
    size_t leaf_nodes(BinaryNode* t) const;

public:
    BET(); // default zero-parameter constructor
    BET(const std::string& postfix); // one-parameter constructor
    BET(const BET&); // copy constructor
    ~BET(); // destructor
    bool buildFromPostfix(const std::string& postfix);
    const BET& operator=(const BET&);
    void printInfixExpression() const;
    void printPostfixExpression() const;
    size_t size() const;
    size_t leaf_nodes() const;
    bool empty() const;
};

#include "bet.hpp"
#endif