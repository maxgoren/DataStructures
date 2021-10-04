/* a deque (double ended queue */
/* can be used as a queue, or stack */
#include <stdlib.h>

struct elem {
  void* e;
  struct elem* next;
};

typedef struct queue {
    struct elem* head;
    struct elem* z;
    struct elem* front;
    struct elem* back;
} queue;

struct elem* newElem(void* item)
{
    struct elem* t = (struct elem*)malloc(sizeof(struct elem));
    t->e = item;
    t->next = NULL;
    return t;
}

queue* newQueue()
{
    struct queue* t = (struct queue*)malloc(sizeof(struct queue));
    t->head = newElem(NULL);
    t->z = newElem(NULL);
    t->z = t->z;
    t->head->next = t->z;
    return t;
}

void queuePush(struct queue **q, void* item)
{
   struct elem* n = newElem(item);
   if ((*q)->head->next == (*q)->z)
   {
       n->next = (*q)->z;
       (*q)->head->next = (*q)->front = (*q)->back = n;
   } 
    n->next = (*q)->back->next;
    (*q)->back->next = n;
    (*q)->back = n;
}

void* queuePop(struct queue **q)
{
    void* ret = (*q)->front->e;
    struct elem* tmp = (*q)->front;
    (*q)->head->next = (*q)->front = (*q)->front->next;
    free(tmp);
    return ret;
}

void* stackPush(struct queue **q, void* item)
{
   struct elem* n = newElem(item);
   if ((*q)->head->next == (*q)->z)
   {
       n->next = (*q)->z;
       (*q)->head->next = (*q)->front = (*q)->back = n;
   } 
    n->next = (*q)->front->next;
    (*q)->front->next = n;
    (*q)->front = n;   
}

void* stackPop(struct queue **q)
{
    void* ret = (*q)->front->e;
    struct elem* tmp = (*q)->front;
    (*q)->head->next = (*q)->front = (*q)->front->next;
    free(tmp);
    return ret;
}
