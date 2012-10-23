//#include <iostream>
//#include <string.h>
//
//using namespace std;
//
//bool equiv_cyc(const string &, const string &);
//
//int count = 0;
//
//int main() {
//    string u = string("aaacaaaaadaaaaaaaaaaaaabaa");
//    string v = string("aadaaaaaaaaaaaaabaaaaacaaa");
//    cout << boolalpha << equiv_cyc(u, v) <<endl;
//    cout << (double)::count / u.length() << endl;
//    return 0;
//}
//
//bool equiv_cyc(const string &u, const string &v)
//{
//    int n = u.length(), i = 0, j = 0, k;
//    if (n != v.length()) return false;
//    
//    while( i<n && j<n )
//    {
//        k = 0;
//        while(k < n && u[(i+k)%n]==v[(j+k)%n]) {k++; ::count++;}
//        if (k == n) return true;
//        if (u[(i+k)%n] > v[(j+k)%n]) i += k + 1; else j += k + 1;
//        ::count++;
//    }
//    
//    return false;
//}