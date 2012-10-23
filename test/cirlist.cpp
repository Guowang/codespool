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
//    template <typename ELEM1>
//	friend class cirlist;
//};
//
//
//template <typename ELEM>
//class cirlist
//{
//private:
//	void freeNode(node<ELEM> * ptr);
//	void clearcirlist();
//public:
//	cirlist();
//	~cirlist();
//	int len;
//	node<ELEM> * nil;
//	ELEM rData(node<ELEM> * ptr);
//	node<ELEM> * rNext(node<ELEM> * ptr);
//	node<ELEM> * rPrev(node<ELEM> * ptr);
//	node<ELEM> * find(const int i);
//	node<ELEM> * search(ELEM key);
//	void append(ELEM item);
//	void insert(ELEM item, int i);
//	void remove(int i);
//	void clearList();
//	void push(ELEM item);
//	void del();
//	void reverse();
//};
//
//template <typename ELEM>
//cirlist<ELEM>::cirlist()
//{
//	node<ELEM> *p;
//	p = new node<ELEM>;
//	p -> data = 0;
//	nil = p;
//	p -> next = nil;
//	p -> prev = nil;
//	len = 0;
//
//}
//
//template <typename ELEM>
//cirlist<ELEM>::~cirlist()
//{
//	clearList();
//}
//
//template <typename ELEM>
//void cirlist<ELEM>::freeNode(node<ELEM> * nodeptr)
//{
//	delete nodeptr;
//}
//
//template <typename ELEM>
//void cirlist<ELEM>::clearList()
//{
//	node<ELEM> * current,* temp;
//	current = nil -> next;
//	while (current != nil)
//	{
//		temp = current;
//		current = temp -> next;
//		freeNode(temp);
//	}
//	delete nil;
////    cout<<"ok"<<endl;
//}
//
//
//template <typename ELEM>
//node<ELEM> * cirlist<ELEM>::find(int i)
//{
//	assert((i >= 0) && (i <= len));
//	if (i == 0)
//		return nil;
//	else
//	{
//		node<ELEM> * temp;
//		int count = i - 1;
//		temp = nil -> next;
//		while (count > 0)
//		{
//			temp = temp -> next;
//			count--;
//		}
//		return temp;
//	}
//}
//
//template <typename ELEM>
//void cirlist<ELEM>::insert(ELEM item, int i)
//{
//	assert((i >= 1) && (i <= len + 1));
//	node<ELEM> * p, * q;
//	p = new node<ELEM>;
//	p -> data = item;
//	q = find(i - 1);
//	p -> prev = q;
//	p -> next = q -> next;
//	q -> next -> prev = p;
//	q -> next = p;
//	len++;
//}
//
//template <typename ELEM>
//void cirlist<ELEM>::remove(int i)
//{
//	assert((i >= 1) && (i <= len));
//	node<ELEM> * p,* q;
//	q = find(i);
//	p = q -> prev;
//	p -> next = q -> next;
//	q -> next -> prev = p;
//	delete q;
//	len--;
//}
//
//template <typename ELEM>
//void cirlist<ELEM>::append(ELEM item)
//{
//	node<ELEM> * p;
//	p = new node<ELEM>;
//	p -> data = item;
//	p -> next = nil;
//	p -> prev = nil -> prev;
//	nil -> prev -> next = p;
//	nil -> prev = p;
//	len++;
//}
//
//template <typename ELEM>
//node<ELEM> * cirlist<ELEM>::rNext(node<ELEM> * ptr)
//{
//	return ptr -> next;
//}
//
//template <typename ELEM>
//node<ELEM> * cirlist<ELEM>::rPrev(node<ELEM> * ptr)
//{
//	return ptr -> prev;
//}
//
//template <typename ELEM>
//ELEM cirlist<ELEM>::rData(node<ELEM> * ptr)
//{
//	return ptr -> data;
//}
//
//template <typename ELEM>
//node<ELEM> * cirlist<ELEM>::search(ELEM key)
//{
//	/*node<ELEM> * temp;
//	temp = nil -> next;
//	while (temp != nil)
//	{
//		if ((temp -> data) == key)
//			return temp;
//		temp = temp -> next;
//	}
//	return NULL;*/
//	nil -> data = key;
//	node<ELEM> * temp = nil -> next;
//	while (temp -> data != key)
//		temp = temp -> next;
//	return temp;
//}
//template <typename ELEM>
//void cirlist<ELEM>::push(ELEM item)
//{
//	node<ELEM> * p;
//	p = new node<ELEM>;
//	p -> data = item;
//	p -> next = nil -> next;
//	p -> prev = nil;
//	nil -> next -> prev = p;
//	nil -> next = p;
//	len++;
//}
//template <typename ELEM>
//void cirlist<ELEM>::del()
//{
//	node<ELEM> * p;
//	p = nil -> next;
//	nil -> next = p -> next;
//	p -> next -> prev = nil;
//	delete p;
//	len--;
//}
//
//template <typename ELEM>
//void cirlist<ELEM>::reverse()
//{
//	node<ELEM> * p, * temp;
//	p = nil -> next;
//	nil -> next = nil -> prev;
//	nil -> prev = p;
//	for (int i = 0;i < len;i++)
//	{
//		temp = p -> next;
//		p -> next = p -> prev;
//		p -> prev = temp;
//		p = temp;
//	}
//}
//int main ()
//{
//	cirlist<double> dl1;
//	dl1.append(1.1);
//	//cout << dl1.rData(dl1.rNext(dl1.nil)) << endl;
//	dl1.push(2.2);
//	dl1.append(3.3);
//	dl1.append(4.4);
//	dl1.append(5.5);
//	dl1.insert(1.2,1);
//	dl1.insert(3.5,3);
//	dl1.insert(6,dl1.len + 1);
//	node<double> * temp = dl1.rNext(dl1.nil);
//
//	while (temp != dl1.nil)
//	{
//		cout << dl1.rData(temp) <<endl;
//		temp = dl1.rNext(temp);
//	}
//
//	dl1.remove(3);
//	dl1.del();
//	cout << "Length: " << dl1.len << endl;
//	int l =dl1.len;
//	for (int j = 0;j < l;j++)
//		dl1.del();
//	dl1.append(3.3);
//	dl1.append(4.4);
//	dl1.append(5.5);
//	dl1.append(6.6);
//	cout << "Length: " << dl1.len << endl;
//	temp = dl1.rNext(dl1.nil);
//
//	while (temp != dl1.nil)
//	{
//		cout << dl1.rData(temp) <<endl;
//		temp = dl1.rNext(temp);
//	}
//	dl1.reverse();
//	cout << "After reverse: " << endl;
//	
//
//	temp = dl1.rNext(dl1.nil);
//
//	while (temp != dl1.nil)
//	{
//		cout << dl1.rData(temp) <<endl;
//		temp = dl1.rNext(temp);
//	}
//
//	cout << "From rear: " << endl;
//	temp = dl1.rPrev(dl1.nil);
//	while (temp != dl1.nil)
//	{
//		cout << dl1.rData(temp) <<endl;
//		temp = dl1.rPrev(temp);
//	}
//
//	temp = dl1.search(4.4);
//	cout << dl1.rData(temp) << endl;
//
//	temp = dl1.search(7);
//		if (temp == dl1.nil)
//			cout << "NULL" <<endl;
//
//	node<double> * ptr;
//	temp = dl1.rNext(dl1.nil);
//	temp = dl1.rNext(temp);
//    cout << dl1.nil<<endl;
//    cout<< temp <<endl;
//	ptr = (node<double> *) ((long)(temp) ^ (long)dl1.nil); // XOR
//	ptr = (node<double> *) (((long)(dl1.nil)) ^ ((long)ptr));
//	
//	cout << "Test XOR: " << (temp == ptr) <<endl;
//    cout<<sizeof(float)<<endl;
//    cout<<sizeof(double)<<endl;
//    cout<<sizeof(long double)<<endl;
//
//	return 0;
//}