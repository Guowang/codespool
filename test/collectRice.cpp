//#include <iostream>
//
//using namespace std;
//
//int collectRice(int **, int, int);
//
//int columnCollectRice(int **, int, int);
//
//int rowCollectRice(int **, int, int);
//
////2 2 3 0 0 3 1 1 1 2 2 1
///*
//2 2 3
//0 0 3
//1 1 1
//2 2 1
// */
//int main() {
//    int m = 4, n = 3;
//    int ** a = new int*[m];
//    for (int i = 0; i < m; i++)
//        a[i] = new int[n];
//    for (int i = 0; i < m; i++)
//        for (int j = 0; j < n; j++)
//            cin >> a[i][j];
//    cout << collectRice(a, m, n) << endl;
//    
//    for (int i = 0; i < m; i++) 
//        delete[] a[i];
//    delete[] a;
//    return 0;
//}
//
//int collectRice(int ** a, int m, int n) {
//    if (m > n)
//        return rowCollectRice(a, m, n);
//    return columnCollectRice(a, m, n);
//}
//
//int columnCollectRice(int ** a, int m, int n) {
//    int * cj_1 = new int[n];
//    int * cj = new int[n];
//    int * temp = cj;
//    
//    cj_1[0] = a[0][0];
//    for (int i = 1; i < m; i++)
//        cj_1[i] = cj_1[i - 1] + a[i][0];
//    
//    for (int j = 1; j < n; j++) {
//        cj[0] = cj_1[0] + a[0][j];
//        for (int i = 1; i < m; i++)
//            cj[i] = max(cj_1[i], cj[i - 1]) + a[i][j];
//        if (j != n - 1) {
//            temp = cj;
//            cj = cj_1;
//            cj_1 = temp;
//        }
//    }
//    
//    return cj[m - 1];
//    delete[] cj_1;
//    delete[] cj;
//}
//
//int rowCollectRice(int ** a, int m, int n) {
//    int * ri_1 = new int[n];
//    int * ri = new int[n];
//    int * temp = ri;
//    
//    ri_1[0] = a[0][0];
//    for (int j = 1; j < n; j++)
//        ri_1[j] = ri_1[j - 1] + a[0][j];
//    
//    for (int i = 1; i < m; i++) {
//        ri[0] = ri_1[0] + a[i][0];
//        for (int j = 1; j < n; j++)
//            ri[j] = max(ri_1[j], ri[j - 1]) + a[i][j];
//        if (i != m - 1) {
//            temp = ri;
//            ri = ri_1;
//            ri_1 = temp;
//        }
//    }
//    
//    return ri[n - 1];
//    delete[] ri_1;
//    delete[] ri;
//}