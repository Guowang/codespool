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
//	node<ELEM> * next;
//
//	template <typename ELEM1>
//	friend class singlist;
//};
//
////template <typename ELEM>
////struct node
////{
////    ELEM data;
////	node<ELEM> * next;
////};
//
//template <typename ELEM>
//class singlist
//{
//private:
//	void freeNode(node<ELEM> * ptr);
//	void clearsinglist();
//public:
//	singlist();
//	~singlist();
//	node<ELEM> * front;
//	ELEM rData(node<ELEM> * ptr);
//	node<ELEM> * rNext(node<ELEM> * ptr);
//	void push(ELEM item);
//	ELEM pop();
//	void reverse();
//};
//
//template <typename ELEM>
//singlist<ELEM>::singlist()
//{
//	node<ELEM> *p;
//	p = new node<ELEM>;
//	front = p;
//	p -> next = NULL;
//}
//
//template <typename ELEM>
//singlist<ELEM>::~singlist()
//{
////    node<ELEM>* current = front;
////    front = NULL;
//    node<ELEM>* temp;
//	while (front != NULL)
//	{
//		temp = front;
//		front = front -> next;
//        delete temp;
//	}
//    //cout<<"ok"<<endl;
//}
//
//template <typename ELEM>
//ELEM singlist<ELEM>::rData(node<ELEM> * ptr)
//{
//	return ptr -> data;
//}
//
//template <typename ELEM>
//node<ELEM> * singlist<ELEM>::rNext(node<ELEM> * ptr)
//{
//	return ptr -> next;
//}
//template <typename ELEM>
//void singlist<ELEM>::freeNode(node<ELEM> * nodeptr)
//{
//	delete nodeptr;
//}
//
//template <typename ELEM>
//void singlist<ELEM>::clearsinglist()
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
//void singlist<ELEM>::push(ELEM item)
//{
//	node<ELEM> * p, * temp;
//	p = new node<ELEM>;
//	temp = front -> next;
//	front -> next = p;
//	p -> data = item;
//	p -> next = temp;
//}
//
//template <typename ELEM>
//ELEM singlist<ELEM>::pop()
//{
//	assert((front -> next) != NULL);
//	node<ELEM> * p;
//	ELEM temp;
//	p = front -> next;
//	front -> next = p -> next;
//
//	temp = p -> data;
//	delete p;
//	return temp;
//}
//
//template <typename ELEM>
//void singlist<ELEM>::reverse()
//{
////	node<ELEM> * p, * q, * temp;
////	p = front -> next;
////	temp = NULL;
////	while (p != NULL)
////	{
////		q = p -> next;
////		p -> next = temp;
////		temp = p;
////		p = q;
////	}
////	if (temp != NULL)
////		front -> next = temp;
//    if (front->next == NULL) return;
//    node<ELEM> *nfront = NULL, *cur = front->next, *next;
//    
//    while (cur != NULL) {
//        node<ELEM> *temp = nfront;
//        next = cur->next;
//        nfront = cur;
//        nfront->next = temp;
//        cur = next;
//    }
//    
//    front->next = nfront;
//    
//}
//
//int main ()
//{
//	singlist<double> s1;
//	s1.push(1.1);
//	s1.push(2.2);
//	s1.push(3.3);
//	s1.push(4.4);
//	
//
//	node<double> * temp = s1.rNext(s1.front);
//
//	while (temp != NULL)
//	{
//		cout <<  s1.rData(temp) <<endl;
//		temp = s1.rNext(temp);
//	}
//    
//	s1.reverse();
//	cout << "After reverse: " << endl;
//	for (int i = 0; i < 4; i++)
//		cout << s1.pop() << endl;
//    
//	return 0;
//}