#define __test__longestPalindrome__
#ifndef __test__longestPalindrome__

#include <iostream>
#include <string.h>

using namespace std;

string preProcess(string &);
int * palindromeArray(string &);
char getContent(string&, int);
void outputLongestPalindromes(string &, int *, int);
bool isPalindrome(string &s, int * paliarr, int i, int j);

int main() {
    string s = "abaabacaaaaaas";
    string str = preProcess(s);
    int* paliarr = palindromeArray(str);
    outputLongestPalindromes(s, paliarr, (int)str.length());
    cout<<isPalindrome(str, paliarr, 1, 11);
    delete[] paliarr;
    return 0;
}

string preProcess(string & s) {
    int len = (int)s.length();
    if (len == 0) return NULL;
    string str = string(2 * len + 1, '#');
    for (int i = 0; i < len; i++) {
        str[2 * i + 1] = s[i];
    }
    cout << str <<endl;
    return str;
}

int * palindromeArray(string& s) {
    int len = (int)s.length(), c = 0, R = 0, i = 1, i_mirror = -1;
    int* r = new int[len];
    r[0] = 0;
    for (i = 1; i < len; i++) {
        i_mirror = c + c - i;
        if ((i > R) || (i_mirror < 0))
            r[i] = 0;
        else
            r[i] = min(r[i_mirror], R - i);
        
        while (getContent(s, i - r[i] - 1) == getContent(s, i + r[i] + 1))
            r[i]++;
        
        if (i + r[i] > R) {
            c = i;
            R = i + r[i];
        }
    }
    for (int i = 0; i < len; ++i) cout<<r[i]<<" ";
    return r;
}

char getContent(string & s, int i) {
    if (i < 0) 
        return '-';
    if (i >= s.length()) 
        return '+';
    return s[i];
}

void outputLongestPalindromes(string & s, int * r, int n) {
    int len = n, l = 0, pos;
    for (int i = 0; i < len; i++) {
        if (r[i] > l)
            l = r[i];
    }
    cout << l <<endl;
    for (int i = 0; i < len; i++) {
        if (r[i] == l) {
            pos = (i - r[i])/2;
            cout << s.substr(pos, l) << endl;
        }
    }
}
bool isPalindrome(string &s, int *paliarr, int i, int j) {
    int len = (int)s.length();
    if (i < 0 || i >= len || j < 0 || j >= len || i > j)
        return false;
    if (i == j)
        return true;
    int mid = i + (j - i)/2;
    cout<<paliarr[mid]<<endl;
    if (paliarr[mid] >= j/2 - i/2 + 1)
        return true;
    else
        return false;
}
#endif