#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

typedef struct node {
    char label;
    struct node *next;
} node;

typedef struct {
    int V;
    node* adj[];
} Graph;

Graph* newGraph(int N)
{
    Graph* n = malloc(sizeof(Graph));
    n->V = N;
    for (int i = 0; i <= n->V; i++)
    {
      n->adj[i] = malloc(sizeof(node));
      n->adj[i]->next = NULL;
    }
    return n;
}

int index(char k)
{
    return k- 'A' + 1;
}

char name(int k)
{
    return k + 'A' - 1;
}

void addEdge(Graph **g, char from, char to)
{
   node *f = malloc(sizeof(node));
   node *t = malloc(sizeof(node));
   f->label = to;
   t->label = from;

   f->next = (*g)->adj[index(from)];
   (*g)->adj[index(from)] = f;
   t->next = (*g)->adj[index(to)];
   (*g)->adj[index(to)] = t;
}

void showGraph(Graph *g)
{
    for (int i = 1; i <= g->V; i++)
    {
        printf("%c: ", name(i));
        for (node *itr = g->adj[i]; itr != NULL; itr = itr->next)
          printf("%c ", itr->label);
        printf("\n");
    }
}
