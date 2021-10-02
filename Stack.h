#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"

template <typename T>
class Stack : public LinkedList<T> {
    public:
    Stack() { }
    void push(T val);
    T pop();
    T top();
    inline bool empty() { return LinkedList<T>::empty(); }
};

template <typename T>
void Stack<T>::push(T val)
{
    LinkedList<T>::push_front(val);
}

template <typename T>
T Stack<T>::pop()
{
    return LinkedList<T>::pop_front();
}

template <typename T>
T Stack<T>::top()
{
    return LinkedList<T>::head->next;
}

#endif