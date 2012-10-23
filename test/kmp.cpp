//#include <iostream>
//#include <string.h>
//
//using namespace std;
//
//int kmpSearch(string &, string &, int);
//
//int* kmpTable (string &);
//
//int main ()
//{
//    string s = "ababababababababababababcabcbb";
//    string p = "babababcab";
//    int start = 0;
//    cout << kmpSearch(s, p, start) << endl;
//    return 0;
//}
//
//int kmpSearch(string & str,string & words, int start)
//{
//    
//    if (str.size() - words.size() < start) {
//        return -1;
//    }
//    else {
//        int m = start;
//        int i = 0;
//        
//        int * T;
//        T = kmpTable(words);
//        
//        while ((m + i) < str.size()) {
//            if (str[m + i] == words[i]) {
//                if (i == words.size() - 1) {
//                    delete[] T;
//                    return m;
//                }
//                i++;
//            }
//            else {
//                m = m + i - T[i];
//                if (T[i] > -1) {
//                    i = T[i];
//                }
//                else
//                    i = 0;
//            }
//        }
//        
//        delete[] T;
//        return -1;
//    }
//}
//
//int* kmpTable (string & words)
//{
//    int size = (int) words.size();
//    int* T = new int[size];
//
//    if (size == 1) {
//        T[0] = -1;
//        return T;
//    }
//    else {
//        T[0] = -1;
//        T[1] = 0;
//        int pos, cnd;
//        pos = 2;
//        cnd = 0;
//        while (pos < size) {
//            if (words[pos - 1] == words[cnd]) {
//                T[pos++] = ++cnd;
//            }
//            else {
//                if (cnd > 0) {
//                    cnd = T[cnd];
//                }
//                else {
//                    T[pos++] = 0;
//                }
//            }
//            
//        }
//        /*
//        for (int i = 0; i < size; i++) {
//            cout<<T[i]<<"\t";
//        }
//        cout<<endl;
//         */
//        return T;
//    }
//}