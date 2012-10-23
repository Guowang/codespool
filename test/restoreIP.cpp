//#include <iostream>
//#include <vector>
//#include <string.h>
//
//using namespace std;
//
//vector<string> restoreIpAddresses(string);
//
//vector<string> getString(string, vector<string>, int);
//
//bool isValid(string);
//
//int main() {
//    string s = "010010";
//    
//    vector<string> v = restoreIpAddresses(s);
//    //cout<< boolalpha << isValid("01.0.01.0")<<endl;
//    for (vector<string>::iterator it = v.begin(); it != v.end(); ++it) 
//        cout<< *it <<endl;
//    
//    return 0;
//}
//
//vector<string> restoreIpAddresses(string s) {
//    vector<string> results, r;
//    r = getString(s, results, 0);
//    if (r.size() > 0) {
//        vector<string>::iterator it = r.begin(), tail = r.end();
//        for (; it != tail;) {
//            if (!isValid(*it)) {
//                tail--;
//                *it = *tail;
//            }
//            else
//                it++;
//        }
//        if (it != r.end())
//            r.erase(it, r.end());
//    }
//    return r;
////    results.clear();
////    for (vector<string>::iterator it = r.begin(); it != r.end(); ++it)
////        if (isValid(*it))
////            results.push_back(*it);
////    r.clear();
////    return results;
//}
//
//vector<string> getString(string s, vector<string> v, int n) {
//    
//    vector<string> v1, v2, v3;
//    
//    if (s.length() < 4 - n) return v1;
//    
//    if (n == 3) {
//        if (atoi(s.c_str()) < 256) {
//            for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
//                *it = *it + s;
//            return v;
//        }
//        else
//            return v1;
//    }
//    
//    if (n == 0)
//        v1.push_back(s.substr(0, 1) + '.');
//    else
//        for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
//            v1.push_back(*it + s.substr(0,1) + '.');
//    v1 = getString(s.substr(1, s.length() - 1), v1, n + 1);
//    
//    if (s.length() > 2 && s.length() - 2 >= 3 - n) {
//        if (n == 0)
//            v2.push_back(s.substr(0, 2) + '.');
//        else
//            for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
//                v2.push_back(*it + s.substr(0,2) + '.');
//        v2 = getString(s.substr(2, s.length() - 2), v2, n + 1);
//    }
//    
//    if ( s.length() > 3 && (s.length() - 3 >= 3 - n) && atoi(s.substr(0, 3).c_str()) < 256) {
//        if (n == 0)
//            v3.push_back(s.substr(0, 3) + '.');
//        else
//            for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
//                v3.push_back(*it + s.substr(0,3) + '.');
//        v3 = getString(s.substr(3, s.length() - 3), v3, n + 1);
//    }
//    
//    v.clear();
//    
//    for (vector<string>::iterator it = v1.begin(); it != v1.end(); ++it) 
//        v.push_back(*it);
//    for (vector<string>::iterator it = v2.begin(); it != v2.end(); ++it) 
//        v.push_back(*it);
//    for (vector<string>::iterator it = v3.begin(); it != v3.end(); ++it) 
//        v.push_back(*it);
//    
//    return v;
//}
//
//bool isValid(string s) {
//    if (s.size() == 0) return false;
//    for (int i = 0; i < s.length();) {
//        int j = i + 1;
//        while (j < s.length() && s[j] != '.')
//            j++;
//        if (j == s.length() && j > i + 1 && s[i] == '0')
//            return false;
//        if (s[j] == '.' && j > i + 1 && s[i] == '0')
//            return false;
//        i = j + 1;
//    }
//    return true;
//}