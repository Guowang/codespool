//#include <iostream>
//
//using namespace std;
//
//int main() {
//    
//    int a[] = {1, 4, 9, 16};
//    
//    int N = sizeof(a) / sizeof(a[0]);
//    int vol = N/2;
//    
//    int sum = 0;
//    
//    for (int i = 0; i < N; i++) 
//        sum += a[i];
//    sum /= 2; 
//    
//    int f[N + 1][sum + 1][vol+1];
//    
//    for (int i = 0; i <= N; i++)
//        for (int v = 0; v <= sum ; v++)
//            for (int u = 0; u <= vol; u++)   
//                f[i][v][u] = 0;
//    
//    for (int i = 1; i <= N; i++) {
//        for (int v = 0; v <= sum ; v++) {
//            for (int u = 1; u <= vol; u++) {
//                if (i - 1 >= 0) {
//                    if (v - a[i - 1] >= 0) {
//                        f[i][v][u] = max(f[i - 1][v][u], f[i - 1][v - a[i - 1]][u - 1] + a[i - 1]);
//                    }
//                    else
//                        f[i][v][u] = f[i-1][v][u];
//                }
//                cout<<"i:" << i << " v: " << v << " u: " << u << " f: " << f[i][v][u]<<endl;
//            }
//            
//        }
//    }
//    cout << "The result is: "<<endl;
//    cout << f[N][sum][vol] <<endl;
//    return 0;
//}