//#include <iostream>
//#include <vector>
//#include <string.h>
//
//using namespace std;
//
//vector<int> ZAlgorithm(string);
//
//int main() {
//    string s = "aabaaaba";
//    vector<int> v = ZAlgorithm(s);
//    
//    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) 
//        cout<< *it << " ";
//    cout<<endl;
//    
//    return 0;
//}
//
//vector<int> ZAlgorithm(string s) {
//    vector<int> v(s.length(), 0);
//    v[0] = (int) s.length();
//    
//    int r = 0, l = 0;
//    
//    for (int i = 1; i < s.length(); ++i) {
////        if (i <= r) {
////            int kprim = i - l;
////            int beta = r - i;
////            v[i] = (v[kprim] > beta) ? beta : v[kprim];
////        }
//        v[i] = (i > r)? 0 : min(v[i - l], r - i);
//        
//        while (i + v[i] < s.length() && s[i + v[i]] == s[v[i]]) 
//            v[i]++;
//        
//        if (r < i + v[i]) {
//            r = i + v[i];
//            l = i;
//        }
//    }
//    
//    return v;
//}