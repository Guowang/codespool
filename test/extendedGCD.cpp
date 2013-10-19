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
//int getE(int, int);
//
//void e_gcd(int, int, int&, int&);
//
//int getPower(int, int, int);
//
//int Lucas(int, int, int);
//
//int sCnr(int, int, int);
//
//int arr27[27] = {1, 2, 2, 8, 13, 26, 20, 25, 25, 7, 23, 11, 8, 4, 20, 23, 13, 26, 8, 25, 13, 16, 17, 1, 25, 2, 2};
//int arr11[11] = {1, 2, 6, 2, 10, 5, 2, 5, 1, 10, 10};
//int arr13[13] = {1, 2, 6, 11, 3, 5, 9, 7, 11, 6, 1, 12, 12};
//int arr37[37] = {1, 2, 6, 24, 9, 17, 8, 27, 21, 25, 16, 7, 17, 16, 18, 29, 12, 31, 34, 14, 35, 30, 24, 21, 7, 34, 30, 26, 14, 13, 33, 20, 31, 18, 1, 36, 36};
//
//int arrS27[27] = {1, 2, 2, 8, 13, 13, 10, 26, 26, 17, 25, 25, 1, 14, 14, 8, 1, 1, 19, 2, 2, 17, 13, 13, 1, 26, 26};
//
//vector<int> decomp(int, int);
//
//int main() {
//    /*
//    int count = 1, num1 = 27, p = 3;
//    for (int n = 1; n <= num1; n++){
//        count = 1;
//    for (int i = 2; i <= n; i++) {
//        if (i % p != 0)
//        count = count * i % num1;
//    }
//    cout<<count % num1<<", ";
//    }
//    */
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
//
//int getCnr(int n, int k) {
//    if (k > n/2) k = n - k;
//    if (k == 0) return 1;
//    if (n == 1) return 1;
//    if (k == n) return 1;
//    if (k == 1) return n % MOD;
//    
//    int m27 = factorialMod(n, k, 3, 3);
//    int m11 = factorialMod(n, k, 11, 1);
//    int m13 = factorialMod(n, k, 13, 1);
//    int m37 = factorialMod(n, k, 37, 1);
//    //int m11 = Lucas(n, k, 11);
//    //cout<< m11 << " : " << factorialMod(n, k, 11, 1) << endl;
//    //int m13 = Lucas(n, k, 13);
//    //int m37 = Lucas(n, k, 37);
//    
////    int e27 = (extendedE(27, MOD/27) + MOD)%MOD;
////    int e11 = (extendedE(11, MOD/11) + MOD)%MOD;
////    int e13 = (extendedE(13, MOD/13) + MOD)%MOD;
////    int e37 = (extendedE(37, MOD/37) + MOD)%MOD;
//    int e27 = 137566, e11 = 103896, e13 = 109890, e37 = 77220;
//    
//    int result = (m27*e27%MOD + m11*e11%MOD +m13*e13%MOD + m37*e37%MOD) % MOD;
//    return (result + MOD) % MOD;
//}
//
//int factorialMod(int n, int k, int p, int c) {
//    int q;
//    if (c != 1)
//        q = 27;
//    else
//        q = p;
//    
//    int nMod = getF(n, p, c);
//    int kMod = getF(k, p, c);
//    int nkMod = getF(n - k, p, c);
//    
//    kMod = (kMod * nkMod);
//    
//    int x, y;
//    
//    e_gcd(kMod, q, x, y);
//    
//    x = (x%q + q)*nMod%q;
//    
//    int nP = getE(n, p);
//    int kP = getE(k,p);
//    int nkP = getE(n - k, p);
//    
//    nP = (nP - kP - nkP);
//    if (nP >= c) return 0;
//    
//    for (int i = 0; i < nP; i++)
//        x = x*p%q;
//    
//    return x%q;
//}
//
//void e_gcd(int a, int b, int &x, int &y) {
//    if (b == 0) {
//        x = 1;
//        y = 0;
//        return;
//    }
//    e_gcd(b, a%b, x, y);
//    int temp = x;
//    x = y;
//    y = temp - a/b*y;
//}
//
////int extendedE(int a, int b) {
////    int x, y;
////    e_gcd(a, b, x, y);
////    return y*b;
////}
//
//int getF(int n, int p, int c) {
//    int num;
//    if (c != 1)
//        num = 27;
//    else
//        num = p;
//    
//    if (n <= num) {
//        /*
//        int count = 1;
//        for (int i = 2; i <= n; i++) {
//            int temp = i;
//            while (temp % p == 0) temp /= p;
//            count = count * temp % num;
//        }
//        return count % num;
//         */
//        if (num == 27) return arr27[n - 1];
//        if (num == 11) return arr11[n - 1];
//        if (num == 13) return arr13[n - 1];
//        if (num == 37) return arr37[n - 1];
//    }
//    
//    int q = n / num;
//    
//    int apart = 1;
//    /*
//    for (int i = 2; i < num; i++){
//        int temp = i;
//        if (temp % p != 0)
//            apart = apart * temp % num;
//    }
//    */
//    if (num == 27) apart = 26;
//    if (num == 11) apart = 10;
//    if (num == 13) apart = 12;
//    if (num == 37) apart = 36;
//
//    apart = (q%2 == 0)? 1 : apart;
//    
//    
//    int bpart = getF(n / p, p, c)%num;
//    
//    int cpart = 1;
//    /*
//    for (int i = q*num + 1; i <= n; i++) {
//        if (i % p != 0)
//            cpart = cpart * i % num;
//    }
//    cout<<"cpart: "<<cpart<<endl;
//    */
//    if (n > q*num){
//        if (num == 27) cpart = arrS27[n - q*num - 1];
//        if (num == 11) cpart = arr11[n - q*num - 1];
//        if (num == 13) cpart = arr13[n - q*num - 1];
//        if (num == 37) cpart = arr37[n - q*num - 1];
//        //cout<<"q: "<<q*num+1<<" n: "<< n <<" table: "<<cpart<<endl;
//    }
//    cpart %= num;
//    
//    return (apart*bpart*cpart)%num;
//}
//
//int getPower(int apart, int q, int num){
//    if (q == 0) return 1;
//    return apart;
//    /*
//    int result = 1;
//    for (int i = 0; i < q % num; i++)
//        result = result * apart % num;
//    result %= num;
//    if (q < num) return result;
//    int f = 1;
//    for (int i = 0; i < num; i++)
//        f = f * apart % num;
//    f %= num;
//    result = result * getPower(f, q/num, num) % num;
//    return result;
//    */
//}
//
//int getE(int n, int p) {
//    int result = 0;
//    while (n >= p) {
//        result += n/p;
//        n /= p;
//    }
//    return result;
//}
//
//int Lucas(int n, int k, int p) {
//    vector<int> vn = decomp(n, p), vk = decomp(k, p);
//    
//    for (int i = 0; i < vn.size() - vk.size(); i++)
//        vk.push_back(0);
//    
//    int result = 1;
//    for (int i = 0; i < vn.size(); i++) {
//        int c = sCnr(vn[i], vk[i], p);
//        //cout<<"n: "<<n<<" k: "<<k<<"c: "<<c<<" vn: "<<vn[i] <<" vk: "<<vk[i]<<endl;
//        if (c == 0) return 0;
//        result = result * c % p;
//    }
//    return result;
//}
//
//int sCnr(int n, int r, int p) {
//    if (n < r) return 0;
//    if (r > n/2) r = n - r;
//    if (r == 0) return 1;
//    if (n == 1) return 1;
//    if (r == n) return 1;
//    if (r == 1) return n % p;
// 
//    vector<int> cur(n, 0), prev(n, 0);
//    
//    for (int i = 0; i < n; i++)
//        prev[i] = i + 1;
//    
//    for (int i = 1; i < r; i++) {
//        for (int j = i; j < n; j++) {
//            if (j == i)
//                cur[j] = 1;
//            else
//                cur[j] = (prev[j - 1] + cur[j - 1]) % p;
//        }
//        if (i != r - 1){
//            vector<int> temp;
//            temp = cur;
//            cur = prev;
//            prev = temp;
//        }
//    }
//    
//    return cur[n - 1] % p;
// 
//}
//
//vector<int> decomp(int n, int p){
//    vector<int> v;
//    int num = n;
//    while (num != 0) {
//        //cout<<n<<": "<< p<<": "<<num%p<<endl;
//        v.push_back(num%p);
//        num /= p;
//    }
//    return v;
//}



