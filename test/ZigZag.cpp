//#include <iostream>
//#include <string.h>
//#include <vector>
//using namespace std;
//
//string getZigZag(string, int);
//
//int main() {
//    string s = "PAYPALISHIRING";
//    //PAHNAPLSIIGYIR
//    int n = 3;
//    cout<< getZigZag(s, n) <<endl;
//    return 0;
//}
//
//string getZigZag(string s, int nRows) {
//    if (s.length() == 0 || nRows == 1)
//        return s;
//        
//    string str = "";
//    int len = s.length();
//    int level[len],count = 0;
//    bool flag = true;
//    for (int i = 0; i < len; i++) {
//        level[i] = count;
//        if (flag)
//            count++;
//        else
//            count--;
//        if ((count == nRows) || (count < 0)) {
//            flag = !flag;
//            if (!flag)
//                count -= 2;
//            else
//                count += 2;
//        }
//    }
//    
//    for (int i = 0; i < nRows; i++) {
//        for (int j = 0; j < len; j++) {
//            if (level[j] == i)
//                str += s[j];
//        }
//    }
//    
//    return str;
//}
