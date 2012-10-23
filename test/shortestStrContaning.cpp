//#include <iostream>
//#include <vector>
//#include <string.h>
//#include <assert.h>
//
//using namespace std;
//
//string findShortestContainingStr(string, string);
//
//bool isSame(int*, int, int*, int, vector<int>);
//
//bool isContain(int, vector<int>);
//
//int main() {
//    
//    string s1 = "this is a test string", s2 = "tist";
//    string s = findShortestContainingStr(s1, s2);
//    
//    if (!s.empty())
//        cout<< "The result is: " << s <<endl;
//    
//    return 0;
//}
//
//bool isSame(int* arrS1, int lenS1, int* arrS2, int lenS2, vector<int> charArr){
//    if (lenS1 <= 0 || lenS2 <=0 || lenS1 != lenS2)
//        return false;
//    for (vector<int>::iterator it = charArr.begin(); it != charArr.end(); it++)
//        if (arrS1[*it] < arrS2[*it])
//            return false;
//    return true;
//}
//
//bool isContain(int i, vector<int> charArr){
//    for (vector<int>::iterator it = charArr.begin(); it != charArr.end(); it++)
//        if (i == *it)
//            return true;
//    return false;
//}
//
//string findShortestContainingStr(string s1, string s2){
//    
//    string result = "";
//    
//    if (s1.empty() || s2.empty() || s1.length() < s2.length())
//        return result;
//    
//    int start = 0, end = 0, minlen = s1.length() + 1, i, j;
//    int* arrS1 = new int[26];
//    int* arrS2 = new int[26];
//    vector<int> charArr;
//    
//    for (int i = 0; i < s2.length(); i++) {
//        int s2i = s2[i] - 'a';
//        if (!isContain(s2i, charArr))
//            charArr.push_back(s2i);
//        arrS2[s2i]++;
//    }
//        
//    //initiate start position
//    while (start < s1.length()) {
//        int s1start = s1[start] - 'a';
//        if (isContain(s1start, charArr)) {
//            arrS1[s1start]++;
//            break;
//        }
//        start++;
//    }
//    
//    if (start == s1.length())   return result;
//    else if (s2.length() == 1)  return s2;
//    else                        end = start;
//    
//    while (start < s1.length() && end < s1.length()) {
//        //move end pointer to fulfill req.
//        while (!isSame(arrS1, 26, arrS2, 26, charArr) && (end < s1.length())) {
//            end++;
//            int s1end = s1[end] - 'a';
//            if (isContain(s1end, charArr))
//                arrS1[s1end]++;
//        }
//        
//        if (end == s1.length()) break;
//        
//        //move start until break the equality, and at the same time check whether encounter shorter substring
//        while (isSame(arrS1, 26, arrS2, 26, charArr) && start <= end) {
//            
//            if (end - start + 1 < minlen) {
//                i = start;
//                j = end;
//                minlen = end - start + 1;
//            }
//            
//            int s1start = s1[start] - 'a';
//            arrS1[s1start]--;
//            
//            while (start <= end) {
//                start++;
//                s1start = s1[start] - 'a';
//                if (isContain(s1start, charArr))
//                    break;
//            }
//            
//        }
//    }
//    
//    if (minlen < s1.length() + 1)
//        result = s1.substr(i, j - i + 1);
//    return result;
//}