///* Enter your code here. Read input from STDIN. Print output to STDOUT */
//#include <iostream>
//using namespace std;
//
//#define MOD 142857
//
//int getCnr(int, int);
//
//int factorialMod(int, int, int, int);
//
//int getF(int, int, int);
//
//int getE(int, int);
//
//void e_gcd(int, int, int&, int&);
//
//int arr27[27] = {1, 2, 2, 8, 13, 26, 20, 25, 25, 7, 23, 11, 8, 4, 20, 23, 13, 26, 8, 25, 13, 16, 17, 1, 25, 2, 2};
//int arr11[11] = {1, 2, 6, 2, 10, 5, 2, 5, 1, 10, 10};
//int arr13[13] = {1, 2, 6, 11, 3, 5, 9, 7, 11, 6, 1, 12, 12};
//int arr37[37] = {1, 2, 6, 24, 9, 17, 8, 27, 21, 25, 16, 7, 17, 16, 18, 29, 12, 31, 34, 14, 35, 30, 24, 21, 7, 34, 30, 26, 14, 13, 33, 20, 31, 18, 1, 36, 36};
//
//int arrS27[27] = {1, 2, 2, 8, 13, 13, 10, 26, 26, 17, 25, 25, 1, 14, 14, 8, 1, 1, 19, 2, 2, 17, 13, 13, 1, 26, 26};
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
//
//int getCnr(int n, int k) {
//    if (k > n/2) k = n - k;
//    if (k == 0) return 1;
//    if (n == 1) return 1;
//    if (k == n) return 1;
//    if (k == 1) return n % MOD;
//    
//    int m27 = factorialMod(n, k, 3, 3);
//    int m11 = factorialMod(n, k, 11, 1);
//    int m13 = factorialMod(n, k, 13, 1);
//    int m37 = factorialMod(n, k, 37, 1);
//    
//    int e27 = 137566, e11 = 103896, e13 = 109890, e37 = 77220;
//    
//    int result = (m27*e27%MOD + m11*e11%MOD +m13*e13%MOD + m37*e37%MOD) % MOD;
//    return (result + MOD) % MOD;
//}
//
//int factorialMod(int n, int k, int p, int c) {
//    int q;
//    if (c != 1)
//        q = 27;
//    else
//        q = p;
//    
//    int nMod = getF(n, p, c);
//    int kMod = getF(k, p, c);
//    int nkMod = getF(n - k, p, c);
//    
//    kMod = (kMod * nkMod);
//    
//    int x, y;
//    
//    e_gcd(kMod, q, x, y);
//    
//    x = (x%q + q)*nMod%q;
//    
//    int nP = getE(n, p);
//    int kP = getE(k,p);
//    int nkP = getE(n - k, p);
//    
//    nP = (nP - kP - nkP);
//    if (nP >= c) return 0;
//    
//    for (int i = 0; i < nP; i++)
//        x = x*p%q;
//    
//    return x%q;
//}
//
//void e_gcd(int a, int b, int &x, int &y) {
//    if (b == 0) {
//        x = 1;
//        y = 0;
//        return;
//    }
//    e_gcd(b, a%b, x, y);
//    int temp = x;
//    x = y;
//    y = temp - a/b*y;
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
//        if (num == 27) return arr27[n - 1];
//        if (num == 11) return arr11[n - 1];
//        if (num == 13) return arr13[n - 1];
//        if (num == 37) return arr37[n - 1];
//    }
//    
//    int q = n / num;
//    
//    int apart = 1;
//    if (num == 27) apart = 26;
//    if (num == 11) apart = 10;
//    if (num == 13) apart = 12;
//    if (num == 37) apart = 36;
//    
//    apart = (q%2 == 0)? 1 : apart;
//    
//    
//    int bpart = getF(n / p, p, c)%num;
//    
//    int cpart = 1;
//    
//    if (n > q*num){
//        if (num == 27) cpart = arrS27[n - q*num - 1];
//        if (num == 11) cpart = arr11[n - q*num - 1];
//        if (num == 13) cpart = arr13[n - q*num - 1];
//        if (num == 37) cpart = arr37[n - q*num - 1];
//    }
//    cpart %= num;
//    
//    return (apart*bpart*cpart)%num;
//}
//
//int getE(int n, int p) {
//    int result = 0;
//    while (n >= p) {
//        result += n/p;
//        n /= p;
//    }
//    return result;
//}