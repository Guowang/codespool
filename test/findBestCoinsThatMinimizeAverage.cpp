//#include <iostream>
//
//using namespace std;
//
//void findBestCoinsThatMinimizeAverage(int, int);
//
//void getMinNumCoins(int, int *, int, int *);
//
//int main() {
//    findBestCoinsThatMinimizeAverage(4, 100);
//    return 0;
//}
//
//void findBestCoinsThatMinimizeAverage(int N, int M) {
//    int * d = new int[N];
//    int * count = new int[M + 1];
//    double min = M, temp = 0;
//    d[0] = 1;
//    int i_min, j_min, k_min;
//    
//    for (int i = 2; i <= M - 2; i++) {
//        d[1] = i;
//        for (int j = i + 1; j <= M - 1; j++) {
//            d[2] = j;
//            for (int k = j + 1; k <= M; k++) {
//                d[3] = k;
//                temp = 0;
//                getMinNumCoins(M, d, N, count);
//                for (int c = 1; c <= M; c++) {
//                    temp += count[c];
//                }
//                temp /= M;
//                if (min > temp) {
//                    min = temp;
//                    i_min = i;
//                    j_min = j;
//                    k_min = k;
//                }
//            }
//        }
//    }
//    cout << 1 << " " << i_min << " " << j_min << " " << k_min <<endl;
//    delete[] d;
//    delete[] count;
//}
//
//void getMinNumCoins(int m, int * d, int n, int * count) {
//    for (int i = 1; i <= m; i++) {
//        count[i] = i;
//        for (int k = 0; k < n; k++)
//            if ((d[k] < i) && (count[i - d[k]] + 1 < count[i]))
//                count[i] = count[i - d[k]] + 1;
//    }
//}
