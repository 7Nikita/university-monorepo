public class AVLTree {

    private Node root;

    public class Node {
        private Node left;
        private Node right;
        private Node parent;

        public int key;

        private int balance;
        private int height = 1;

        private Node(int value, Node parent) {
            this.key = value;
            this.parent = parent;
        }

        public Node getParent() {
            return this.parent;
        }

    }

    public AVLTree() { root = null; }

    public boolean insert(int key) {
        if (root == null) {
            root = new Node(key, null);
            return true;
        }

        Node n = root;
        while (true) {
            if (n.key == key)
                return false;

            Node parent = n;

            boolean goLeft = n.key > key;
            n = goLeft ? n.left : n.right;

            if (n == null) {
                if (goLeft)
                    parent.left = new Node(key, parent);
                else
                    parent.right = new Node(key, parent);
                rebalance(parent);
                break;
            }
        }
        return true;
    }

    private void delete(Node node) {
        if (node.left == null && node.right == null) {
            if (node.parent == null)
                root = null;

            else {
                Node parent = node.parent;
                if (parent.left == node)
                    parent.left = null;
                else
                    parent.right = null;
                rebalance(parent);
            }
            return;
        }

        if (node.left != null) {
            Node child = node.left;
            while (child.right != null) child = child.right;
            node.key = child.key;
            delete(child);
        }
        else {
            Node child = node.right;
            while (child.left != null) child = child.left;
            node.key = child.key;
            delete(child);
        }
    }

    public void delete(int delKey) {
        if (root == null)
            return;

        Node child = root;
        while (child != null) {
            Node node = child;
            child = delKey >= node.key ? node.right : node.left;
            if (delKey == node.key) {
                delete(node);
                return;
            }
        }
    }

    private void rebalance(Node n) {
        setBalance(n);

        // L > R
        if (n.balance == -2) {
            if (height(n.left.left) >= height(n.left.right))
                n = rotateRight(n);
            else
                n = rotateLeftThenRight(n);

        }
        // R > L
        else if (n.balance == 2) {
            if (height(n.right.right) >= height(n.right.left))
                n = rotateLeft(n);
            else
                n = rotateRightThenLeft(n);
        }

        if (n.parent != null)
            rebalance(n.parent);
        else
            root = n;
    }

    private Node rotateLeft(Node a) {

        Node b = a.right;
        b.parent = a.parent;

        a.right = b.left;

        if (a.right != null)
            a.right.parent = a;

        b.left = a;
        a.parent = b;

        if (b.parent != null) {
            if (b.parent.right == a) {
                b.parent.right = b;
            }
            else {
                b.parent.left = b;
            }
        }

        setBalance(a, b);

        return b;
    }

    private Node rotateRight(Node a) {

        Node b = a.left;
        b.parent = a.parent;

        a.left = b.right;

        if (a.left != null)
            a.left.parent = a;

        b.right = a;
        a.parent = b;

        if (b.parent != null) {
            if (b.parent.right == a) {
                b.parent.right = b;
            }
            else {
                b.parent.left = b;
            }
        }

        setBalance(a, b);

        return b;
    }

    private Node rotateLeftThenRight(Node n) {
        n.left = rotateLeft(n.left);
        return rotateRight(n);
    }

    private Node rotateRightThenLeft(Node n) {
        n.right = rotateRight(n.right);
        return rotateLeft(n);
    }

    private int height(Node n) {
        if (n == null)
            return -1;
        return n.height;
    }

    private void setBalance(Node... nodes) {
        for (Node n : nodes) {
            reheight(n);
            n.balance = height(n.right) - height(n.left);
        }
    }

    private void reheight(Node node) {
        if (node != null) {
            node.height = 1 + Math.max(height(node.left), height(node.right));
        }
    }

    public Node minNode() {
        var cur = root;
        while (cur.left != null)
            cur = cur.left;
        return cur;
    }

    public Node maxNode() {
        var cur = root;
        while (cur.right != null)
            cur = cur.right;
        return cur;
    }

    private void inorder(Node node) {
        if (node == null)
            return;
        inorder(node.left);
        System.out.print(node.key + " ");
        inorder(node.right);
    }

    public void print_tree() {
        inorder(root);
        System.out.println();
    }

    private Node find(int key, Node n) {
        if (n != null) {
            if (key < n.key)
                return find(key, n.left);
            else if (key > n.key)
                return find(key, n.right);
            else
                return n;
        }
        return null;
    }

    public Node find(int key) {
        return find(key, root);
    }

    private void printBinaryTree(Node root, int level){
        if(root==null)
            return;
        printBinaryTree(root.right, level + 1);
        if(level != 0){
            for(int i = 0; i < level - 1; ++i)
                System.out.print("|\t");
            System.out.println("|-------" + root.key);
        }
        else
            System.out.println(root.key);
        printBinaryTree(root.left, level + 1);
    }

    public void printBinaryTree(){
        printBinaryTree(root, 0);
    }

}
