//#include <iostream>
//#include <string>
//#include <tr1/unordered_map>
//#include <memory>
//#include <vector>
//using namespace std;
//
//int main ()
//{
//    tr1::unordered_map<std::string,std::string> mymap;
//    
//    // populating container:
//    mymap["U.S."] = "Washington";
//    mymap["U.K."] = "London";
//    mymap["France"] = "London";
//    mymap["Russia"] = "Moscow";
//    mymap["China"] = "Beijing";
//    mymap["Germany"] = "Berlin";
//    mymap["Japan"] = "Tokyo";
//    
//    // erase examples:
////    mymap.erase ( mymap.begin() );      // erasing by iterator
////    mymap.erase ("France");             // erasing by key
////    mymap.erase ( mymap.find("China"), mymap.end() ); // erasing by range
//    
//    // show content:
//    for ( tr1::unordered_map<std::string,std::string>::const_iterator x = mymap.begin(); x != mymap.end();) {
////        tr1::unordered_map<std::string,std::string>::const_iterator xit = x++;
////        if (xit->second == "London") 
////        {
////            mymap.erase(xit);
////        }
//        if (x->second == "London") 
//        {
//            mymap.erase(x++);
//        }
//        else
//            ++x;
//    }
//    for ( tr1::unordered_map<std::string,std::string>::iterator x = mymap.begin(); x != mymap.end(); ++x ) {
//        std::cout << x->first << ": " << x->second << std::endl;
//    }
//    
//    vector<int> avector;
//    for (int i=1; i<=10; i++) {
//        avector.push_back(i);
//        avector.push_back(i+1);
//    }
//    for (vector<int>::iterator it = avector.begin(); it != avector.end();) {
//        if (*it == 3) 
//        {
//            avector.erase(it);
//        }
//        else
//            ++it;
//    }
//    for (vector<int>::iterator it = avector.begin(); it != avector.end(); it++) {
//        cout << *it <<endl;
//    }
//    return 0;
//}