//#include <iostream>
//#include <tr1/unordered_map>
//#include <vector>
//#include <string.h>
//#include <algorithm>
//
//using namespace std;
//
//void addSubstring(string, tr1::unordered_map<string, bool>&);
//
//string selectS(int, vector<string>&, vector<int>&, vector<int>&);
//
//int getIndex(int, vector<int>&);
//
//int getLCP(string&, string&);
//
//int main() {
//    int n, k;
//    tr1::unordered_map<string, bool> smap;
//    cin >> n;
//    for (int i = 0; i < n; i++) {
//        string str;
//        cin >> str;
//        addSubstring(str, smap);
//    }
//    
//    vector<string> v;
//    for (tr1::unordered_map<string, bool>::iterator it = smap.begin(); it != smap.end(); ++it)
//        v.push_back(it->first);
//    sort(v.begin(), v.end());
//    
//    vector<int> cv(v.size()), LCP(v.size());
//    cv[0] = v[0].size();
//    for (int i = 1; i < v.size(); i++) {
//        LCP[i] = getLCP(v[i - 1], v[i]);
//        cv[i] = cv[i - 1] + v[i].size() - LCP[i];
//    }
//    
//    for (int i = 0; i < v.size(); i++)
//        cout<<"s: "<<v[i]<<" len: "<<cv[i]<<" LCP: "<<LCP[i]<<endl;
//    
//    cin >> k;
//    int index, len = v.size();
//    for (int i = 0; i < k; i++) {
//        cin >> index;
//        if (index >= 1 && index <= cv[len - 1]) {
//            cout<< selectS(index, v, cv, LCP)<<endl;
//        }
//        else
//            cout<< "INVALID" <<endl;
//    }
//}
//
//void addSubstring(string s, tr1::unordered_map<string, bool> &smap) {
//    if (s.length() == 0) return;
//    
//    for (int i = 0; i < s.length(); i++) {
//        string str = s.substr(i, s.length());
//        if (smap.find(str) == smap.end())
//            smap.insert(make_pair(str, true));
//    }
//}
//
//string selectS(int k, vector<string> &v, vector<int> &cv, vector<int> &LCP) {
//    int index = getIndex(k, cv);
//    if (index > 0)
//        k -= cv[index - 1];
//    return v[index].substr(0, k + LCP[index]);
//}
//
//int getIndex(int k, vector<int> &cv) {
//    int lo = 0, hi = cv.size() - 1;
//    if (k <= cv[lo]) return 0;
//    if (k > cv[hi - 1]) return hi;
//    while (lo < hi) {
//        int mid = (lo + hi) / 2;
//        if (k > cv[mid]) lo = mid + 1;
//        if (k < cv[mid]) hi = mid;
//        if (k == cv[mid]) return mid;
//    }
//    return lo;
//}
//
//int getLCP(string &s, string &t) {
//    int N = min(s.length(), t.length());
//    for (int i = 0; i < N; i++)
//        if (s[i] != t[i]) return i;
//    return N;
//}