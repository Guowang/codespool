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
//class queues
//{
//private:
//	void freeNode(node<ELEM> * ptr);
//	void clearQueue();
//public:
//	queues();
//	~queues();
//	node<ELEM> * first, * rear;
//	//int length();
//	void enqueue(ELEM item);
//	ELEM dequeue();
//};
//
//template <typename ELEM>
//queues<ELEM>::queues()
//{
//	node<ELEM> *p;
//	p = new node<ELEM>;
//	first = p;
//	rear = first;
//	p -> next = NULL;
//}
//
//template <typename ELEM>
//queues<ELEM>::~queues()
//{
//	clearQueue();
//}
//
//template <typename ELEM>
//void queues<ELEM>::freeNode(node<ELEM> * nodeptr)
//{
//	delete nodeptr;
//}
//
//template <typename ELEM>
//void queues<ELEM>::clearQueue()
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
////template <typename ELEM>
////int queues<ELEM>::length()
////{
////	int count = 0;
////	node<ELEM> * temp = first -> next;
////
////	while(temp != NULL)
////	{
////		count++;
////		temp = temp -> next;
////	}
////
////	return count;
////}
//
//template <typename ELEM>
//void queues<ELEM>::enqueue(ELEM item)
//{
//	node<ELEM> * p;
//	p = new node<ELEM>;
//	rear -> next = p;
//	rear = p;
//	p -> data = item;
//	p -> next = NULL;
//}
//
//template <typename ELEM>
//ELEM queues<ELEM>::dequeue()
//{
//	assert((first -> next) != NULL);
//	node<ELEM> * p;
//	p = first -> next;
//	first -> next = p -> next;
//	ELEM temp;
//	temp = p -> data;
//	delete p;
//	return temp;
//}
//
//int main ()
//{
//	queues<double> l1;
//	l1.enqueue(1.1);
//	l1.enqueue(2.2);
//	l1.enqueue(3.3);
//	l1.enqueue(4.4);
//	
//
//	node<double> * temp = l1.first -> next;
//
//	while (temp != NULL)
//	{
//		cout << temp -> data <<endl;
//		temp = temp -> next;
//	}
//
//	for (int i = 1; i <= 4; i++)
//	{
//		cout << l1.dequeue() << endl;
//	}
//
//	return 0;
//}