//#include <iostream>
//#include <stdlib.h>
//#include <assert.h>
//
//using namespace std;
//
//template <typename ELEM>
//struct node
//{
//	ELEM data;
//	node<ELEM> * next;
//};
//
//
//template <typename ELEM>
//class singlist
//{
//private:
//	void freeNode(node<ELEM> * ptr);
//	void clearList();
//public:
//	singlist();
//	~singlist();
//	node<ELEM> * first;
//	int length();
//	node<ELEM> * find(const int i);
//	void append(ELEM item);
//	void insert(ELEM item, int i);
//	void remove(int i);
//};
//
//template <typename ELEM>
//singlist<ELEM>::singlist()
//{
//	node<ELEM> *p;
//	p = new node<ELEM>;
//	first = p;
//	p -> next = NULL;
//}
//
//template <typename ELEM>
//singlist<ELEM>::~singlist()
//{
//	clearList();
//}
//
//template <typename ELEM>
//void singlist<ELEM>::freeNode(node<ELEM> * nodeptr)
//{
//	delete nodeptr;
//}
//
//template <typename ELEM>
//void singlist<ELEM>::clearList()
//{
//	node<ELEM> * current,* temp;
//	current = first -> next;
//	while (current != NULL)
//	{
//		temp = current;
//		current = temp -> next;
//		freeNode(temp);
//	}
//	delete first;
//}
//
//template <typename ELEM>
//int singlist<ELEM>::length()
//{
//	int count = 0;
//	node<ELEM> * temp = first -> next;
//
//	while(temp != NULL)
//	{
//		count++;
//		temp = temp -> next;
//	}
//
//	return count;
//}
//
//template <typename ELEM>
//node<ELEM> * singlist<ELEM>::find(int i)
//{
//	assert((i >= 0) && (i <= length()));
//	if (i == 0)
//		return first;
//	else
//	{
//		node<ELEM> * temp;
//		int count = i - 1;
//		temp = first -> next;
//		while (count > 0)
//		{
//			temp = temp -> next;
//			count--;
//		}
//		assert(temp != NULL);
//		return temp;
//	}
//}
//
//template <typename ELEM>
//void singlist<ELEM>::insert(ELEM item, int i)
//{
//	assert((i >= 1) && (i <= length() + 1));
//	node<ELEM> * p, * q;
//	p = new node<ELEM>;
//	q = find(i - 1);
//	p -> next = q -> next;
//	p -> data = item;
//	q -> next = p;
//}
//
//template <typename ELEM>
//void singlist<ELEM>::remove(int i)
//{
//	assert((i >= 1) && (i <= length()));
//	node<ELEM> * p,* q;
//	p = find(i - 1);
//	q = find(i);
//	p -> next = q -> next;
//	delete q;
//}
//
//template <typename ELEM>
//void singlist<ELEM>::append(ELEM item)
//{
//	int l;
//	l = length();
//	insert(item,l + 1);
//}
//
//int main ()
//{
//	singlist<double> l1;
//	l1.append(1.1);
//	//cout << l1.length() << endl;
//	l1.append(2.2);
//	l1.insert(0.1,1);
//	l1.insert(3.3,2);
//	l1.append(4.4);
//
//	node<double> * temp = l1.first -> next;
//
//	while (temp != NULL)
//	{
//		cout << temp -> data <<endl;
//		temp = temp -> next;
//	}
//	l1.remove(1);
//
//	node<double> * temp1 = l1.first ->next;
//
//	while (temp1 != NULL)
//	{
//		cout << temp1 -> data <<endl;
//		temp1 = temp1 -> next;
//	}
//	cout << l1.length() << endl;
//	
//	return 0;
//}