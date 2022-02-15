import java.util.Random;

public class BinarySearchTree<K extends Comparable, V> {
    final static Boolean red = true;
    final static Boolean black = false;
    class Node<K extends Comparable, V> {
        private Node left;
        private Node right;
        private K key;
        private V value;
        private Boolean color;
        Node()
        {
            this.left = null;
            this.right = null;
            this.color = red;
        }
        Node(K key, V value)
        {
            this.key = key;
            this.value= value;
            this.left = null;
            this.right = null;
            this.color = red;
        }
        public void setLeft(Node l)
        {
            this.left = l;
        }
        public void setRight(Node r)
        {
            this.right = r;
        }
        public void setColor(Boolean c)
        {
            this.color = c;
        }
        public Boolean color()
        {
            return color;
        }
        public K key()
        {
            return key;
        }
        public V value()
        {
            return value;
        }
        public Node leftChild()
        {
            return left;
        }
        public Node rightChild()
        {
            return right;
        }
    }
    private Node<K,V> root;
    BinarySearchTree()
    {
        root = null;
    }
    private Boolean isRed(Node<K,V> h)
    {
        if (h == null) 
            return false;

        return h.color();
    }
    private Node<K,V> colorFlip(Node<K,V> h)
    {
        h.setColor(!h.color());
        h.leftChild().setColor(!h.leftChild().color());
        h.rightChild().setColor(!h.rightChild().color());
        return h;
    }
    private Node<K,V> rightRotate(Node<K,V> h)
    {
        Node<K,V> x = h.leftChild();
        h.setLeft(x.rightChild());
        x.setRight(h);
        x.setColor(h.color());
        h.setColor(red);
        return x;
    }
    private Node<K,V> leftRotate(Node<K,V> h)
    {
        Node<K,V> x = h.rightChild();
        h.setRight(x.leftChild());
        x.setLeft(h);
        x.setColor(h.color());
        h.setColor(red);
        return x;
    }
    private Node<K,V> fixTree(Node<K,V> h)
    {
        if (isRed(h.rightChild()) && !isRed(h.leftChild()))
            h = leftRotate(h);
        if (isRed(h.leftChild()) && isRed(h.leftChild().leftChild()))
            h = rightRotate(h);
        if (isRed(h.leftChild()) && isRed(h.rightChild()))
            h = colorFlip(h);
        return h;
    }
    private Node<K,V> insert(Node<K,V> h, K key, V val)
    {
        if (h == null)
        {
            return new Node(key, val);
        }
        if (key.compareTo(h.key()) < 0)
        {
            h.setLeft(insert(h.leftChild(), key, val));
        } else {
            h.setRight(insert(h.rightChild(), key, val));
        }
        return fixTree(h);
    }
    public void insert(K key, V val)
    {
        root = insert(root, key, val);
        root.setColor(black);
    }
    private Node<K,V> deleteMin(Node<K,V> h)
    {
        if (h.leftChild() == null)
          return h.rightChild();

        h.setLeft(deleteMin(h.leftChild()));

        return h;
    }
    private Node<K,V> min(Node<K,V> h)
    {
        if (h.leftChild() == null)
          return h;

        return min(h.leftChild());
    }
    private Node<K,V> delete(Node<K,V> h, K key)
    {
        if (h == null)
            return null;

        if (key.compareTo(h.key()) < 0)
           h.setLeft(delete(h.leftChild(), key));
        else if (key.compareTo(h.key()) > 0)
           h.setRight(delete(h.rightChild(), key));
        else {
            if (h.rightChild() == null)
               return h.leftChild();

            Node<K,V> temp = h;
            h = min(temp.rightChild());
            h.setRight(deleteMin(temp.rightChild()));
            h.setLeft(temp.leftChild());
        }
        return h;
    }
    public void delete(K key)
    {
        root = delete(root, key);
        root.setColor(black);
    }
    private void preorder(Node<K,V> h)
    {
        if (h == null) return;
        System.out.print(h.key() + ":" + h.value());
        if (isRed(h)) System.out.println(" red");
        else System.out.println(" black");
        preorder(h.leftChild());
        preorder(h.rightChild());
    }
    public K getMin()
    {
        return min(root).key(); 
    }
    public void show()
    {
        preorder(root);
    }
    public static void main(String[] args) {
        BinarySearchTree<Character, Integer> myBST = new BinarySearchTree();
        Random rng = new Random();
        String sed = "ASEARCHINGEXAMPLE";
        for (int i = 0; i < 17; i++)
        {
            myBST.insert(sed.charAt(i), rng.nextInt(100));
        }
        myBST.show();
        System.out.println("\n min: " + myBST.getMin());
        myBST.delete('P');
        myBST.show();
    }
}