//#include <iostream>
//#include <limits>
//using namespace std;
//
//double findkthElement(double *, int, double *, int, int);
//
//int main() {
//    double a[] = {1, 3.3, 5.5, 7.7, 9};
//    double b[] = {2, 3.3, 4.4, 6.6, 8, 10};
//    int alen = sizeof(a) / sizeof(a[0]);
//    int blen = sizeof(b) / sizeof(b[0]);
//    
//    for (int i = 1; i <= alen + blen; i++) {
//        cout << findkthElement(a, alen, b, blen, i) <<endl;
//    }
//    return 0;
//}
//
//double findkthElement(double * a, int alen, double * b, int blen, int k) {
//    if ((k <= alen + blen) && (alen >= 0) && (blen >= 0) && (alen + blen > 0)) {
//        int i = (int) ((double) alen / (alen + blen) * k);
//        int j = k - 1 - i;
//        
//        double ai = (i >= alen) ? numeric_limits<double>::max( ) : a[i]; 
//        double ai_1 = (i <= 0) ? numeric_limits<double>::min( ) : a[i - 1]; 
//        double bj = (j >= blen) ? numeric_limits<double>::max( ) : b[j]; 
//        double bj_1 = (j <= 0) ? numeric_limits<double>::min( ) : b[j - 1]; 
//        
//        if (bj_1 <= ai && ai <= bj) {
//            return ai;
//        }
//        else if (ai_1 <= bj && bj <= ai) {
//            return bj;
//        }
//        
//        if (ai > bj)
//            return findkthElement(a, i - 1, b + j + 1, blen - (j + 1), k - (j + 1));
//        else
//            return findkthElement(a + i + 1, alen - (i + 1), b, j + 1, k - (i + 1));
//
//    }
//    else
//        return NULL;
//}