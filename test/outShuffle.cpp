//#include <iostream>
//#include <math.h>
//
//using namespace std;
////index from 1!!!
//void nOutShuffle(int*, int);
//
//void n2OutShuffle(int*, int);
//
//bool check(int*, int, int*, int);
//
//void arrSwap(int*, int, int);
//
//void arrReverse(int*, int, int);
//
//int main() {
//    for (int i = 2; i <= 1000; i += 2) {
//        int* A = new int[i + 1];
//        int* B = new int[i + 1];
//        for (int j = 1; j <= i; j++) {
//            A[j] = j;
//            B[j] = j;
//        }
//        cout<< "i: " << i <<endl;
//        cout<< boolalpha <<check(A, i+1, B, i+1) <<endl;
//        delete[] A;
//        delete[] B;
//    }
//    return 0;
//}
//
//bool check(int* A, int alen, int* B, int blen) {
//    if (alen != blen)
//        return false;
//    
//    n2OutShuffle(A, alen);
//    nOutShuffle(B, blen);
//    
//    for (int i = 1; i < alen; i++)
//        if (A[i] != B[i])
//            return false;
//    return true;
//}
//
//void nOutShuffle(int* A, int len) {
//    
//    if (len == 0 || len == 1 || len == 3) 
//        return;
//    if (len == 5) {
//        arrSwap(A, 2, 3);
//        return;
//    }
//    
//    int k = 0, n = (len - 1) / 2;
//    double length = len;
//    //3^k <= len <3^(k+1)
//    while (length >= 3) {
//        k++;
//        length /= 3;
//    }
//    //2*m = 3^k - 1;
//    int m = (pow(3, k) - 1) / 2;
//    
//    if (m < n) {
//        arrReverse(A, m + 1, n + m);
//        arrReverse(A, m + 1, 2*m);
//        arrReverse(A, 2*m + 1, n + m);
//    }
//    
//    if (m > 1) {
//        for (int i = 1; i <= 2*m; i *= 3) {
//            int cur = i;
//            int next = 2*cur % (2*m + 1);
//            int storage = A[cur];
//            while (next != i) {
//                int temp = A[next];
//                A[next] = storage;
//                storage = temp;
//                cur = next;
//                next = 2*cur % (2*m + 1); 
//            }
//            A[i] = storage; 
//        }
//        //in-shuffle to out-shuffle
//        for (int i = 1; i <= m; i++)
//            arrSwap(A, 2*i - 1, 2*i);
//    }
//    
//    nOutShuffle(A + 2*m, 2*(n - m) + 1);
//}
//
//void n2OutShuffle(int* A, int len) {
//    int n = (len - 1) / 2;
//    for (int i = 1; i < n; i++)
//        for (int j = 0; j < i; j++)
//            arrSwap(A, n - i + 2*j + 1, n - i + 2*j + 2);
//}
//
//void arrSwap(int* A, int i, int j) {
//    int temp = A[i];
//    A[i] = A[j];
//    A[j] = temp;
//}
//
//void arrReverse(int* A, int i, int j) {
//    while (i < j) {
//        arrSwap(A, i, j);
//        i++;
//        j--;
//    }
//}