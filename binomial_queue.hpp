/* 
 *  (c) Max Goren 8/2022 MIT LICENSE
 * a minimal implementation of a binomial heap based priority queue
 *  can be used to increase the running time of Dijkstra's SSP algorithm
 *  similar to a fibonacci heap
 */
#ifndef BINOMIAL_QUEUE_HPP
#define BINOMIAL_QUEUE_HPP

#include <iostream>
using namespace std;

template <class Item>
class PQ {
    private:
        struct node {
            Item item;
            node* l;
            node* r;
            node(Item v) { item = v; l = nullptr; r = nullptr; } 
        };
        typedef node* link;
        link* bq;
        static link pair(link p, link q)
        {
            if (p->item > q->item)  //p > q == min heap, p < q == max heap
            {
                p->r = q->l; q->l = p;
                return q;
            } else {
                q->r = p->l; p->l = q;
                return p;
            }
        }
        int N;
        int maxBQsize;
        static inline int test(int C, int B, int A)
        {
            return 4*C + 2*B + 1*A;
        }
        void BQjoin(link *a, link *b)
        {
            link c = nullptr;
            for (int i = 0; i < maxBQsize; i++)
                switch(test(c != nullptr, b[i] != nullptr, a[i] != nullptr))
                {
                    case 2: a[i] = b[i]; 
                            break;
                    case 3: c = pair(a[i], b[i]);
                            a[i] = nullptr; 
                            break;
                    case 4: a[i] = c; 
                            c = nullptr; 
                            break;
                    case 5: c = pair(c, a[i]);
                            a[i] = nullptr;
                            break;
                    case 6:
                    case 7: c = pair(c, b[i]); break;
                }
        }
    public:
        PQ(int n)
        {
            N = 0;
            maxBQsize = n;
            bq = new  node*[maxBQsize];
            for (int i = 0; i < maxBQsize; i++)
                bq[i] = nullptr;
        }
        bool empty() const { return N == 0; }
        int size() const { return N; }
        link insert(Item v)
        {
            link t = new node(v), c = t;
            for (int i = 0; i < maxBQsize; i++)
            {
                if (c == nullptr) break;
                if (bq[i] == nullptr) { bq[i] = c; break; }
                c = pair(c, bq[i]);
                bq[i] = nullptr;
            }
            N++;
            return t;
        }
        Item getmin()
        {
            int i, max;
            Item v;
            link* temp = new link[maxBQsize];
            for (i = 0, max = -1; i < maxBQsize; i++)
                if (bq[i] != nullptr)
                    if ((max == -1) || (v > bq[i]->item)) // if v > bq[i] == min heap, v < bq[i] == max heap
                    {
                        max = i; v = bq[max]->item;
                    }
            link x = bq[max]->l;
            for (i = max; i < maxBQsize; i++) temp[i] = nullptr;
            for (i = max; i > 0; i--)
            {
                temp[i - 1] = x;
                 x = x->r; 
                 temp[i - 1]->r = nullptr;
            }
            delete bq[max];
            bq[max] = nullptr;
            BQjoin(bq, temp);
            delete temp;
            N--;
            return v;          
        }
        Item peek()
        {
            Item v = getmin();
            insert(v);
            return v;
        }
};


#endif