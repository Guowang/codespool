#define __test__kmp__
#ifndef __test__kmp__
#include <iostream>
#include <string.h>

using namespace std;

int kmpSearch(string &, string &, int);

int* kmpTable (string &);

int main ()
{
    string s = "ababababababababababababcabcbb";
    string p = "ababac+";
    //string p = "babababcab";
    int start = 0;
    cout << kmpSearch(s, p, start) << endl;
    return 0;
}

int kmpSearch(string & str,string & words, int start)
{
    
    if (str.size() - words.size() < start) {
        return -1;
    }
    else {
        int m = start;
        int i = 0;
        
        int * T;
        T = kmpTable(words);
        
        while ((m + i) < str.size()) {
            if (str[m + i] == words[i]) {
                if (i == words.size() - 1) {
                    delete[] T;
                    return m;
                }
                i++;
            }
            else {
                m = m + i - T[i];
                if (T[i] > -1)
                    i = T[i];
                else
                    i = 0;
            }
        }
        
        delete[] T;
        return -1;
    }
}

int* kmpTable (string & words)
{
    int size = (int) words.size();
    int* T = new int[size];

    if (size == 1) {
        T[0] = -1;
        return T;
    }
    else {
        T[0] = -1;
        T[1] = 0;
        int pos, cnd;
        pos = 2;
        cnd = 0;
        while (pos < size) {
            if (words[pos - 1] == words[cnd])
                T[pos++] = ++cnd;
            else {
                if (cnd > 0)
                    cnd = T[cnd];
                else
                    T[pos++] = 0;
            }
            
        }
        
        for (int i = 0; i < size; i++) cout<<T[i]<<" ";
        cout<<endl;
        
        return T;
    }
}

void MismatchTable(const char *pat, vector<int> &v) {
    v.clear();
    if (pat[0] == '\0')
        return;
    v.push_back(-1);
    if (pat[1] == '\0')
        return;
    v.push_back(0);
    if (pat[2] == '\0')
        return;
    int i = 2, cnd = 0;
    while (pat[i] != '\0') {
        if (pat[i - 1] == pat[cnd]) {
            ++i;
            ++cnd;
            v.push_back(cnd);
        }
        else if (cnd > 0)
            cnd = v[cnd];
        else {
            v.push_back(0);
            ++i;
        }
    }
}
char *strStr(char *haystack, char *needle) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<int> v;
    MismatchTable(needle, v);
    int i = 0, j = 0;
    while (haystack[i] != '\0' && needle[j] != '\0') {
        if (haystack[i + j] == needle[j])
            ++j;
        else {
            i = i + j - v[j];
            j = (v[j] != -1) ? v[j] : 0;
        }
    }
    if (needle[j] == '\0')
        return haystack + i;
    return NULL;
}

#endif