#ifndef test_RedBlackTree_h
#define test_RedBlackTree_h

#endif

#include <iostream>
#include <assert.h>
namespace std {
    template <typename Key, typename Value>
    class RBTree{
        
    struct Node {
        public:
            Key key;
            Value val;
            Node* left;
            Node* right;
            bool color;
            int N;
            
            Node(Key key, Value val, bool color, int N) {
                this->key = key;
                this->val = val;
                this->color = color;
                this->N = N;
                this->left = NULL;
                this->right = NULL;
            }
    };
        
    private:
        static const bool RED = true, BLACK = false;
        
        Node* root;
        
        void delTree(Node* h) {
            if (h != NULL) {
                delTree(h->left);
                delTree(h->right);
                delete h;
            }
            return;
        }
        
        bool isRed(Node* x) {
            if (x == NULL) return false;
            return x->color == RED;
        }
        
        int size(Node* x) {
            if (x == NULL) return 0;
            return x->N;
        }
        
        Value get(Node* x, Key key) {
            while (x != NULL) {
                if (x->key < key) 
                    return get(x->right, key);
                else if (x->key > key)
                    return get(x->left, key);
                else
                    return x->val;
            }
            return NULL;
        }
        
        bool contains(Node* x, Key key) {
            if (x == NULL)
            return false;
            if (x->key < key) 
                return contains(x->right, key);
            else if (x->key > key)
                return contains(x->left, key);
            else
                return true;
            
        }
        
        Node* put(Node* x, Key key, Value val) {
            if (x == NULL)
                return new Node(key, val, RED, 1);
            
            if      (x->key < key)       x->right = put(x->right, key, val);
            else if (x->key > key)       x->left = put(x->left, key, val);
            else                         x->val = val;
            
            if (isRed(x->right) && !isRed(x->left))     x = rotateLeft(x);
            if (isRed(x->left) && isRed(x->left->left)) x = rotateRight(x);
            if (isRed(x->left) && isRed(x->right))      flipColors(x);
            
            x->N = size(x->left) + size(x->right) + 1;
            
            return x;
        }
        
        Node* delMin(Node* h) {
            if (h->left == NULL)
                return NULL;
            
            if (!isRed(h->left) && !isRed(h->left->left))
                h = moveRedLeft(h);
            
            h->left = delMin(h->left);
            
            return balance(h);
        }
        
        Node* delMax(Node* h) {
            if (isRed(h->left))
                h = rotateRight(h);
            
            if (h->right == NULL)
                return NULL;
            
            if (!isRed(h->right) && !isRed(h->right->left))
                h = moveRedRight(h);
            
            h->right = delMax(h->right);
            
            return balance(h);
        }
        
        Node* delKey(Node* h, Key key) {
            if (h->key > key) {
                if (!isRed(h->left) && !isRed(h->left->left))
                    h = moveRedLeft(h);
                h->left = delKey(h->left, key);
            }
            else {
                if (isRed(h->left))
                    h = rotateRight(h);
                if ((h->key == key) && (h->right == NULL))
                    return NULL;
                if (!isRed(h->right) && !isRed(h->right->left))
                    h = moveRedRight(h);
                if (h->key == key) {
                    Node* rMin = min(h->right);
                    h->key = rMin->key;
                    h->val = rMin->val;
                    h->right = delMin(h->right);
                }
                else {
                    h->right = delKey(h->right, key);
                }
            }
            return balance(h);
        }
        
        Node* rotateRight(Node* h) {
            Node* x = h->left;
            h->left = x->right;
            x->right = h;
            x->color = h->color;
            h->color = RED;
            x->N = h->N;
            h->N = size(h->left) + size(h->right) + 1;
            return x;
        }
        
        Node* rotateLeft(Node* h) {
            Node* x = h->right;
            h->right = x->left;
            x->left = h;
            x->color = h->color;
            h->color = RED;
            x->N = h->N;
            h->N = size(h->left) + size(h->right) + 1;
            return x;
        }
        
        void flipColors(Node* h) {
            h->color = !h->color;
            h->left->color = !h->left->color;
            h->right->color = !h->right->color;
        }
        
        Node* moveRedLeft(Node* h) {
            flipColors(h);
            
            if (isRed(h->right->left)) {
                h->right = rotateRight(h->right);
                h = rotateLeft(h);
            }
            
            return h;
        }
        
        Node* moveRedRight(Node* h) {
            flipColors(h);
            
            if (isRed(h->left->left)) 
                h = rotateRight(h);
            
            return h;
        }
        
        Node* balance(Node* h) {
            if (isRed(h->right))                        h = rotateLeft(h);
            if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
            if (isRed(h->left) && isRed(h->right))      flipColors(h);
            h->N = size(h->left) + size(h->right) + 1;
            
            return h;
        }
        
        int height(Node* h) {
            if (h == NULL)
                return 0;
            return 1 + std::max(height(h->left), height(h->right));
        }
        
        Node* min(Node* h) {
            if (h->left == NULL)
                return h;
            return min(h->left);
        }
        
