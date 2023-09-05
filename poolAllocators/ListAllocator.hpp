#include <iostream>
#include <vector>
using namespace std;

template <typename valueType, typename indexType = std::size_t>
class ListPool {
    public:
        typedef indexType nodePtr;
        typedef valueType value_type;
    private:
        struct node_t {
            value_type value;
            nodePtr next;
            bool operator==(const node_t& o) const {
                return value == o.value && next == o.next;
            }
            bool operator!=(const node_t& o) {
                return !(*this==o);
            }
        };
        std::vector<node_t> pool;
        nodePtr free_list;
    public:
        value_type& value(nodePtr x) {
            return node(x).value;
        }
        nodePtr& next(nodePtr x) {
            return node(x).next;
        }
        nodePtr free(nodePtr x) {
            nodePtr _next = next(x);
            next(x) = free_list;
            free_list = x;
            return _next;
        }
        nodePtr allocate(const value_type& val, nodePtr tail) {
            nodePtr new_list = free_list;
            if (is_empty(free_list)) {
                new_list = new_node();
            } else {
                free_list = next(free_list);
            }
            value(new_list) = val;
            next(new_list) = tail;
            return new_list;
        }
        bool isEmpty(nodePtr x) {
            return x == empty();
        }
        ListPool() {
            free_list = empty();
        }
        nodePtr empty() {
            return nodePtr(0);
        }
        nodePtr end() {
            return nodePtr(0);
        }
        bool is_end(nodePtr x) {
            return x == end();
        }
        node_t& node(nodePtr x) {
            return pool[x - 1];
        }
        const node_t& node(nodePtr x) const {
            return pool[x-1];
        }
        nodePtr new_node() {
            pool.push_back(node_t());
            return nodePtr(pool.size());
        }
        bool operator==(const ListPool& o) noexcept {
            return pool == o.pool;
        }
        bool operator!=(const ListPool& o) noexcept {
            return !(*this==o);
        }
};

template <typename value_type, typename index_type>
void free_list_x(ListPool<value_type,index_type>& pool, typename ListPool<value_type,index_type>::nodePtr x) {
    while (!pool.isEmpty(x)) 
        x = pool.free(x);
}

template <class T>
class List {
    private:
        ListPool<T, int> pool;
        typedef typename list_pool<T, int>::nodePtr nodePtr;
        typedef typename list_pool<T, int>::value_type value_type;
        nodePtr head;
        nodePtr tail;
        int n;
        nodePtr end() {
            return pool.end();
        }
        T& value(nodePtr x) {
            return pool.value(x);
        }
        nodePtr next(nodePtr x) {
            return pool.next(x);
        }
        bool isNil(nodePtr x) {
            return pool.is_end(x);
        }
    public:
        List() {
            head = end();
            n = 0;
        }
        ~List() {
            free_list(pool, head);
        }
        int size() const {
            return n;
        }
        bool isEmpty() {
            return pool.is_end(head);
        }
        void push_back(value_type val) {
            nodePtr nl = pool.allocate(val, pool.end());
            if (isEmpty()) {
                head = nl;
                tail = nl;
            } else {
                pool.next(tail) = nl;
                tail = nl;
            }
            n++;
        }
        void push_front(value_type val) {
            head = pool.allocate(val, head);
            if (pool.is_end(pool.next(head)))
                tail = head;
            n++;
        }
        T pop_front() {
            T ret = pool.value(head);
            nodePtr tmp = head;
            head = pool.next(head);
            pool.free(tmp);
            n--;
            return ret;
        }
        T pop_back() {
            T ret = pool.value(tail);
            nodePtr it = head;
            if (n > 1) {
                while (pool.next(pool.next(it)) != pool.end()) it = pool.next(it);
                nodePtr tmp = pool.next(it);
                pool.next(it) = pool.next(pool.next(it));
                n--;
                pool.free(tmp);
            } else {
                nodePtr tmp = head;
                head = pool.next(head);
                n--;
                pool.free(tmp);
            }
            return ret;
        }
        void remove(T info) {
            nodePtr it = head;
            bool found = false;
            if (n > 1) {
                while (pool.next(pool.next(it)) != pool.end()) {
                    if (info == pool.value(pool.next(it))) {
                        found = true;
                        break;
                    }
                    it = pool.next(it);
                }
                if (found) {
                    nodePtr tmp = pool.next(it);
                    pool.next(it) = pool.next(pool.next(it));
                    n--;
                    pool.free(tmp);
                }
            } else {
                nodePtr tmp = head;
                head = pool.next(head);
                n--;
                pool.free(tmp);
            }
        }
        class Iterator {
            private:
                nodePtr curr;
                ListPool<T, int> pool;
            public:
                Iterator(nodePtr head, ListPool<T,int>& lp) {
                    curr = head;
                    pool = lp;
                }
                T& operator*() {
                    return pool.value(curr);
                }
                Iterator operator++() {
                    curr = pool.next(curr);
                    return *this;
                }
                Iterator operator++(int) {
                    auto it = *this;
                    ++*this;
                    return it;
                }
                bool operator==(const Iterator& o) noexcept {
                    return pool == o.pool && curr == o.curr;
                }
                bool operator!=(const Iterator& o) noexcept {
                    return !(*this==o);
                }
        };
        Iterator begin() {
            return Iterator(head, pool);
        }
        Iterator end() {
            return Iterator(pool.end(), pool);
        }
};

template <class T>
void print(List<T>& list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout<<*it<<" ";
    }
    cout<<endl;
}

template <class T>
class Queue {
    private:
        List<T> __list;
    public:
        Queue() {

        }
        ~Queue() {

        }
        void push(T info) {
            __list.push_back(info);
        }
        T& top() {
            return (*__list.begin());
        }
        T pop() {
            return __list.pop_front();
        }
        bool isEmpty() {
            return __list.isEmpty();
        }
        int size() {
            return __list.size();
        }
};

template <class T>
class Stack {
    private:
        List<T> __list;
    public:
        Stack() { }
        ~Stack() { }
        void push(T info) {
            __list.push_front(info);
        }
        T& top() {
            return (*__list.begin());
        }
        T pop() {
            return __list.pop_front();
        }
        bool isEmpty() {
            return __list.isEmpty();
        }
        int size() {
            return __list.size();
        }
};

template <class T>
void print(List<T>& list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout<<*it;
    }
    cout<<endl;
} 
