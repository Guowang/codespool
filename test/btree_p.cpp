//#include <iostream>
//#include <stdlib.h>
//
//using namespace std;
//
//template <typename ELEM>
//class node
//{
//public:
//	node * left, * right, * parent, * sibling;
//	ELEM data;
//	node(){}
//	~node()
//	{
//            delete left;
//            delete right;
//	}
//};
//
//template <typename ELEM>
//class btree
//{
//public:
//	node<ELEM> * root;
//	btree(){root = NULL;};
//	~btree(){delete root;};
//	void insert(ELEM item);
//	void transversal();
//    void connectSiblings(){connectSiblings(root);};
//    void connectSiblings(node<ELEM>* cur);
//    node<ELEM>* getNodeAtNextLevel(node<ELEM>*);
//    node<ELEM>* getNextSibling(node<ELEM>*);
//	void del();
//};
//
//template <typename ELEM>
//void btree<ELEM>::insert(ELEM item)
//{
//	node<ELEM> * p, * ptr, * prev;
//	p = new node<ELEM>;
//	p->data = item;
//	
//	prev = NULL;
//	ptr = root;
//	if (ptr == NULL)
//		root = p;
//	else
//	{
//		while (ptr != NULL)
//		{
//			prev = ptr;
//			if (p->data < ptr->data)
//				ptr = ptr->left;
//			else
//				ptr = ptr->right;
//		}
//		p->parent = prev;
//		if (p->data < prev->data)
//			prev->left = p;
//		else
//			prev->right = p;
//	}
//}
//
//template <typename ELEM>
//void btree<ELEM>::connectSiblings(node<ELEM>* cur) {
//    if (cur == NULL)
//        return;
//    node<ELEM>* p = getNodeAtNextLevel(cur);
//    if (p == NULL)
//        return;
//    node<ELEM>* next = getNextSibling(p), * nextseed = p;
//    while (next != NULL) {
//        p->sibling = next;
//        p = next;
//        next = getNextSibling(p);
//    }
//    connectSiblings(nextseed);
//}
//
//template <typename ELEM>
//node<ELEM>* btree<ELEM>::getNodeAtNextLevel(node<ELEM>* cur) {
//    if (cur == NULL)
//        return NULL;
//    if (cur->left != NULL)
//        return cur->left;
//    if (cur->right != NULL)
//        return cur->right;
//    if (cur->sibling == NULL)
//        return NULL;
//    return getNodeAtNextLevel(cur->sibling);
//}
//
//template <typename ELEM>
//node<ELEM>* btree<ELEM>::getNextSibling(node<ELEM>* cur) {
//    if (cur == NULL)
//        return NULL;
//    node<ELEM> *s = NULL, *p = cur->parent;
//    if ((cur == p->left) && (p->right != NULL))
//        return p->right;
//    while ((p->sibling != NULL) && (s == NULL)) {
//        if (p->sibling->left != NULL)
//            s = p->sibling->left;
//        else if (p->sibling->right != NULL)
//            s = p->sibling->right;
//        p = p->sibling;
//    }
//    return s;
//}
//
//template <typename ELEM>
//void btree<ELEM>::transversal()
//{
//	node<ELEM> * cur, * prev;
//	cur = root;
// 
//    while(cur != NULL) 
//	{
//		if(cur->left == NULL) 
//		{
//			cout << cur->data << endl;
//            if (cur->sibling != NULL)
//                cout << cur->data << " sibling: " << cur->sibling->data <<endl;
//			cur = cur->right;
//		} 
//		else 
//		{
//			prev = cur->left;
//			while((prev->right != NULL) && (prev->right != cur))
//				prev = prev->right;
//			if (prev->right == NULL) 
//			{
//				prev->right = cur;
//				cur = cur->left;
//            } 
//			else 
//			{
//				prev->right = NULL;
//				cout << cur->data << endl;
//                if (cur->sibling != NULL)
//                    cout << cur->data << " sibling: " << cur->sibling->data <<endl;
//				cur = cur->right;
//            }
//         }
//     }
//}
//
//int main()
//{
//	btree<double> tree1;
//	tree1.insert(12);
//	tree1.insert(5);
//	tree1.insert(18);
//	tree1.insert(2);
//	tree1.insert(9);
//	tree1.insert(15);
//	tree1.insert(19);
//	tree1.insert(13);
//	tree1.insert(17);
//    tree1.connectSiblings(tree1.root);
//	tree1.transversal();
//	
//  return 0;
//}