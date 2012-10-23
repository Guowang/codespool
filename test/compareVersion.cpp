//#include <iostream>
//#include <stdlib.h>
//#include <string.h>
//#include <queue>
//
//using namespace std;
//
//bool compareVersion(string&, string&);
//
//double getNum(string&, bool);
//
//queue<string> getString(string&);
//
//int main() {
//    string s1 = "1.0.1";
//    string s2 = "1.0";
//    cout<< boolalpha << compareVersion(s1, s2) <<endl;
//    return 0;
//}
//
//bool compareVersion(string& s1, string& s2) {
//    queue<string> q1 = getString(s1);
//    queue<string> q2 = getString(s2);
//    bool flag = true;    
//    
//    while ((!q1.empty()) && (!q2.empty())) {
//        if (q1.front().compare(q2.front()) != 0)
//            return getNum(q1.front(), flag) > getNum(q2.front(), flag);
//        flag = false;
//        q1.pop();
//        q2.pop();
//    }
//    
//    if(q1.size() != q2.size())
//        return q1.size() > q2.size();
//    
//    return true;
//}
//
//queue<string> getString(string& s) {
//    queue<string> q;
//    for (int i = 0; i < s.length();) {
//        int j = i;
//        for (; j < s.length() && s[j] != '.'; j++) 
//            ;
//        q.push(s.substr(i, j - i));
//        i = j + 1;
//    }
//    return q;
//}
//
//double getNum(string& s, bool flag) {
//    if (flag || s[0] != '0')
//        return atof(s.c_str());
//    string str = "0." + s;
//    return atof(str.c_str());
//}