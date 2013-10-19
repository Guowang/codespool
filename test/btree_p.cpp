#define __test__btree_p__
#ifndef __test__btree_p__
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <stack.h>

using namespace std;

template <typename ELEM>
struct node
{
	node * left, * right, * parent, * sibling, *small, *large;
	ELEM data;
};

template <typename ELEM>
class btree
{
public:
	node<ELEM> * root;
	btree(){root = NULL;};
	~btree(){delete root;};
	void insert(ELEM item);
	void transversal();
    void PreOrderTransversal();
    void InOrderTransversal();
    void PostOrderTransversal();
    void connectSiblings(){connectSiblings(root);};
    void connectSiblings(node<ELEM>* cur);
    node<ELEM>* getNodeAtNextLevel(node<ELEM>*);
    node<ELEM>* getNextSibling(node<ELEM>*);
    node<ELEM>* treeToList(node<ELEM>*);
    void treeToList();
    void treeToListNR();
    node<ELEM>* treeToListNR(node<ELEM>*);
    void joinNodesNR(node<ELEM>*, node<ELEM>*);
    node<ELEM>* appendList(node<ELEM>*, node<ELEM>*);
    void joinNodes(node<ELEM>*, node<ELEM>*);
    void printList(node<ELEM>*);
    void printListNR();
	void del();
    ELEM maxPath();
    ELEM maxPath(node<ELEM>*, ELEM &);
};