        Node* max(Node* h) {
            if (h->right == NULL)
                return h;
            return max(h->right);
        }
        
        Node* floor(Node* h, Key key) {
            if (h == NULL)
                return NULL;
            if (h->key == key)
                return h;
            if (h->key > key)
                return floor(h->left);
            Node* x = floor(h->right, key);
            if (x != NULL) 
                return x;
            return h;
        }
        
        Node* ceiling(Node* h, Key key) {
            if (h == NULL)
                return NULL;
            if (h->key == key)
                return h;
            if (h->key < key)
                return ceiling(h->right);
            Node* x = ceiling(h->left, key);
            if (x != NULL)
                return x;
            return h;
        }
        
        Node* select(Node* h, int k) {
            if (k < 0)
                return NULL;
            int t = size(h->left);
            if (t < k)      return select(h->right, k - t - 1);
            else if (t > k) return select(h->left, k);
            else            return h;
        }
        
        int rank(Node* h, Key key) {
            if (h == NULL)
                return 0;
            if (h->key < key)       return 1 + size(h->left) + rank(h->right, key);
            else if (h->key > key)  return rank(h->left, key);
            else                    return size(h->left);
        }
        
        bool isBST(Node* x, Key min, Key max) {
            if (x == NULL)
                return true;
            if (min != NULL && x->key <= min) return false;
            if (max != NULL && x->key >= max) return false;
            return isBST(x->left, min, x->key) && isBST(x->right, x->key, max);
        }
        
        bool isSizeConsistant(Node* h) {
            if (h == NULL)
                return true;
            if (size(h) != size(h->left) + size(h->right) + 1)
                return false;
            return isSizeConsistant(h->left) && isSizeConsistant(h->right);
        }
        
        bool isRankConsistant() {
            for (int i = 0; i < size(); i++)
                if (i != rank(select(i)))
                    return false;
            return true;
        }
        
        bool is23Tree(Node* h) {
            if (h == NULL)
                return true;
            if (isRed(h->right))
                return false;
            if (h != root && isRed(h) && isRed(h->left))
                return true;
            return is23Tree(h->left) && is23Tree(h->right);
        }
        
        bool isBalanced(Node* x, int black) {
            if (x == NULL)
                return black == 0;
            if (!isRed(x))
                black--;
            return isBalanced(x->left, black) && isBalanced(x->right, black);
        }
    public:
        
        RBTree() {
            root = NULL;
        }
        
        ~RBTree() {
            delTree(root);
        }
        
        int size() {
            return size(root);
        }
        
        bool isEmpty() {
            return root == NULL;
        }
        
        Value get(Key key) {
            return get(root, key);
        }
        
        bool contains(Key key) {
            return contains(root, key);
        }
        
        void put(Key key, Value val) {
            root = put(root, key, val);
            root->color = BLACK;
        }
        
        void delMin() {
            if (root == NULL)
                return;
            if (!isRed(root->left) && !isRed(root->right))
                root->color = RED;
            root = delMin(root);
            if (!isEmpty())
                root->color = BLACK;
        }
        
        void delMax() {
            if (root == NULL)
                return;
            if (!isRed(root->left) && !isRed(root->right))
                root->color = RED;
            root = delMax(root);
            if (!isEmpty())
                root->color = BLACK;
        }
        
        void delKey(Key key) {
            if (!contains(key))
                return;
            
            if (!isRed(root->left) && !isRed(root->right))
                root->color = RED;
            root = delKey(root, key);
            if (!isEmpty())
                root->color = BLACK;
        }
        
        int height() {
            return height(root);
        }
        
        Key min() {
            if (root == NULL)
                return NULL;
            return min(root)->key;
        }
        
        Key max() {
            if (root == NULL)
                return NULL;
            return max(root)->key;
        }
        
        Key floor(Key key) {
            Node* x = floor(root, key);
            if (x == NULL)
                return NULL;
            return x->key;
        }
        
        Key ceiling(Key key) {
            Node* x = ceiling(root, key);
            if (x == NULL)
                return NULL;
            return x->key;
        }
        
        Key select(int k) {
            if (k < 0 || k >= size(root))
                return NULL;
            Node* x = select(root, k);
            return x->key;
        }
        
        int rank(Key key) {
            return rank(root, key);
        }
        
        int size(Key lo, Key hi) {
            if (lo >= hi) 
                return 0;
            if (contains(hi))
                return rank(hi) - rank(lo) + 1;
            return rank(hi) - rank(lo);
        }
        
        void check() {
            assert(isBST());
            assert(isSizeConsistant());
            assert(isRankConsistant());
            assert(is23Tree());
            assert(isBalanced());
        }
        
        bool isBST() {
            return isBST(root, NULL, NULL);
        }
        
        bool isSizeConsistant() {
            return isSizeConsistant(root);
        }
        
        bool is23Tree() {
            return is23Tree(root);
        }
        
        bool isBalanced() {
            int black = 0;
            Node* x = root;
            
            while (x != NULL) {
                if (!isRed(x))
                    black++;
                x = x->left;
            }
            return isBalanced(root, black);
        }
    };
}
