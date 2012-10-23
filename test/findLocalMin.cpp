//#include <iostream>
//
//using namespace std;
//
//int findLocalMin(int **, int, int, int);
//
//bool isLocalMin(int **, int, int, int, int, int);
//
//int getValue(int **, int, int, int, int, int);
//
//int main() {
//    
//    int N = 9;
//    
//    int** a = new int* [N];
//    for (int i = 0; i < N; i++)
//        a[i] = new int[N];
//    
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            a[i][j] = N * i + j + 10;
//        }
//    }
//    //a[0][0] = 99;
//    a[N - N/3][N - N/4] = -1;
//    
//    cout<< "The matrix is: " <<endl;
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            cout << a[i][j] << " ";
//        }
//        cout << endl;
//    }
//    
//    int localmin = findLocalMin(a, N, 0, 0);
//    cout << "Localmin: " << localmin <<endl;
//    
//    for (int i = 0; i < N; i++)
//        delete[] a[i];
//    delete[] a;
//    
//    return 0;
//}
//
//int findLocalMin(int** a, int N, int i_0, int j_0) {
//    
//    if (N == 1)
//        return a[i_0][j_0];
//    
//    int mid = N/2;
//    
//    int i_mid = i_0 + mid;
//    int j_mid = j_0 + mid;
//    int localmin = a[i_mid][j_mid];
//    int i_min = i_mid;
//    int j_min = j_mid;
//    
//    if (isLocalMin(a, N, i_0, j_0, i_mid, j_mid))
//        return localmin;
//    
//    //check row i_mid
//    for (int j = j_0; j < j_0 + N; j++) {
//        if (a[i_mid][j] < localmin) {
//            j_min = j;
//            localmin = a[i_mid][j];
//        }
//    }
//    
//    //check col j_mid
//    for (int i = i_0; i < i_0 + N; i++) {
//        if (a[i][j_mid] < localmin) {
//            i_min = i;
//            localmin = a[i][j_min];
//        }
//    }
//    
//    if (isLocalMin(a, N, i_0, j_0, i_min, j_min))
//        return localmin;
//    
//    //check position of the min point
//    //on +y
//    if ((j_min == j_mid) && (i_min < i_mid)) {
//        if (getValue(a, N, i_0, j_0, i_min, j_min + 1) < getValue(a, N, i_0, j_0, i_min, j_min - 1))
//            //1st quad
//            return findLocalMin(a, N - (j_mid + 1), i_0, j_mid + 1);
//        else
//            //2nd quad
//            return findLocalMin(a, j_mid, i_0, j_0);
//    }
//    
//    //on -y
//    if ((j_min == j_mid) && (i_min > i_mid)) {
//        if (getValue(a, N, i_0, j_0, i_min, j_min + 1) < getValue(a, N, i_0, j_0, i_min, j_min - 1))
//            //4th quad
//            return findLocalMin(a, N - (i_mid + 1), i_mid + 1, j_mid + 1);
//        else
//            //3rd quad
//            return findLocalMin(a, N - (i_mid + 1), i_mid + 1, j_0);
//    }
//    
//    //on +x
//    if ((i_min == i_mid) && (j_min > j_mid)) {
//        if (getValue(a, N, i_0, j_0, i_min + 1, j_min) < getValue(a, N, i_0, j_0, i_min - 1, j_min))
//            //1st quad
//            return findLocalMin(a, N - (j_mid + 1), i_0, j_mid + 1);
//        else
//            //4rd quad
//            return findLocalMin(a, N - (i_mid + 1), i_mid + 1, j_mid + 1);
//    }
//
//    //on -x
//    if ((i_min == i_mid) && (j_min > j_mid)) {
//        if (getValue(a, N, i_0, j_0, i_min + 1, j_min) < getValue(a, N, i_0, j_0, i_min - 1, j_min))
//            //2nd quad
//            return findLocalMin(a, j_mid, i_0, j_0);
//        else
//            //3rd quad
//            return findLocalMin(a, N - (i_mid + 1), i_mid + 1, j_0);
//    }
//    
//    return INT_MAX;
//}
//
//bool isLocalMin(int** a, int N, int i_0, int j_0, int i_index, int j_index) {
//    //cout << "The point to check is: " << i_index << " , " << j_index << " of " << a[i_index][j_index] <<endl;
//    if (getValue(a, N, i_0, j_0, i_index, j_index) >= getValue(a, N, i_0, j_0, i_index + 1, j_index))
//        return false;
//    if (getValue(a, N, i_0, j_0, i_index, j_index) >= getValue(a, N, i_0, j_0, i_index - 1, j_index))
//        return false;
//    if (getValue(a, N, i_0, j_0, i_index, j_index) >= getValue(a, N, i_0, j_0, i_index, j_index + 1))
//        return false;
//    if (getValue(a, N, i_0, j_0, i_index, j_index) >= getValue(a, N, i_0, j_0, i_index, j_index - 1))
//        return false;
//    return true;
//}
//
//int getValue(int** a, int N, int i_0, int j_0, int i_index, int j_index) {
//    if (i_index < i_0 || i_index > i_0 + N - 1 || j_index < j_0 || j_index > j_0 + N - 1) {
//        return INT_MAX;
//    }
//    else
//        return a[i_index][j_index];
//}