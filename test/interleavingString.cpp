//#include <iostream>
//#include <string.h>
//#include <vector>
//
//using namespace std;
//
//bool isInterleaving(string, string, string);
//
//
//int main() {
//    string s1 = "";
//    string s2 = "b";
//    string s3 = "b";
//    
//    cout << boolalpha << isInterleaving(s1, s2, s3) <<endl;
//}
//
//bool isInterleaving(string s1, string s2, string s3) {
//    if (s3.length() != s1.length() + s2.length())
//        return false;
//    
//    vector< vector<bool> > m(s1.length() + 1, vector<bool>(s2.length() + 1, false));
//    m[0][0] = true;
//    
//    for (int  i = 0; i < s1.length(); i++) {
//        if (s1[i] != s3[i])
//            break;
//        m[i + 1][0] = true;
//    }
//    
//    for (int  j = 0; j < s2.length(); j++) {
//        if (s2[j] != s3[j])
//            break;
//        m[0][j + 1] = true;
//    }
//    
//    for (int i = 0; i < s1.length(); i++) {
//        for (int j = 0; j < s2.length(); j++) {
//            if (s1[i] == s3[i + j + 1] && m[i][j + 1])
//                m[i + 1][j + 1] = true;
//            if (s2[j] == s3[i + j + 1] && m[i + 1][j])
//                m[i + 1][j + 1] = true;
//        }
//    }
//    
//    return m[s1.length()][s2.length()];
//
//}
