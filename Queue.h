#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

template <typename T>
class Queue : public LinkedList<T> {
    public:
    Queue() { }
    void push(T val);
    T pop();
    inline bool empty() { return LinkedList<T>::empty(); }
};

template <typename T>
void Queue<T>::push(T val)
{
    LinkedList<T>::push_front(val);
}

template <typename T>
T Queue<T>::pop()
{
    return LinkedList<T>::pop_back();
}

template <typename T>
class Dequeue : public LinkedList<T> {
   public:
   Dequeue() { }
   void push_front(T val);
   void push_back(T val);
   T pop_front();
   T pop_back();
   inline bool empty() { return LinkedList<T>::empty(); }
};

template <typename T>
void Dequeue<T>::push_back(T val)
{
    LinkedList<T>::push_back(val);
}

template <typename T>
void Dequeue<T>::push_front(T val)
{
    LinkedList<T>::push_front(val);
}

template <typename T>
T Dequeue<T>::pop_back()
{
    return LinkedList<T>::pop_back();
}

template <typename T>
T Dequeue<T>::pop_front()
{
    return LinkedList<T>::pop_front();
}

#endif