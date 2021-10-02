#ifndef LINKEDLIST_H
#define LINKEDLIST_H

using namespace std;

template <typename T>
class LinkedList {
   private:
    int numNodes;
   public:
    struct node {
        T data;
        node *next;
        node *prev;
        node(T d) : data(d) { }
        node() { }
    };
    node *head;
    node *z;
    node *front;
    node *back;
    LinkedList()
    {
        head = new node;
        z = new node;
        z->next = z;
        head->next = z;
        head->prev = head;
        z->prev = head;
        front=back=nullptr;
        numNodes = 0;
    }
    bool empty() { return head->next == z; }
    int size() { return numNodes; }
    void push_back(T n);
    void push_front(T n);
    T pop_front();
    T pop_back();

    void insert(int pos, T n);
    void remove(T n);
    T at(int pos);
    T find(T n);
};

template <typename T>
void LinkedList<T>::push_back(T n)
{
    node *x = new node(n);
    x->next = z;
    x->prev = z->prev;
    if (empty())
    {

        head->next = front = back = x;
    }
    back->next = x;
    z->prev = back = x;
    numNodes++;
}

template <typename T>
void LinkedList<T>::push_front(T n)
{
    node *x = new node(n);
    x->next = head->next;
    x->prev = head;
    if (empty())
      z->prev = front = back = x;
    
    front->prev = x;
    head->next = front = x;
    numNodes++;
}

template <typename T>
T LinkedList<T>::pop_front()
{
    if (!empty())
    {
        node *t = front;
        T ret = front->data;
        head->next = head->next->next;
        front = head->next;
        front->prev = head;
        delete t;
        numNodes--;
        return ret;
    }
}

template <typename T>
T LinkedList<T>::pop_back()
{
    if (!empty())
    {
        node *t = back;
        T ret = back->data;
        z->prev = z->prev->prev;
        z->prev->next = z;
        back = z->prev;
        delete t;
        numNodes--;
        return ret;
    }
}

template <typename T>
void LinkedList<T>::insert(int pos, T d)
{
    if (pos >= 0 && pos <= numNodes)
    {
      node *n = new node(d);
      int p = 0;
      for (auto itr = head; itr != z; p++, itr = itr->next)
      {
        if (p == pos)
        {
            itr->next->prev = n;
            n->next = itr->next;
            n->prev = itr;
            itr->next = n;
            numNodes++;
        }
      }
    }
}

template <typename T>
T LinkedList<T>::at(int pos)
{
    if (pos > 0 && pos <= numNodes)
    {
      int p = 0;
      for (auto itr = head; itr != z; p++, itr = itr->next)
      {
        if (p == pos)
         return itr->data;
      }
    }
    return NULL;
}

template <typename T>
T LinkedList<T>::find(T n)
{
    for (auto itr = head; itr != z; itr = itr->next)
    {
        if (n == itr->data)
        {
            return itr->data;
        }
    }
    return NULL;
}

template <typename T>
void LinkedList<T>::remove(T n)
{
    for (auto itr = head->next; itr != z; itr = itr->next)
    {
        if (n == itr->data)
        {
            itr->prev->next = itr->next;
            itr->next->prev = itr->prev;
            node *t = itr;
            delete(t);
            numNodes--;
            break;
        }
    }
}

#endif