template <typename ELEM>
void btree<ELEM>::insert(ELEM item)
{
	node<ELEM> * p, * ptr, * prev;
	p = new node<ELEM>;
	p->data = item;
	prev = NULL;
	ptr = root;
	if (ptr == NULL)
		root = p;
	else
	{
		while (ptr != NULL)
		{
			prev = ptr;
			if (p->data < ptr->data)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
		p->parent = prev;
		if (p->data < prev->data)
			prev->left = p;
		else
			prev->right = p;
	}
}

template <typename ELEM>
void btree<ELEM>::connectSiblings(node<ELEM>* cur) {
    if (cur == NULL)
        return;
    node<ELEM>* p = getNodeAtNextLevel(cur);
    if (p == NULL)
        return;
    node<ELEM>* next = getNextSibling(p), * nextseed = p;
    while (next != NULL) {
        p->sibling = next;
        p = next;
        next = getNextSibling(p);
    }
    connectSiblings(nextseed);
}

template <typename ELEM>
node<ELEM>* btree<ELEM>::getNodeAtNextLevel(node<ELEM>* cur) {
    if (cur == NULL)
        return NULL;
    if (cur->left != NULL)
        return cur->left;
    if (cur->right != NULL)
        return cur->right;
    if (cur->sibling == NULL)
        return NULL;
    return getNodeAtNextLevel(cur->sibling);
}

template <typename ELEM>
node<ELEM>* btree<ELEM>::getNextSibling(node<ELEM>* cur) {
    if (cur == NULL)
        return NULL;
    node<ELEM> *s = NULL, *p = cur->parent;
    if ((cur == p->left) && (p->right != NULL))
        return p->right;
    while ((p->sibling != NULL) && (s == NULL)) {
        if (p->sibling->left != NULL)
            s = p->sibling->left;
        else if (p->sibling->right != NULL)
            s = p->sibling->right;
        p = p->sibling;
    }
    return s;
}

template <typename ELEM>
void btree<ELEM>::transversal()
{
	node<ELEM> * cur, * prev;
	cur = root;
 
    while(cur != NULL) 
	{
		if(cur->left == NULL) 
		{
			cout << cur->data << endl;
            if (cur->sibling != NULL)
                cout << cur->data << " sibling: " << cur->sibling->data <<endl;
			cur = cur->right;
		} 
		else 
		{
			prev = cur->left;
			while((prev->right != NULL) && (prev->right != cur))
				prev = prev->right;
			if (prev->right == NULL) 
			{
				prev->right = cur;
				cur = cur->left;
            } 
			else 
			{
				prev->right = NULL;
				cout << cur->data << endl;
                if (cur->sibling != NULL)
                    cout << cur->data << " sibling: " << cur->sibling->data <<endl;
				cur = cur->right;
            }
         }
     }
}

template <typename ELEM>
node<ELEM>* btree<ELEM>::appendList(node<ELEM> *a, node<ELEM> *b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    
    node<ELEM>* aLast = a->left;
    node<ELEM>* bLast = b->left;
    
    joinNodes(aLast, b);
    joinNodes(bLast, a);
    
    return a;
}

template <typename ELEM>
void btree<ELEM>::joinNodes(node<ELEM> *a, node<ELEM> *b) {
    a->right = b;
    b->left = a;
}

template <typename ELEM>
node<ELEM>* btree<ELEM>::treeToList(node<ELEM> *r) {
    if (r == NULL) return NULL;
    
    node<ELEM> *a = treeToList(r->left);
    node<ELEM> *b = treeToList(r->right);
    
    r->left = r;
    r->right = r;
    
    
    a = appendList(a, r);
    a = appendList(a, b);

    return a;
}

template <typename ELEM>
void btree<ELEM>::treeToListNR() {
    if (root == NULL) return;
    root = treeToListNR(root);
}

template <typename ELEM>
void btree<ELEM>::joinNodesNR(node<ELEM> *a, node<ELEM> *b) {
    //cout<<"hah: " << a->data << " : " << b->data <<endl;
    a->large = b;
    b->small = a;
}

template <typename ELEM>
void btree<ELEM>::treeToList() {
    if (root == NULL) return;
    root = treeToList(root);
}

template <typename ELEM>
node<ELEM>* btree<ELEM>::treeToListNR(node<ELEM> *r) {
    if (r == NULL) return NULL;
    
    node<ELEM>* prev, *cur = r, *p_min = r, *p_max = r;
    
    while(cur != NULL) {
        if (cur->left != NULL) {
            prev = cur->left;
            while (prev->right != NULL && prev->right != cur)
                prev = prev->right;
            if (prev->right == NULL) {
                prev->right = cur;
                joinNodesNR(prev, cur);
                cur = cur->left;
            }
            else {
                prev->right = NULL;
                cur = cur->right;
            }
        }
        else {
            cur = cur->right;
        }
    }
    cout<<endl;
    cur = r;
    while(cur != NULL) {
        if (cur->right != NULL) {
            prev = cur->right;
            while (prev->left != NULL && prev->left != cur)
                prev = prev->left;
            if (prev->left == NULL) {
                prev->left = cur;
                joinNodesNR(cur, prev);
                cur = cur->right;
            }
            else {
                prev->left = NULL;
                cur = cur->left;
            }
        }
        else {
            cur = cur->left;
        }
    }
    
    while (p_min->left != NULL)
        p_min = p_min->left;
    while (p_max->right != NULL)
        p_max = p_max->right;
    
    joinNodesNR(p_max, p_min);
    
    return p_min;
}
template <typename ELEM>
void btree<ELEM>::printList(node<ELEM>* head) {
    node<ELEM> *p = head;
    
    while (p != NULL) {
        cout<< p->data <<" ";
        p = p->right;
        if (p == head) break;
    }
    cout<<endl;
}

template <typename ELEM>
void btree<ELEM>::printListNR() {
    node<ELEM> *p = root;
    
    while (p != NULL){
        cout<< p->data <<" ";
        p = p->large;
        if (p == root) break;
    }
    cout<<endl;
}

template <typename ELEM>
ELEM btree<ELEM>::maxPath() {
    ELEM g;
    return maxPath(root, g);
}

template <typename ELEM>
ELEM btree<ELEM>::maxPath(node<ELEM>* p, ELEM& g){
    if (p == NULL) {
        g = (ELEM) 0;
        return (ELEM) 0;
    }
    ELEM f = (ELEM) 0, leftG = (ELEM) 0, rightG = (ELEM) 0;
    f = max(maxPath(p->left, leftG), maxPath(p->right, rightG));
    f = max(f, p->data + leftG + rightG);
    g = max((ELEM) 0, p->data + max(leftG, rightG));
    return f;
}

template <typename ELEM>
void btree<ELEM>::PreOrderTransversal()
{
	node<ELEM> *cur = root;
	stack<node<ELEM> *> s;
    while (!s.empty() || cur != NULL) {
        //go left
        if (cur != NULL) {
            s.push(cur);
            cout<<cur->data<<" ";
            cur = cur->left;
        }
        //go right
        else {
            cur = s.top()->right;
            s.pop();
        }
    }
    
}

template <typename ELEM>
void btree<ELEM>::InOrderTransversal()
{
	node<ELEM> *cur = root;
	stack<node<ELEM> *> s;
    while (!s.empty() || cur != NULL) {
        //go left
        if (cur != NULL) {
            s.push(cur);
            cur = cur->left;
        }
        //go right
        else {
            cur = s.top()->right;
            cout<<s.top()->data<<" ";
            s.pop();
        }
    }
    
}

template <typename ELEM>
void btree<ELEM>::PostOrderTransversal()
{
	node<ELEM> *cur = root, *prev = NULL;
    if (cur == NULL) {
        return;
    }
    stack<node<ELEM> *> s;
    s.push(cur);
    while (!s.empty()) {
        cur = s.top();
        //go left; if not then try to go right
        if (prev == NULL || cur == prev->left || cur == prev->right) {
            if (cur->left != NULL) {
                s.push(cur->left);
            }
            else if (cur->right != NULL) {
                s.push(cur->right);
            }
        }
        //finish left, try to go right
        else if (cur->left == prev) {
            if (cur->right != NULL) {
                s.push(cur->right);
            }
        }
        //left and right done, visit cur
        else {
            cout<<cur->data<<" ";
            s.pop();
        }
        prev = cur;
    }
    
}

int main()
{
	btree<char> tree1;
    /*
	tree1.insert(12);
	tree1.insert(5);
	tree1.insert(18);
	tree1.insert(2);
	tree1.insert(9);
	tree1.insert(15);
	tree1.insert(19);
	tree1.insert(13);
	tree1.insert(17);
    cout<<tree1.maxPath()<<endl;
     */
    tree1.insert('F');
	tree1.insert('B');
	tree1.insert('G');
	tree1.insert('A');
	tree1.insert('D');
	tree1.insert('C');
	tree1.insert('E');
	tree1.insert('I');
	tree1.insert('H');
    tree1.PostOrderTransversal();
  return 0;
}

#endif