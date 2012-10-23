//#include <iostream>
//#include <algorithm>
//#include <vector>
//using namespace std;
//
//struct node
//{
//    int index;
//    int dist;
//};
//
//bool myfunction (node i,node j) { return (i.index<j.index); }
//
//struct myclass {
//    bool operator() (node i,node j) { return (i.index>j.index);}
//} myobject;
//
//int main () {
//    node myints[8];
//    myints[0].index = 32;
//    myints[1].index = 71;
//    myints[2].index = 12;
//    myints[3].index = 45;
//    myints[4].index = 26;
//    myints[5].index = 80;
//    myints[6].index = 52;
//    myints[7].index = 33;
//    
//    vector<node> myvector (myints, myints+8);               // 32 71 12 45 26 80 53 33
//    vector<node>::iterator it;
//    
//    
//    // using function as comp
//    sort (myvector.begin(), myvector.end(), myfunction); // 12 32 45 71(26 33 53 80)
//    
//    // using object as comp
//    sort (myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)
//    
//    // print out content:
//    cout << "myvector contains:";
//    for (it=myvector.begin(); it!=myvector.end(); ++it)
//        cout << " " << (*it).index;
//    
//    cout << endl;
//    
//    return 0;
//}