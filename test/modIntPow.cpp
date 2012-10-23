//#include <iostream>
//
//using namespace std;
//
//long int modIntPow(long int, long int, long int);
//
//int main() {
//    long int a = 12123123121, b = 33223123, c = 12323;
//    cout << modIntPow(a, b, c) << endl;
//    
//    long int test = a % c;
//    for (int i = 1; i < b; i++)
//        test = test * a % c % c;
//    cout << test << endl;
//    
//    return 0;
//}
//
//long int modIntPow(long int a, long int b, long int c) {
//    long int result = 1, base = a % c;
//    
//    while (b > 0) {
//        if (b & 1) 
//            result = result * base % c;
//        b >>= 1;
//        base = base * base % c;
//    }
//    return result;
//}
