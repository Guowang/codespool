//#include <iostream>
//#include <string.h>
//
//using namespace std;
//
//bool isPalindrome(string);
//
//bool isValid(char);
//
//bool isEqual(char, char);
//
//int main() {
//    string s = " ni Hao! 32hi, ?? ih 23 oa! h ?i ~n ";
//    cout << boolalpha << isPalindrome(s) <<endl;
//    return 0;
//}
//
//bool isValid(char c) {
//    if (isalpha(c) || isnumber(c))
//        return true;
//    return false;
//}
//
//bool isEqual(char c1, char c2) {
//    if (c1 == c2)
//        return true;
//    if (isalpha(c1) && isalpha(c2)) 
//        return toupper(c1) == toupper(c2);
//    return false;
//}
//
//bool isPalindrome(string str) {
//    if (str.length() == 0)
//        return true;
//    
//    int i = 0, j = str.length() - 1;
//    
//    while (i < j) {
//        while (i < j && !isValid(str[i])) i++;
//        while (i < j && !isValid(str[j])) j--;
//        if (!isEqual(str[i], str[j]))
//            return false;
//        i++;
//        j--;
//    }
//    
//    return isValid(str[i]);
//}