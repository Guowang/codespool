//#include <iostream>
//#include <string.h>
//#include <vector>
//#include "RedBlackTree.h"
//
//using namespace std;
//
//int main() {
//    
//    RBTree<int, string>* st = new RBTree<int, string>();
//    int n = 10;
//    string s[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
//    for (int i = 0; i < n; i++) {
//        st->put(i, s[i]);
//        st->check();
//        cout<< "size: " << st->size() <<endl;
//        cout<< "height: " << st->height() <<endl;
//        cout<< "min: " << st->get(st->min()) <<endl;
//        cout<< "max: " << st->get(st->max()) <<endl;
//    }
//    cout<<"Test for deletetion."<<endl;
//    for (int i = 0; i < n; i++) {
//        cout<< "size: " << st->size() <<endl;
//        cout<< "height: " << st->height() <<endl;
//        cout<< "min: " << st->get(st->min()) <<endl;
//        cout<< "max: " << st->get(st->max()) <<endl;
//        st->delKey((i + 1) % n);
//        st->check();
//        //st->delMax();
//    }
//
//    return 0;
//}
