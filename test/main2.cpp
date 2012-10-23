//#include <iostream>
//using namespace std;
//
//#include "animal.h"
//
//int main()
//{
//    cout << "\n*** Regular objects of animal and dog classes ***\n\n";
//    
//    Animal a(3);
//    Dog d(25);
//    Cat c(46);
//    
//    cout << endl;
//    
//    a.talk();
//    d.talk();
//    c.talk();
//    
//    cout << "\n*** Pointers to objects of corresponding classes ***\n\n";
//    
//    Animal *ap;
//    Dog *dp;
//    Cat *cp;
//    
//    ap = &a;
//    dp = &d;
//    cp = &c;
//    
//    ap->talk();
//    dp->talk();
//    cp->talk();
//    
//    cout << "\n*** Base class pointer pointing to derived class object ***\n\n";
//    
//    ap = &d;
//    ap->talk();
//    ap = &c;
//    ap->talk();
//    
//    cout << endl;
//    
//    return 0;
//}
