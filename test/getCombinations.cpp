//#include <iostream>
//#include <vector>
//#include <tr1/unordered_set>
//#include <math.h>
//using namespace std;
//
//#define MOD 142857
//
//int getCnr(int, int);
//
//int factorialMod(int, int, int, int);
//
//int extendedE(int, int);
//
//int getF(int, int, int);
//
//void e_gcd(int, int, int&, int&);
//
//int getPower(int, int, int);
//
////int getFactor(int);
////
////int gcd(int, int);
////
////void eliminateOdds(int, vector<int>&);
//
//int main() {
//    int num;
//    cin >> num;
//    for (int i = 0; i < num; i++) {
//        int n, k;
//        cin >> n >> k;
//        cout<< getCnr(n, k) <<endl;
//    }
//    
//    return 0;
//}
//
////int getCnr(int n, int k) {
////    if (k > n/2) k = n - k;
////    if (k == 0) return 0;
////    if (n == 1) return 1;
////    if (k == n) return 1;
////    if (k == 1) return n % MOD;
////
//    vector<int> cur(n, 0), prev(n, 0);
//    
//    
//    for (int i = 0; i < n; i++)
//        prev[i] = i + 1;
//    
//    for (int i = 1; i < k; i++) {
//        for (int j = i; j < n; j++) {
//            if (j == i)
//                cur[j] = 1;
//            else
//                cur[j] = (prev[j - 1] + cur[j - 1]) % MOD;
//        }
//        if (i != k - 1){
//            vector<int> temp;
//            temp = cur;
//            cur = prev;
//            prev = temp;
//        }
//    }
//    
//    return cur[n - 1] % MOD;
////
//
//    
////    tr1::unordered_multiset<int> s;
////    tr1::unordered_multiset<int>::iterator it;
////    for (int i = n; i >= n - k + 1; i--)
////        s.insert(i);
////    
////    for (int i = k; i >= 2; i--) {
////        int num = i;
////        it = s.begin();
////        while (it != s.end() && num != 1) {
////            int d = gcd(num, *it);
////            if (d == 1)
////                ++it;
////            else {
////                num /= d;
////                if (*it != d)
////                    s.insert(*it /d);
////                s.erase(it);
////                
////                if (num == 1)
////                    break;
////                else
////                    it = s.begin();
////            }
////            
////        }
////    }
////    
////    int result = 1;
////    
////    for (it = s.begin(); it != s.end(); ++it)
////        result = (result* (*it % MOD)) % MOD;
////    
////    return result;
////    
////}
////
////int gcd(int p, int q) {
////    if (q == 0) return p;
////    int r = p % q;
////    return gcd(q, r);
////}
////
////int getFactor(int n) {
////    int s = sqrt(n);
////    while (n % s != 0) s--;
////    return s;
////}
////
////void eliminateOdds(int n, vector<int>&v) {
////    if (n == 1) return;
////    int len = v.size();
////    
////    int a = getFactor(n), b = n / a;
////    int i = 0;
////    for (; i < len; i++)
////        if (v[i] % a == 0) {
////            v[i] /= a;
////            break;
////        }
////    if (i == len)
////        eliminateOdds(a, v);
////    
////    i = 0;
////    for (; i < len; i++)
////        if (v[i] % b == 0) {
////            v[i] /= b;
////            break;
////        }
////    if (i == len)
////        eliminateOdds(b, v);
////}
//
//int getCnr(int n, int k) {
//    if (k > n/2) k = n - k;
//    if (k == 0) return 0;
//    if (n == 1) return 1;
//    if (k == n) return 1;
//    if (k == 1) return n % MOD;
//    
//    int m27 = factorialMod(n, k, 3, 3);
//    int m11 = factorialMod(n, k, 11, 1);
//    int m13 = factorialMod(n, k, 13, 1);
//    int m37 = factorialMod(n, k, 37, 1);
//    
//    int e27 = extendedE(27, MOD/27);
//    int e11 = extendedE(11, MOD/11);
//    int e13 = extendedE(13, MOD/13);
//    int e37 = extendedE(37, MOD/37);
//    
//    int result = (m27*e27%MOD + m11*e11%MOD +m13*e13%MOD + m37*e37%MOD) % MOD;
//    return result;
//}
//
//int factorialMod(int n, int k, int p, int c) {
//    int q;
//    if (c != 1)
//        q = 27;
//    else
//        q = p;
//    int nMod = getF(n, p, c);
//    int kMod = getF(k, p, c);
//    int nkMod = getF(n - k, p, c);
//    
//    kMod = (kMod * nkMod) % MOD;
//    
//    int x, y;
//    
//    e_gcd(kMod, q, x, y);
//    
//    x = x*nMod;
//    
//    int nP = n / p;
//    int kP = k / p;
//    int nkP = (n - k) / p;
//    
//    nP = (nP - kP - nkP) % c;
//    
//    for (int i = 0; i < nP; i++)
//        x *= p;
//    
//    return x%MOD;
//}
//
//void e_gcd(int a, int b, int &x, int &y) {
//    if (b ==0) {
//        x = 1;
//        y = 0;
//        return;
//    }
//    e_gcd(b, a%b, x, y);
//    int temp = y;
//    x = y;
//    y = temp - a/b*y;
//}
//
//int extendedE(int a, int b) {
//    int x, y;
//    e_gcd(a, b, x, y);
//    return y*b;
//}
//
//int getF(int n, int p, int c) {
//    int num;
//    if (c != 1)
//        num = 27;
//    else
//        num = p;
//    
//    if (n <= num) {
//        int count = 1;
//        for (int i = 2; i < num; i++)
//            if (i % p != 0)
//                count *= i;
//        return count % MOD;
//    }
//    
//    int q = n / num, r = n % num;
//    
//    int apart = 1;
//    for (int i = 1; i < num; i++)
//        if (i % p != 0)
//            apart *= i;
//    
//    apart %= num;
//    apart = getPower(apart, q, num);
//    apart %= num;
//    
//    int bpart = getF(n / p, p, c)%num;
//    
//    int cpart = 1;
//    for (int i = q*r + 1; i <= n; i++)
//        if (i % p != 0)
//            cpart *= i%num;
//    cpart %= num;
//    
//    return (apart*bpart*cpart)%num;
//}
//
//int getPower(int apart, int q, int num){
//    if (apart == 1) return 1;
//    int result = 1;
//    for (int i = 0; i < q % num; i++)
//        result *= apart;
//    result %= num;
//    int f = 1;
//    for (int i = 1; i < num; i++)
//        f *= apart;
//    f %= num;
//    result = result * getPower(f, q/num, num) % num;
//    return result;
//}