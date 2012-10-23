//#include <iostream>
//#include <string.h>
//using namespace std;
//
//string removeComments(string);
//
//string removeSlashes(string);
//
//string removeStars(string);
//
//int main() {
//    string s = "abc//xyz\nwwe*/*sdfsd/*sdfda*/sd*/cvcd";
//    //abc\nwwe*sd*/cvcd
//    cout << removeComments(s) <<endl;
//    return 0;
//}
//
//string removeComments(string s) {
//    //s = removeSlashes(s);
//    //s = removeStars(s);
//    
//    int prev = 0, cur = 0, tail = 0;
//    bool flag1 = true, flag2 = true;
//    
//    while (cur < s.length()) {
//        if ((s[cur] == '/') && (s[cur + 1] == '/') && flag1 && flag2) {
//            prev = tail;
//            flag1 = false;
//        }
//        else if ((s[cur] == '\n') && !flag1) {
//            tail = prev;
//            flag1 = true;
//        }
//        else if ((s[cur] == '/') && (s[cur + 1] == '*') && flag1 && flag2) {
//            prev = tail;
//            flag2 = false;
//        }
//        else if ((s[cur] == '*') && (s[cur + 1] == '/') && !flag2) {
//            tail = prev;
//            cur += 2;
//            flag2 = true;
//        }
//        s[tail++] = s[cur++];
//    }
//    
//    return s.substr(0, tail);
//}
//
//string removeSlashes(string s) {
//    int prev = 0, cur = 0, tail = 0;
//    bool flag = true;
//    
//    while (cur < s.length()) {
//        if ((s[cur] == '/') && (s[cur + 1] == '/') && flag) {
//            prev = tail;
//            flag = false;
//        }
//        else if ((s[cur] == '\n') && !flag) {
//            tail = prev;
//            flag = true;
//        }
//        s[tail++] = s[cur++];
//    }
//    return s.substr(0, tail);
//}
//
//string removeStars(string s) {
//    int prev = 0, cur = 0, tail = 0;
//    bool flag = true;
//    
//    while (cur < s.length()) {
//        if ((s[cur] == '/') && (s[cur + 1] == '*') && flag) {
//            prev = tail;
//            flag = false;
//        }
//        else if ((s[cur] == '*') && (s[cur + 1] == '/') && !flag) {
//            tail = prev;
//            cur += 2;
//            flag = true;
//        }
//        s[tail++] = s[cur++];
//    }
//    return s.substr(0, tail);
//}