//#include <iostream>
//#include <tr1/unordered_map>
//
//using namespace std;
//
//#define MOD 142857
//
//long int getCnr(int, int);
//
//void pushMap(int, int, tr1::unordered_map<int, int>&);
//
//void popMap(int, int, tr1::unordered_map<int, int>&);
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
//long int getCnr(int n, int k) {
//    if (k == 0) return 0;
//    if (n == 1) return 1;
//    if (k == n) return 1;
//    if (k == 1) return n % MOD;
//    if (k > n/2) k = n - k;
//    
//    tr1::unordered_map<int, int> map;
//    
//    pushMap(n, k, map);
//    popMap(n, k, map);
//    
//    long int result = 1;
//    tr1::unordered_map<int, int>::iterator it;
//    for (it = map.begin(); it != map.end(); ++it)
//        for (int i = 1; i <= it->second; i++)
//            result = result * (it->first) % MOD;
//    return result;
//}
//
//void pushMap(int n, int k, tr1::unordered_map<int, int>& map) {
//    for (int i = n; i >= n - k + 1; i--) {
//        int num = i, count = 0;
//        for (int j = 2; j <= num; j++) {
//            count = 0;
//            bool flag = false;
//            while (num % j == 0) {
//                flag = true;
//                count++;
//                num /= j;
//            }
//            if (flag) {
//                flag = false;
//                if (map.find(j) == map.end())
//                    map.insert(make_pair(j, count));
//                else
//                    map.find(j)->second += count;
//            }
//        }
//    }
//}
//
//void popMap(int n, int k, tr1::unordered_map<int, int>& map) {
//    for (int i = k; i >= 2; i--) {
//        int num = i, count = 0;
//        for (int j = 2; j <= num; j++) {
//            count = 0;
//            bool flag = false;
//            while (num % j == 0) {
//                flag = true;
//                count++;
//                num /= j;
//            }
//            if (flag) {
//                flag = false;
//                map.find(j)->second -= count;
//            }
//        }
//    }
//}