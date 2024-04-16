#ifndef TLIST_HPP
#define TLIST_HPP

#include <iostream>

// TList class implementation ----------------------------------------------------------------------------

template <typename T>
TList<T>::TList()
{
    first = 0;
    last = 0;
    size = 0;
}

template <typename T>
TList<T>::TList(T val, int num)
{
    first = 0;
    last = 0;
    size = 0;

    for (int i = 0; i < num; ++i)
    {
        InsertBack(val);
    }
}

template <typename T>
TList<T>::~TList()
{
    Clear();
}

template <typename T>
TList<T>::TList(const TList& L)
{
    first = 0;
    last = 0;
    size = 0;

    Node<T>* current = L.first;
    while (current != 0)
    {
        InsertBack(current->data);
        current = current->next;
    }
}

template <typename T>
TList<T>& TList<T>::operator=(const TList& L)
{
    if (this != &L)
    {
        Clear();

        Node<T>* current = L.first;
        while (current != 0)
        {
            InsertBack(current->data);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
TList<T>::TList(TList&& L)
{
    first = L.first;
    last = L.last;
    size = L.size;

    L.first = 0;
    L.last = 0;
    L.size = 0;
}

template <typename T>
TList<T>& TList<T>::operator=(TList&& L)
{
    if (this != &L)
    {
        Clear();

        first = L.first;
        last = L.last;
        size = L.size;

        L.first = 0;
        L.last = 0;
        L.size = 0;
    }
    return *this;
}

template <typename T>
bool TList<T>::IsEmpty() const
{
    if ( size==0){
        return 1;
    }
    else{
        return 0;
    }
}

template <typename T>
void TList<T>::Clear()
{
    Node<T>* current = first;
    while (current != 0)
    {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }

    first = 0;
    last = 0;
    size = 0;
}

template <typename T>
int TList<T>::GetSize() const
{
    return size;
}

template <typename T>
void TList<T>::InsertFront(const T& d)
{
    Node<T>* newNode = new Node<T>(d);

    if (IsEmpty())
    {
        first = newNode;
        last = newNode;
    }
    else
    {
        newNode->next = first;
        first->prev = newNode;
        first = newNode;
    }

    size++;
}

template <typename T>
void TList<T>::InsertBack(const T& d)
{
    Node<T>* newNode = new Node<T>(d);

    if (IsEmpty())
    {
        first = newNode;
        last = newNode;
    }
    else
    {
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
    }

    size++;
}

template <typename T>
void TList<T>::RemoveFront()
{
    if (!IsEmpty())
    {
        Node<T>* temp = first;
        first = first->next;

        if (first != 0)
        {
            first->prev = 0;
        }
        else
        {
            last = 0;
        }

        delete temp;
        size--;
    }
}

template <typename T>
void TList<T>::RemoveBack()
{
    if (!IsEmpty())
    {
        Node<T>* temp = last;
        last = last->prev;

        if (last != 0)
        {
            last->next = 0;
        }
        else
        {
            first = 0;
        }

        delete temp;
        size--;
    }
}

template <typename T>
T& TList<T>::GetFirst() const
{
    if (IsEmpty())
    {
        return dummy;
    }
    return first->data;
}

template <typename T>
T& TList<T>::GetLast() const
{
    if (IsEmpty())
    {
        return dummy;
    }
    return last->data;
}

template <typename T>
TListIterator<T> TList<T>::GetIterator() const
{
    TListIterator<T> iter;
    iter.ptr = first;
    return iter;
}

template <typename T>
TListIterator<T> TList<T>::GetIteratorEnd() const
{
    TListIterator<T> iter;
    iter.ptr = last;
    return iter;
}

template <typename T>
void TList<T>::Insert(TListIterator<T> pos, const T& d)
{
    if (pos.ptr == 0)
    {
        InsertBack(d);
        return;
    }

    Node<T>* newNode = new Node<T>(d);

    Node<T>* current = pos.ptr;
    Node<T>* previous = current->prev;

    if (previous != 0)
    {
        previous->next = newNode;
    }
    else
    {
        first = newNode;
    }

    newNode->prev = previous;
    newNode->next = current;
    current->prev = newNode;

    size++;
}

template <typename T>
TListIterator<T> TList<T>::Remove(TListIterator<T> pos)
{
    Node<T>* current = pos.ptr;
    Node<T>* previous = current->prev;
    Node<T>* next = current->next;

    if (previous != 0)
    {
        previous->next = next;
    }
    else
    {
        first = next;
    }

    if (next != 0)
    {
        next->prev = previous;
    }
    else
    {
        last = previous;
    }

    TListIterator<T> nextIter;
    nextIter.ptr = next;
    delete current;
    size--;

    return nextIter;
}

template <typename T>
void TList<T>::Print(std::ostream& os, char delim) const
{
    Node<T>* current = first;
    while (current != 0)
    {
        os << current->data;
        current = current->next;
        if (current != 0)
        {
            os << delim;
        }
    }
}

template <typename T>
TList<T> operator+(const TList<T>& t1, const TList<T>& t2)
{
    TList<T> result;

    // Copy elements from t1 to result
    TListIterator<T> it1 = t1.GetIterator();
    while (it1.HasNext())
    {
        result.InsertBack(it1.GetData());
        it1.Next();
    }

    // Copy elements from t2 to result
    TListIterator<T> it2 = t2.GetIterator();
    while (it2.HasNext())
    {
        result.InsertBack(it2.GetData());
        it2.Next();
    }

    return result;
}


// TListIterator class implementation ------------------------------------------------------------------------------

template <typename T>
TListIterator<T>::TListIterator() : ptr(0)
{
}

template <typename T>
bool TListIterator<T>::HasNext() const
{
    if(ptr != 0){
        return 1;
    }
    else{
        return 0;
    }
}

template <typename T>
bool TListIterator<T>::HasPrevious() const
{
    if(ptr != 0){
        return 1;
    }
    else{
        return 0;
    }}

template <typename T>
TListIterator<T> TListIterator<T>::Next()
{
    if (ptr != 0)
    {
        ptr = ptr->next;
    }
    return *this;
}

template <typename T>
TListIterator<T> TListIterator<T>::Previous()
{
    if (ptr != 0)
    {
        ptr = ptr->prev;
    }
    return *this;
}

template <typename T>
T& TListIterator<T>::GetData() const
{
    if (ptr != 0)
    {
        return ptr->data;
    }
    return TList<T>::dummy;
}



#endif  // TLIST_HPP