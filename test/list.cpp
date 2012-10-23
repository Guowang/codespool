//#include <iostream>
//#include <stdlib.h>
//#include <assert.h>
//
//using namespace std;
//
//template <typename ELEM>
//class list
//{
//private:
//	int max_len;
//	int curr_len;
//	ELEM * nodelist;
//public:
//	int curr;
//	list(int len = 0);
//	~list();
//	bool empty();
//	bool full();
//	bool inlist();
//	void setFirst();
//	void next();
//	void prev();
//	int length();
//	void insert (ELEM item);
//	void append (ELEM item_1);
//	ELEM remove();
//	ELEM currValue();
//};
//
//template <typename ELEM>
//list<ELEM>::list(int len)
//{
//	max_len = len;
//	nodelist = new ELEM[max_len];
//	assert(nodelist != NULL);
//	curr = 0;
//	curr_len = 0;
//}
//
//template <typename ELEM>
//list<ELEM>::~list()
//{
//	delete [] nodelist;
////    cout<<"ok"<<endl;
//}
//
//template <typename ELEM>
//bool list<ELEM>::empty()
//{
//	return (curr_len == 0);
//}
//template <typename ELEM>
//bool list<ELEM>::full()
//{
//	return (curr_len == max_len);
//}
//template <typename ELEM>
//bool list<ELEM>::inlist()
//{
//	return ((curr >= 0) && (curr <= max_len-1));
//}
//
//template <typename ELEM>
//void list<ELEM>::setFirst()
//{
//	if (!empty())
//		curr = 0;
//}
//
//template <typename ELEM>
//void list<ELEM>::next()
//{
//	curr++;
//}
//template <typename ELEM>
//void list<ELEM>::prev()
//{
//	curr--;
//}
//template <typename ELEM>
//int list<ELEM>::length()
//{
//	return curr_len;
//}
//template <typename ELEM>
//void list<ELEM>::insert(ELEM item)
//{
//	assert(inlist() && !full());
//	for (int i = curr_len - 1;i > curr;--i)
//	{
//		nodelist[i] =nodelist[i - 1];
//	}
//	nodelist[curr] = item;
//	curr_len++;
//}
//template <typename ELEM>
//void list<ELEM>::append(ELEM item_1)
//{
//	assert(!full());
//	curr_len++;
//	nodelist[curr_len-1] = item_1;
//}
//template <typename ELEM>
//ELEM list<ELEM>::remove()
//{
//	assert(inlist() && (curr_len > 0));
//	ELEM temp = currValue();
//	for (int i = curr; i < curr_len - 1; ++i)
//		nodelist[i] = nodelist[i + 1];
//	curr_len--;
//	return temp;
//}
//template <typename ELEM>
//ELEM list<ELEM>::currValue()
//{
//	assert(inlist());
//	return nodelist[curr];
//}
//int main()
//{
//	list<double> l1(100);
//	l1.setFirst();
//	l1.insert(0);
//	l1.append(1.1);
//	l1.append(2.2);
//	l1.append(3.3);
//	l1.append(4.4);
//	l1.append(5.5);
//
//	for (l1.setFirst(); l1.curr < l1.length(); l1.next())
//	{
//		cout << l1.currValue() <<endl;
//	}
//
//	l1.prev();
//	cout << l1.currValue() <<endl;
//	l1.prev();
//	l1.prev();
//	l1.next();
//	cout << l1.currValue() <<endl;
//	l1.remove();
//
//	for (l1.setFirst(); l1.curr < l1.length(); l1.next())
//	{
//		cout << l1.currValue() <<endl;
//	}
//
//	return 0;
//}