#ifndef LIST_HPP
#define LIST_HPP

#include "List.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// NESTED CONST ITERATOR CLASS ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Default zero-parameter constructor
template <typename T>
List<T>::const_iterator::const_iterator() : current(nullptr) {}

// Return a reference to the corresponding element in the list by calling retrieve()
template <typename T>
const T& List<T>::const_iterator::operator*() const {
    return retrieve();
}

// Prefix increment operator
template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++() {
    current = current->next;
    return *this;
}

// Postfix increment operator
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
    const_iterator old = *this;
    ++(*this);
    return old;
}

// Prefix decrement operator
template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--() {
    current = current->prev;
    return *this;
}

// Postfix decrement operator
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
    const_iterator old = *this;
    --(*this);
    return old;
}

// Two iterators are equal if they refer to the same element
template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator& rhs) const {
    return current == rhs.current;
}

// Two iterators are equal if they do not refer to the same element
template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator& rhs) const {
    return !(*this == rhs);
}

// Return a reference to the corresponding element in the list
template <typename T>
T& List<T>::const_iterator::retrieve() const {
    return current->data;
}

// One-parameter constructor
template <typename T>
List<T>::const_iterator::const_iterator(Node* p) : current(p) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// END OF NESTED CONST ITERATOR CLASS //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////// NESTED ITERATOR CLASS ///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Default zero-parameter constructor
template <typename T>
List<T>::iterator::iterator() {}

// Return a reference to the corresponding element in the list by calling retrieve()
template <typename T>
T& List<T>::iterator::operator*() {
    return this->retrieve();
}

// Return a const reference to the corresponding element in the list by calling retrieve()
template <typename T>
const T& List<T>::iterator::operator*() const {
    return const_iterator::operator*();
}

// Prefix increment operator
template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++() {
    this->current = this->current->next;
    return *this;
}

// Postfix increment operator
template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
    iterator old = *this;
    ++(*this);
    return old;
}

// Prefix decrement operator
template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--() {
    this->current = this->current->prev;
    return *this;
}

// Postfix decrement operator
template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
    iterator old = *this;
    --(*this);
    return old;
}

// One-parameter constructor
template <typename T>
List<T>::iterator::iterator(Node* p) : const_iterator(p) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////// END OF NESTED ITERATOR CLASS ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////// LIST CLASS ////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Default zero-parameter constructor
template <typename T>
List<T>::List() {
    init();
}

// Copy constructor
template <typename T>
List<T>::List(const List& rhs) {
    init();
    *this = rhs;
}

// Move constructor
template <typename T>
List<T>::List(List&& rhs) {
    init();
    *this = std::move(rhs);
}

// Constructor with number of elements and value
template <typename T>
List<T>::List(int num, const T& val) {
    init();
    for (int i = 0; i < num; ++i)
        push_back(val);
}

// Constructor with iterators
template <typename T>
List<T>::List(const_iterator start, const_iterator end) {
    init();
    for (auto itr = start; itr != end; ++itr)
        push_back(*itr);
}

// Constructor with initializer list
template <typename T>
List<T>::List(std::initializer_list<T> iList) {
    init();
    for (const auto& val : iList)
        push_back(val);
}

// Destructor
template <typename T>
List<T>::~List() {
    clear();
    delete tail;
}

// Copy assignment operator
template <typename T>
const List<T>& List<T>::operator=(const List& rhs) {
    if (this != &rhs) {
        clear();
        for (auto itr = rhs.begin(); itr != rhs.end(); ++itr)
            push_back(*itr);
    }
    return *this;
}

