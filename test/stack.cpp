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
//	friend class stack;
//};
//
//
//template <typename ELEM>
//class stack
//{
//private:
//	void freeNode(node<ELEM> * ptr);
//	void clearStack();
//public:
//	stack();
//	~stack();
//	node<ELEM> * front;
//	ELEM rData(node<ELEM> * ptr);
//	node<ELEM> * rNext(node<ELEM> * ptr);
//	void push(ELEM item);
//	ELEM pop();
//	bool empty();
//};
//
//template <typename ELEM>
//stack<ELEM>::stack()
//{
//	node<ELEM> *p;
//	p = new node<ELEM>;
//	front = p;
//	p -> next = NULL;
//}
//
//template <typename ELEM>
//stack<ELEM>::~stack()
//{
//	node<ELEM> * current, * temp;
//	current = front;
//	while (current != NULL)
//	{
//		temp = current;
//		current = temp -> next;
//		freeNode(temp);
//	}
//	front = NULL;
//}
//
//template <typename ELEM>
//ELEM stack<ELEM>::rData(node<ELEM> * ptr)
//{
//	return ptr -> data;
//}
//
//template <typename ELEM>
//node<ELEM> * stack<ELEM>::rNext(node<ELEM> * ptr)
//{
//	return ptr -> next;
//}
//template <typename ELEM>
//void stack<ELEM>::freeNode(node<ELEM> * nodeptr)
//{
//	delete nodeptr;
//}
//
//template <typename ELEM>
//void stack<ELEM>::clearStack()
//{
//	node<ELEM> * current,* temp;
//	current = front -> next;
//	while (current != NULL)
//	{
//		temp = current;
//		current = temp -> next;
//		freeNode(temp);
//	}
//	front = NULL;
//}
//
//
//template <typename ELEM>
//void stack<ELEM>::push(ELEM item)
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
//ELEM stack<ELEM>::pop()
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
//bool stack<ELEM>::empty()
//{
//	if (front -> next == NULL)
//		return 1;
//	else
//		return 0;
//}
//
//template <typename ELEM>
//class queue
//{
//private:
//	stack<ELEM> * in, * out;
//public:
//	queue();
//	~queue();
//	void enqueue(ELEM item);
//	ELEM dequeue();
//	bool empty();
//};
//
//template <typename ELEM>
//queue<ELEM>::queue()
//{
//	in = new stack<ELEM>;
//	out = new stack<ELEM>;
//}
//
//template <typename ELEM>
//queue<ELEM>::~queue()
//{
//	in -> ~stack();
//	out -> ~stack();
//}
//
//template <typename ELEM>
//void queue<ELEM>::enqueue(ELEM item)
//{
//	in -> push(item);
//}
//
//template <typename ELEM>
//ELEM queue<ELEM>::dequeue()
//{
//	if (out -> empty())
//	{
//		while (!(in -> empty()))
//		{
//			out -> push(in -> pop());
//		}
//		return out -> pop();
//	}
//	else
//		return out -> pop();
//}
//
//template <typename ELEM>
//bool queue<ELEM>::empty()
//{
//	return in -> empty() && out -> empty();
//}
//
//template <typename ELEM>
//class qstack
//{
//private:
//	queue<ELEM> * in, * out;
//public:
//	qstack();
//	~qstack();
//	void push(ELEM item);
//	ELEM pop();
//	bool empty();
//};
//
//template <typename ELEM>
//qstack<ELEM>::qstack()
//{
//	queue<ELEM> * i, * o;
//	i = new queue<ELEM>;
//	o = new queue<ELEM>;
//	in = i;
//	out = o;
//}
//
//template <typename ELEM>
//qstack<ELEM>::~qstack()
//{
//	in -> ~queue();
//	out -> ~queue();
//}
//
//template <typename ELEM>
//bool qstack<ELEM>::empty()
//{
//	return in -> empty() && out -> empty();
//}
//
//template <typename ELEM>
//void qstack<ELEM>::push(ELEM item)
//{
//	// O(1) push
//	//in -> enqueue(item);
//
//	// O(n) push
//	queue<ELEM> * temp;
//	out -> enqueue(item);
//	while (!in -> empty())
//		out -> enqueue(in -> dequeue());
//	temp = in;
//	in = out;
//	out = temp;
//}
//
//template <typename ELEM>
//ELEM qstack<ELEM>::pop()
//{
//	// O(n) pop
//	/*ELEM temp;
//	queue<ELEM> * ptr;
//	while (!in -> empty())
//	{
//		temp = in -> dequeue();
//		if (!in -> empty())
//			out -> enqueue(temp);
//		else
//		{
//			ptr = in;
//			in = out;
//			out = ptr;
//			return temp;
//		}
//	}*/
//
//	// O(1) pop
//	return in -> dequeue();
//}
//
//int main ()
//{
//	/*stack<double> s1;
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
//	for (int i = 1; i <= 4; i++)
//	{
//		cout << s1.pop() << endl;
//	}*/
//
//	/*queue<double> l1;
//	l1.enqueue(1.1);
//	l1.enqueue(2.2);
//	l1.enqueue(3.3);
//	l1.enqueue(4.4);
//
//	for (int i = 0; i < 4; ++i)
//	{
//		cout << l1.dequeue() << endl;
//	}
//*/
//	qstack<double> s1;
//	s1.push(1.1);
//	s1.push(2.2);
//	s1.push(3.3);
//	s1.push(4.4);
//	s1.push(5.5);
//	
//	
//	for (int i = 0; i < 5; i++)
//	{
//		cout << s1.pop() << endl;
//	}
//
//	/*int a = 3, b;
//	b = (a++) * 2;
//	cout << a << "\t" << b << endl;
//	a = 3;
//	b = (++a) * 2;
//	cout << a << "\t" << b << endl;*/
//
//	return 0;
//}