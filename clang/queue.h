#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>

typedef struct qnode {
    void* element;
    struct qnode* next;
    struct qnode* prev;
}qnode;

typedef struct QUEUE {
    qnode* head;
    qnode* z;
    int size;
} QUEUE;

qnode* new_qnode(void* element)
{
    qnode* nqn = (struct qnode*)malloc(sizeof(qnode));
    nqn->element = element;
    nqn->prev = NULL;
    nqn->next = NULL;
    return nqn;
}

QUEUE* newQueue()
{
    QUEUE* nq = (struct QUEUE*)malloc(sizeof nq);
    nq->head = new_qnode(NULL);
    nq->z = new_qnode(NULL);
    nq->head->next = nq->z;
    nq->head->prev = nq->head;
    nq->z->next = nq->z;
    nq->z->prev = nq->head;
    nq->size = 0;
    return nq;
}

void queuePush(QUEUE** q, void* element)
{
    qnode* n = new_qnode(element);
    n->prev = (*q)->z->prev;
    n->next = (*q)->z;
    (*q)->z->prev->next = n;
    (*q)->z->prev = n;
    (*q)->size++;
}

void* queueFront(QUEUE* q)
{
    return q->head->next->element;
}

void queuePop(QUEUE** q)
{
    qnode* t = (*q)->head->next;
    (*q)->head->next = (*q)->head->next->next;
    (*q)->head->next->prev = (*q)->head;
    free(t);
    (*q)->size--;
}

int queueEmpty(QUEUE* q)
{
    return (q->head->next == q->z);
}

int queueSize(QUEUE *q)
{
    return q->size;
}

#endif
