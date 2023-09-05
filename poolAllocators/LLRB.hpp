#include <iostream>
#include <vector>
using namespace std;

template <typename K, typename V, typename N = std::size_t>
class tree_pool {
    public:
        typedef N nodePtr;
        typedef K key_type;
        typedef V value_type;
        typedef bool color_type;
    private:
        struct node_t {
            key_type key;
            value_type value;
            color_type color;
            nodePtr left;
            nodePtr right;
            bool operator==(const node_t& o) const {
                return key == o.key;
            }
            bool operator!=(const node_t& o) {
                return !(*this==o);
            }
        };
        std::vector<node_t> pool;
        nodePtr free_list;
    public:
        tree_pool() {
            free_list = empty();
        }
        ~tree_pool() {

        }
        void initfreelist(int initsize) {
            for (int i = 0; i < initsize; i++) {
                nodePtr t = new_node();
                free(t);
            }
        }
        value_type& value(nodePtr x) {
            return node(x).value;
        }
        key_type& key(nodePtr x) {
            return node(x).key;
        }
        color_type& color(nodePtr x) {
            return node(x).color;
        }
        nodePtr& left(nodePtr x) {
            return node(x).left;
        }
        nodePtr& right(nodePtr x) {
            return node(x).right;
        }
        nodePtr& next(nodePtr x) {
            return node(x).right;
        }
        void free(nodePtr x) {
            next(x) = free_list;
            free_list = x;
        }
        nodePtr allocate(K& k, V& val, nodePtr nil_node) {
            nodePtr new_tree = free_list;
            if (is_empty(free_list)) {
                new_tree = new_node();
            } else {
                free_list = _next(free_list);
            }
            key(new_tree) = k;
            value(new_tree) = val;
            color(new_tree) = true;
            right(new_tree) = nil_node;
            left(new_tree) = nil_node;
            return new_tree;
        }
        nodePtr allocate(nodePtr nil_node) {
            nodePtr new_tree = free_list;
            if (is_empty(free_list)) {
                new_tree = new_node();
            } else {
                free_list = next(free_list);
            }
            color(new_tree) = true;
            right(new_tree) = nil_node;
            left(new_tree) = nil_node;
            return new_tree;
        }
        bool is_empty(nodePtr x) {
            return x == empty();
        }
        nodePtr empty() {
            return nodePtr(0);
        }
        nodePtr nil() {
            return nodePtr(0);
        }
        bool is_nil(nodePtr x) {
            return x == nil();
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
        bool operator==(const tree_pool& o) noexcept {
            return pool == o.pool;
        }
        bool operator!=(const tree_pool& o) noexcept {
            return !(*this==o);
        }
};

template <typename K, typename V, typename N>
void free_tree(tree_pool<K,V,N>& pool, typename tree_pool<K,V,N>::nodePtr x) {
    if (!pool.is_empty(x)) {
        free_tree(pool, pool.left(x));
        free_tree(pool, pool.right(x));
        pool.free(x);
    }
}

template <typename K, typename V>
class LLRedBlack {
    private:
        typedef tree_pool<K,V,int> treepool;
        typedef typename tree_pool<K,V,int>::key_type key_type;
        typedef typename tree_pool<K,V,int>::value_type value_type;
        typedef typename tree_pool<K,V,int>::nodePtr nodePtr;
        typedef typename tree_pool<K,V,int>::color_type color_type;
        treepool pool;
        nodePtr root;
        nodePtr& Left(nodePtr x) {
            return pool.left(x);
        }
        nodePtr& Right(nodePtr x) {
            return pool.right(x);
        }
        key_type& Key(nodePtr x) {
            return pool.key(x);
        }
        value_type& Value(nodePtr x) {
            return pool.value(x); 
        }
        color_type& Color(nodePtr x) {
            return pool.color(x);
        }
        bool isNil(nodePtr x) {
            return pool.is_nil(x);
        }
        bool isRed(nodePtr x) {
            return isNil(x) ? false:Color(x) == true;
        }
        V nillValue;
        int n;
        nodePtr rotL(nodePtr h) {
            nodePtr x = Right(h);
            Right(h) = Left(x);
            Left(x) = h;
            Color(x) = Color(h);
            Color(h) = true;
            return x;
        }
        nodePtr rotR(nodePtr h) {
            nodePtr x = Left(h);
            Left(h) = Right(x);
            Right(x) = h;
            Color(x) = Color(h);
            Color(h) = true;
            return x;
        }
        nodePtr flipColor(nodePtr x) {
            Color(x) = true;
            Color(Left(x)) = false;
            Color(Right(x)) = false;
            return x;
        }
        nodePtr bal23(nodePtr x) {
            if (isRed(Right(x)) && !isRed(Left(x))) x = rotL(x);
            if (isRed(Left(x)) && isRed(Left(Left(x)))) x = rotR(x);
            if (isRed(Right(x)) && isRed(Left(x))) x = flipColor(x);
            return x;
        }
        nodePtr put(nodePtr h, K key, V value) {
            if (isNil(h)) {
                n++;
                return pool.allocate(key, value, pool.nil());
            }
            if (key < Key(h)) Left(h) = put(Left(h), key, value);
            else Right(h) = put(Right(h), key, value);
            return bal23(h);
        }
        bool contains(nodePtr h, K key) {
            if (isNil(h))
                return false;
            if (key == Key(h))
                return true;
            if (key < Key(h)) return contains(Left(h), key);
            else return contains(Right(h), key);
        }
        V& get(nodePtr h, K key) {
            if (isNil(h))
                return nillValue;
            if (key == Key(h))
                return Value(h);
            if (key < Key(h)) return get(Left(h), key);
            else return get(Right(h), key);
        }
        void traverse(nodePtr h) {
            if (!isNil(h)) {
                cout<<Key(h)<<" ";
                traverse(Left(h));
                traverse(Right(h));
            }
        }
    public:
        LLRedBlack(int initsize = 150) {
            pool.initfreelist(initsize);
            root = pool.nil();
            n = 0;
        }
        ~LLRedBlack() {
            free_tree(pool, root);
        }
        void insert(K key, V value) {
            root = put(root, key, value);
            Color(root) = false;
        }
        int size() {
            return n;
        }
        V& get(K key) {
            return get(root, key);
        }
        bool contains(K key) {
            return contains(root, key);
        }
        void show() {
            traverse(root);
            cout<<endl;
        }
        V& operator[](K key) {
            if (!contains(key))
                insert(key, 0);
            return get(key);
        }
};