// Move assignment operator
template <typename T>
List<T>& List<T>::operator=(List&& rhs) {
    if (this != &rhs) {
        clear();
        theSize = rhs.theSize;
        head = rhs.head;
        tail = rhs.tail;
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    return *this;
}

// Assignment operator with initializer list
template <typename T>
List<T>& List<T>::operator=(std::initializer_list<T> iList) {
    clear();
    for (const auto& val : iList)
        push_back(val);
    return *this;
}

// Return the number of elements in the list
template <typename T>
int List<T>::size() const {
    return theSize;
}

// Check if the list is empty
template <typename T>
bool List<T>::empty() const {
    return theSize == 0;
}

// Delete all elements in the list
template <typename T>
void List<T>::clear() {
    while (!empty())
        pop_front();
}

template <typename T>
void List<T>::reverse() {
    if (size() < 2)
        return;

    Node* current = head->next;
    Node* temp = nullptr;

    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    temp = head;
    head = tail;
    tail = temp;
}

// Return reference to the first element
template <typename T>
T& List<T>::front() {
    return *begin();
}

// Return constant reference to the first element
template <typename T>
const T& List<T>::front() const {
    return *begin();
}

// Return reference to the last element
template <typename T>
T& List<T>::back() {
    return *--end();
}

// Return constant reference to the last element
template <typename T>
const T& List<T>::back() const {
    return *--end();
}

// Insert value at the beginning of the list
template <typename T>
void List<T>::push_front(const T& val) {
    insert(begin(), val);
}

// Move version of inserting value at the beginning of the list
template <typename T>
void List<T>::push_front(T&& val) {
    insert(begin(), std::move(val));
}

// Insert value at the end of the list
template <typename T>
void List<T>::push_back(const T& val) {
    insert(end(), val);
}

// Move version of inserting value at the end of the list
template <typename T>
void List<T>::push_back(T&& val) {
    insert(end(), std::move(val));
}

// Remove the first element in the list
template <typename T>
void List<T>::pop_front() {
    erase(begin());
}

// Remove the last element in the list
template <typename T>
void List<T>::pop_back() {
    erase(--end());
}

// Remove all nodes with value equal to val
template <typename T>
void List<T>::remove(const T& val) {
    auto itr = begin();
    while (itr != end()) {
        if (*itr == val)
            itr = erase(itr);
        else
            ++itr;
    }
}

// Remove nodes for which pred returns true
template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred) {
    auto itr = begin();
    while (itr != end()) {
        if (pred(*itr))
            itr = erase(itr);
        else
            ++itr;
    }
}

// Print all elements in the list
template <typename T>
void List<T>::print(std::ostream& os, char ofc) const {
    for (auto itr = begin(); itr != end(); ++itr) {
        os << *itr;
        if (itr != --end())
            os << ofc;
    }
}

// Return iterator to the first element
template <typename T>
typename List<T>::iterator List<T>::begin() {
    return iterator(head->next);
}

// Return constant iterator to the first element
template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
    return const_iterator(head->next);
}

// Return iterator to the end marker of the list
template <typename T>
typename List<T>::iterator List<T>::end() {
    return iterator(tail);
}

// Return constant iterator to the end marker of the list
template <typename T>
typename List<T>::const_iterator List<T>::end() const {
    return const_iterator(tail);
}

// Insert value ahead of the node referred to by itr
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val) {
    Node* p = itr.current;
    theSize++;
    return { p->prev = p->prev->next = new Node{ val, p->prev, p } };
}

// Move version of inserting value ahead of the node referred to by itr
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T&& val) {
    Node* p = itr.current;
    theSize++;
    return { p->prev = p->prev->next = new Node{ std::move(val), p->prev, p } };
}

// Delete node referred to by itr and return iterator to the following node
template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr) {
    Node* p = itr.current;
    iterator retVal{ p->next };
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;
    return retVal;
}

// Delete nodes between start and end (excluding end)
template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end) {
    for (auto itr = start; itr != end;)
        itr = erase(itr);
    return end;
}

// Initialize the member variables of the list
template <typename T>
void List<T>::init() {
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////// END OF LIST CLASS ////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////// Non-class functions /////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Overload the equality operator
template <typename T>
bool operator==(const List<T>& lhs, const List<T>& rhs) {
    if (lhs.size() != rhs.size())
        return false;

    auto lhsItr = lhs.begin();
    auto rhsItr = rhs.begin();

    while (lhsItr != lhs.end()) {
        if (*lhsItr != *rhsItr)
            return false;
        ++lhsItr;
        ++rhsItr;
    }

    return true;
}

// Overload the inequality operator
template <typename T>
bool operator!=(const List<T>& lhs, const List<T>& rhs) {
    return !(lhs == rhs);
}

// Overload the output stream operator
template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& l) {
    l.print(os);
    return os;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////// END OF Non-class functions /////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // LIST_HPP