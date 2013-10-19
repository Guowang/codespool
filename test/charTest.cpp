//#include <iostream>
//#include <string>
//
//#define MOD 145827
//
//using namespace std;
//struct inflatable{
//    char name[20];
//    int age;
//    double weight;
//};
//
//int getIndex(int, int);
//
//long long int getCnr(int, int);
//
//int main() {
//    char c = '\007';
//    double e = 9.1e-31;
//    cout<< ":" << c << ":" << long(-100 % 2) << "ok " "ha"<< e <<endl;
//    cout<< getIndex(-100,100) <<endl;
//    inflatable H = {"ha", 10, 4.5};
//    cout<< H.age ;
//    cout<<getCnr(52, 5)<<" : "<<2598960 % MOD<<endl;
//    return 0;
//}
//
//int getIndex(int x, int y) {
//    if (x == 0 && y == 0) return 0;
//    int d = max(abs(x), abs(y)), rest = 4*d*(d - 1);
//    if (x > -d && y == d) return rest + d + x;
//    if (x == d) return rest + 3*d - y;
//    if (y == -d) return rest + 5*d - x;
//    return rest + 7*d + y;
//}
//
//
//long long int getCnr(int n, int k) {
//    if (k == 0) return 0;
//    if (n == 1) return 1;
//    if (k == n) return 1;
//    if (k == 1) return n;
//    long long int a = getCnr(n - 1, k - 1) % MOD;
//    long long int b = getCnr(n - 1, k) % MOD;
//    return (a + b) % MOD;
//}