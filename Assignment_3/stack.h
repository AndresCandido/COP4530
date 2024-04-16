#ifndef STACK_H
#define STACK_H

#include <list>
#include <iostream>

namespace cop4530 {

template <typename T>
class Stack {
public:
    Stack();                        // Zero-argument constructor
    ~Stack();                       // Destructor
    Stack(const Stack&);            // Copy constructor
    Stack(Stack&&);                 // Move constructor
    Stack& operator=(const Stack&); // Copy assignment operator
    Stack& operator=(Stack&&);      // Move assignment operator
    
    bool empty() const;             // Check if the stack is empty
    void clear();                   // Clear all elements from the stack
    void push(const T& x);          // Push an element onto the stack (copy version)
    void push(T&& x);               // Push an element onto the stack (move version)
    void pop();                     // Pop the top element from the stack
    T& top();                       // Get a reference to the top element (modifiable)
    const T& top() const;           // Get a const reference to the top element
    int size() const;               // Get the size of the stack
    void print(std::ostream& os, char ofc = ' ') const; // Print the elements of the stack

private:
    std::list<T> data;              // internal container to store elements
};

// Non-member functions

// Output the stack to the provided ostream
template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a);

// Compare two stacks for equality
template <typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b);

// Compare two stacks for inequality
template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b);

// Compare two stacks based on their elements' order
template <typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b);

#include "stack.hpp" // Include the implementation file

} // namespace cop4530

#endif // STACK_H