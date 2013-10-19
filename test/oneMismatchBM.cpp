//#include <iostream>
//#include <string.h>
//#include <vector>
//
//using namespace std;
//
//#define SIZE 26
//#define k 1
///*
//1
//aabdcddaabddcbcabdac
//aacdbcdaab
//*/
//int main() {
//    int T;
//    cin >> T;
//    for (int count = 0; count < T; count++) {
//        string t, p, dump;
//        cin >> t;
//        cin >> p;
//        getline(cin, dump);
//        getline(cin, dump);
//        
//        int m = p.length(), n = t.length();
//        if (m > n)
//            cout<<endl;
//        else if (m == 1) {
//            for (int i = 0; i < n; i++)
//                cout<<i<<" ";
//            cout<<endl;
//        }
//        else {
//            vector<int> ready(SIZE, m);
//            vector<vector<int> > dk(k + 1, vector<int>(SIZE, m));
//            
//            for (int i = m - 2; i >= 0; i--) {
//                int pi = p[i] - 'a';
//                for (int j = ready[pi] - 1; j >= max(i, m - k - 1); j--)
//                    if (i != j)
//                        dk[m - 1 - j][pi] = j - i;
//                ready[pi] = max(i + 1, m - k - 1);
//            }
//            
//            for (int i = 0; i <= k; i++) {
//                for (int j = 0; j < SIZE; j++)
//                    cout<<  dk[i][j] << " ";
//                cout<<endl;
//            }
//            
//            int j = m - 1;
//            
//            while (j < n) {
//                int h = j, i = m - 1, missed = 0, d = m - k;
//                while (i >= 0 && missed <= k) {
//                    if (t[h] != p[i])
//                        missed++;
//                    if (i >= m - k - 1)
//                        d = min(d, dk[m - 1 - i][t[h] - 'a']);
//                    i--;
//                    h--;
//                }
//                if (missed <= k)
//                    cout << j - m + 1<< " ";
//                cout<<"d: "<<d<<endl;
//                j += d;
//            }
//            cout<<endl;
//        }
//    }
//    return 0;
//}