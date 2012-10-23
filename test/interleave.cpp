//#include <iostream>
//#include <string.h>
//
//using namespace std;
//
//bool isInterleave(string, string, string);
//
//bool interleave(string, int, string, int, string);
//
//
//int main() {
//    string a = "ab";
//    string b = "ac";
//    string c = "acab";
//    cout << isInterleave(a, b, c) << endl;
//    return 0;
//}
//
//bool isInterleave(string a, string b, string c) {
//    if (c.length() != a.length() + b.length())
//        return false;
//    if (a.length() == 0) {
//        if (c.compare(b) == 0)
//            return true;
//        else
//            return false;
//    }
//    if (b.length() == 0) {
//        if (c.compare(a) == 0) 
//            return true;
//        else
//            return false;
//    }
//    return interleave(a, 0, b, 0, c);
//}
//
//bool interleave(string a, int i, string b, int j, string c) {
//    if (i + j == c.length()) {
//        if (i == a.length() && j == b.length())
//            return true;
//        return false;
//    }
//    if (i == a.length()) {
//        while (j != b.length() && (i + j) != c.length()) {
//            if (b[j] != c[i + j])
//                return false;
//            j++;
//        }
//        return true;
//    }
//    if (j == b.length()) {
//        while (i != a.length() && (i + j) != c.length()) {
//            if (a[i] != c[i + j])
//                return false;
//            i++;
//        }
//        return true;
//    }
//    if ((a[i] == c[i + j]) && (b[j] != c[i + j]))
//        return interleave(a, i + 1, b, j, c);
//    if ((b[j] == c[i + j]) && (a[i] != c[i + j]))
//        return interleave(a, i, b, j + 1, c);
//    if ((a[i] == c[i + j]) && (b[j] == c[i + j])) {
//        bool isa = interleave(a, i + 1, b, j, c);
//        bool isb = interleave(a, i, b, j + 1, c);
//        return isa||isb;
//    }
//    return false;
//}