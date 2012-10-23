//#include <iostream>
//#include <stdlib.h>
//#include <assert.h>
//
//using namespace std;
//
//template <typename ELEM>
//class node
//{
//public:
//	ELEM data;
//	node<ELEM> * np;
//
//	//template <typename ELEM>
//	//friend class xordlist;
//};
//
//template <typename ELEM>
//class xordlist
//{
//public:
//	xordlist();
//	~xordlist();
//	node<ELEM> * nil, * head, * rear;
//	void insert(ELEM item); // from rear
//	void del(node<ELEM> * ptr);
//	node<ELEM> * search(ELEM key); // return the first node with key
//	void reverse();
//	void lprint();
//};
//
//template <typename ELEM>
//xordlist<ELEM>::xordlist()
//{
//	node<ELEM> * p;
//	p = new node<ELEM>;
//	nil = p;
//	head = nil;
//	rear = nil;
//	nil -> np = (node<ELEM> *) ((long)head ^ (long)rear);
//}
//
//template <typename ELEM>
//xordlist<ELEM>::~xordlist()
//{
//	//node<ELEM> * ptr, * p, * n, * temp;
//	//ptr = head;
//	//p = nil; //p -> prev
//	//n = (node<ELEM> *) ((int)p ^ (int)(ptr -> np)); // p -> next
//	//while (ptr != nil)
//	//{
//	//	temp = ptr;
//	//	ptr = n;
//	//	p = temp;
//	//	n = (node<ELEM> *) ((int)p ^ (int)(ptr -> np));
//	//	delete temp;
//	//}
//	//delete nil;
//	;
//}
//
//template <typename ELEM>
//void xordlist<ELEM>::insert(ELEM item)
//{
//	node<ELEM> * ptr, * temp;
//
//	ptr = new node<ELEM>;
//	ptr -> data = item;
//	ptr -> np = (node<ELEM> *) ((long)rear ^ (long)nil);
//
//	if (head == nil)
//	{
//		head = ptr;
//		rear = ptr;
//		//nil -> np = (node<ELEM> *) ((int)head ^ (int)rear);
//	}
//	else
//	{
//		temp = (node<ELEM> *)((long)nil ^ (long)(rear -> np)); // prev in rear
//		rear -> np = (node<ELEM> *)((long)temp ^ (long)(ptr));
//		rear = ptr;
//		nil -> np = (node<ELEM> *) ((long)head ^ (long)rear);
//	}
//}
//
//template <typename ELEM>
//void xordlist<ELEM>::del(node<ELEM> * ptr)
//{
//	if (ptr != nil)
//	{
//		node<ELEM> * ptr_1, * p, * n, * temp;
//		ptr_1 = head;
//		p = nil; //p -> prev
//		n = (node<ELEM> *) ((long)p ^ (long)(ptr_1 -> np)); // p -> next
//		while ((ptr_1 != nil) && (ptr_1 != ptr))
//		{
//			p = ptr_1;
//			ptr_1 = n;
//			n = (node<ELEM> *) ((long)p ^ (long)(ptr_1 -> np));
//		}
//		if (ptr_1 == ptr)
//		{
//			temp = (node<ELEM> *) ((long)ptr_1 ^ (long)(p -> np));
//			p -> np = (node<ELEM> *) ((long)temp ^ (long)(n));
//			temp = (node<ELEM> *) ((long)ptr_1 ^ (long)(n -> np));
//			n -> np = (node<ELEM> *) ((long)temp ^ (long)(p));
//			if (ptr == head)
//				head = n;
//			if (ptr == rear)
//				rear = p;
//			delete ptr_1;
//		}
//	}
//}
//
//template <typename ELEM>
//node<ELEM> * xordlist<ELEM>::search(ELEM key)
//{
//		node<ELEM> * ptr_1, * p, * n;
//		nil -> data = key;
//		ptr_1 = head;
//		p = nil; //p -> prev
//		n = (node<ELEM> *) ((long)p ^ (long)(ptr_1 -> np)); // p -> next
//		while (ptr_1 -> data != key)
//		{
//			p = ptr_1;
//			ptr_1 = n;
//			n = (node<ELEM> *) ((long)p ^ (long)(ptr_1 -> np));
//		}
//		return ptr_1;
//}
//
//template <typename ELEM>
//void xordlist<ELEM>::reverse()
//{
//	node<ELEM> * p;
//	p = head;
//	head = rear;
//	rear = p;
//}
//
//template <typename ELEM>
//void xordlist<ELEM>::lprint()
//{
//	node<ELEM> * ptr_1, * p, * n;
//	ptr_1 = head;
//	p = nil; //p -> prev
//	n = (node<ELEM> *) ((long)p ^ (long)(ptr_1 -> np)); // p -> next
//	while (ptr_1 != nil)
//	{
//		cout << ptr_1 -> data << endl;
//		p = ptr_1;
//		ptr_1 = n;
//		n = (node<ELEM> *) ((long)p ^ (long)(ptr_1 -> np));
//	}
//}
//int main ()
//{
//	xordlist<double> xl1;
//	xl1.insert(1.1);
//	xl1.insert(2.2);
//	xl1.insert(3.3);
//	xl1.insert(4.4);
//	xl1.insert(5.5);
//	xl1.lprint();
//	xl1.del(xl1.rear);
//	node<double> * p;
//	p = (node<double> *) ((long)xl1.nil ^ (long)(xl1.head -> np));
//	xl1.del(p);
//	xl1.lprint();
//	xl1.reverse();
//	xl1.lprint();
//	xl1.~xordlist();
//
//	return 0;
//}
