#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "queue.h"

void showPath(int val[], char from, char to)
{
    printf("\nPath: ");
    for (int v = index(to); v != -1; v = val[v])
    {
        printf("%c ", name(v));
    }
    printf("\n");
}

void bfs(Graph *g, char from, char to)
{
  int val[g->V];
  for (int i = 0; i <= g->V; i++)
  {
      val[i] = -666;
  }
  char curr = from;
  queue* q = newQueue();

  queuePush(&q, curr);
  val[index(curr)] = -1;
  while (!(q->head->next == q->z))
  {
      curr = queuePop(&q);
      printf("%c Popped from queue\n", curr);
      if (curr == to)
      {
          printf("\nFound!\n");
          showPath(val, from, to);
          break;
      }
      for (node* a = g->adj[index(curr)]; a != NULL; a = a->next)
      {
          if (val[index(a->label)] == -666)
          {
              val[index(a->label)] = index(curr);
              printf("%c added to queue\n", a->label);
              queuePush(&q, a->label);
          }
      }
  }
}

int main()
{
    Graph* g = newGraph(5);
    addEdge(&g, 'A', 'B');
    addEdge(&g, 'A', 'C');
    addEdge(&g, 'B', 'E');
    addEdge(&g, 'B', 'D');
    addEdge(&g, 'C', 'D');
    addEdge(&g, 'D', 'E');
    showGraph(g);
    bfs(g, 'A', 'E');
    return 0;
}
