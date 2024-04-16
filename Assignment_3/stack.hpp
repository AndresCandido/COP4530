#ifndef STACK_HPP
#define STACK_HPP

#include "stack.h"

template <typename T>
Stack<T>::Stack() {}

template <typename T>
Stack<T>::~Stack() {}

template <typename T>
Stack<T>::Stack(const Stack& rhs) : data(rhs.data) {}

template <typename T>
Stack<T>::Stack(Stack&& rhs) : data(std::move(rhs.data)) {}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) {
    if (this != &rhs) {
        data = rhs.data;
    }
    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& rhs) {
    if (this != &rhs) {
        data = std::move(rhs.data);
    }
    return *this;
}

template <typename T>
bool Stack<T>::empty() const {
    return data.empty();
}

template <typename T>
void Stack<T>::clear() {
    data.clear();
}

template <typename T>
void Stack<T>::push(const T& x) {
    data.push_back(x);
}

template <typename T>
void Stack<T>::push(T&& x) {
    data.push_back(std::move(x));
}

template <typename T>
void Stack<T>::pop() {
    if (!empty()) {
        data.pop_back();
    }
}

template <typename T>
T& Stack<T>::top() {
    return data.back();
}

template <typename T>
const T& Stack<T>::top() const {
    return data.back();
}

template <typename T>
int Stack<T>::size() const {
    return data.size();
}

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {
    for (const T& element : data) {
        os << element << ofc;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a) {
    a.print(os);
    return os;
}

template <typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b) {
    return a.data == b.data;
}

template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b) {
    return !(a == b);
}

template <typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b) {
    return a.data <= b.data;
}

#endif // STACK_HPP