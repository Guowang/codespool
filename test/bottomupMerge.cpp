//#include <iostream>
//
//using namespace std;
//
//void bottomupMerge(double *, int);
//
//void merge(double *, double *, int, int, int);
//
//int main(){
//    double a[] = {1.1, 6.6, 5.5, 2.2, 4.4, 3.3};
//    int len = sizeof(a) / sizeof(a[0]);
//    
//    bottomupMerge(a, len);
//    
//    for (int i = 0; i < len; i++)
//        cout << a[i] << " ";
//    
//    return 0;
//}
//
//void bottomupMerge(double* a, int N) {
//    
//    double * aux = new double[N];
//    
//    for (int sz = 1; sz < N; sz = sz + sz)
//        for (int lo = 0; lo < N - sz; lo += sz + sz)
//            merge(a, aux, lo, lo + sz - 1, min(lo + sz + sz - 1, N - 1));
//    
//    delete[] aux;
//}
//
//void merge(double* a, double* aux, int lo, int mid, int hi) {
//    for (int i = lo; i <= hi; i++)
//        aux[i] = a[i];
//    int i = lo;
//    int j = mid + 1;
//    for (int k = lo; k <= hi; k++)
//        if (i > mid) a[k] = aux[j++];
//        else if (j > hi) a[k] = aux[i++];
//        else if (aux[i] <= aux[j]) a[k] = aux[i++];
//        else a[k] = aux[j++];
//    
//}