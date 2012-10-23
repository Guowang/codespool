//#include <iostream>
//#include <stdlib.h>
//#include <assert.h>
//
//using namespace std;
//
//template <typename ELEM>
//class node
//{
//private:
//	ELEM data;
//	node<ELEM> * next, * prev;
//
//	template <typename ELEM1>
//	friend class doublist;
//};
//
//
//template <typename ELEM>
//class doublist
//{
//private:
//	void freeNode(node<ELEM> * ptr);
//	void clearDoublist();
//public:
//	doublist();
//	~doublist();
//	int len;
//	node<ELEM> * front,* rear;
//	ELEM rData(node<ELEM> * ptr);
//	node<ELEM> * rNext(node<ELEM> * ptr);
//	node<ELEM> * rPrev(node<ELEM> * ptr);
//	node<ELEM> * find(const int i);
//	node<ELEM> * search(ELEM key);
//	void append(ELEM item);
//	void insert(ELEM item, int i);
//	void remove(int i);
//	void clearList();
//};
//
//template <typename ELEM>
//doublist<ELEM>::doublist()
//{
//	node<ELEM> *p;
//	p = new node<ELEM>;
//	front = p;
//	rear = front;
//	front -> next = NULL;
//	front -> prev = NULL;
//	len = 0;
//
//}
//
//template <typename ELEM>
//doublist<ELEM>::~doublist()
//{
//	clearList();
//}
//
//template <typename ELEM>
//void doublist<ELEM>::freeNode(node<ELEM> * nodeptr)
//{
//	delete nodeptr;
//}
//
//template <typename ELEM>
//void doublist<ELEM>::clearList()
//{
//	node<ELEM> * current,* temp;
//	current = front -> next;
//	while (current != NULL)
//	{
//		temp = current;
//		current = temp -> next;
//		freeNode(temp);
//	}
//	delete front;
//}
//
//
//template <typename ELEM>
//node<ELEM> * doublist<ELEM>::find(int i)
//{
//	assert((i >= 0) && (i <= len));
//	if (i == 0)
//		return front;
//	else
//	{
//		node<ELEM> * temp;
//		int count = i - 1;
//		temp = front -> next;
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
//void doublist<ELEM>::insert(ELEM item, int i)
//{
//	assert((i >= 1) && (i <= len + 1));
//	node<ELEM> * p, * q;
//	p = new node<ELEM>;
//	q = find(i - 1);
//	p -> prev = q;
//	p -> next = q -> next;
//	p -> data = item;
//	if ((q -> next) != NULL)
//		q -> next -> prev = p;
//	q -> next = p;
//	if (i == len + 1)
//		rear = p;
//	len++;
//}
//
//template <typename ELEM>
//void doublist<ELEM>::remove(int i)
//{
//	assert((i >= 1) && (i <= len));
//	node<ELEM> * p,* q;
//	p = find(i - 1);
//	q = find(i);
//	p -> next = q -> next;
//	if ((q -> next) != NULL)
//		q -> next -> prev = p;
//	else
//		rear = p;
//	delete q;
//	len--;
//}
//
//template <typename ELEM>
//void doublist<ELEM>::append(ELEM item)
//{
//	insert(item,len + 1);
//}
//
//template <typename ELEM>
//node<ELEM> * doublist<ELEM>::rNext(node<ELEM> * ptr)
//{
//	return ptr -> next;
//}
//
//template <typename ELEM>
//node<ELEM> * doublist<ELEM>::rPrev(node<ELEM> * ptr)
//{
//	return ptr -> prev;
//}
//
//template <typename ELEM>
//ELEM doublist<ELEM>::rData(node<ELEM> * ptr)
//{
//	return ptr -> data;
//}
//
//template <typename ELEM>
//node<ELEM> * doublist<ELEM>::search(ELEM key)
//{
//	node<ELEM> * temp;
//	temp = front -> next;
//	while (temp != NULL)
//	{
//		if ((temp -> data) == key)
//			return temp;
//		temp = temp -> next;
//	}
//	return NULL;
//}
//int main ()
//{
//	doublist<double> dl1;
//	dl1.append(1.1);
//	dl1.append(2.2);
//	dl1.append(3.3);
//	dl1.append(4.4);
//	dl1.append(5.5);
//
//	node<double> * temp = dl1.rNext(dl1.front);
//
//	while (temp != NULL)
//	{
//		cout << dl1.rData(temp) <<endl;
//		temp = dl1.rNext(temp);
//	}
//
//	dl1.remove(3);
//	cout << dl1.len << endl;
//	temp = dl1.rear;
//	while (temp != dl1.front)
//	{
//		cout << dl1.rData(temp) <<endl;
//		temp = dl1.rPrev(temp);
//	}
//
//	temp = dl1.search(2.2);
//	cout << dl1.rData(temp) << endl;
//
//	temp = dl1.search(6);
//		if (temp == NULL)
//			cout << "NULL" <<endl;
//
//	return 0;
//}