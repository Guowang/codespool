/*
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

void process(string&, string&);

int main() {
    int T;
    cin >> T;
    for (int count = 0; count < T; count++) {
        string t, p, dump;
        cin >> t;
        cin >> p;
        getline(cin, dump);
        getline(cin, dump);
        process(t, p);
        
    }
    return 0;
}

void process(string& text, string& pat) {
    string prefix, suffix;
    prefix = pat + text;
    suffix = text + pat;
    
    int n = pat.length() + text.length();
    vector<int> p(n, 0), s(n, 0);
    
    int r = 0, l = 0;
    
    for (int i = 1; i < n; i++) {
        p[i] = (i > r) ? 0 : min(p[i - l], r - i);
        
        while (i + p[i] < n && prefix[p[i]] == prefix[i + p[i]])
            p[i]++;
        
        if (i + p[i] > r) {
            r = i + p[i];
            l = i;
        }
    }
    
    r = n - 1, l = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        s[i] = (i < l) ? 0 : min(s[n - 1 - r + i], i - l);
        
        while (i - s[i] >=0 && suffix[i - s[i]] == suffix[n - 1 - s[i]])
            s[i]++;
        
        if (i - s[i] < l) {
            l = i - s[i];
            r = i;
        }
    }
    
    int patlen = pat.length();
    for (int i = 0; i <= text.length() - pat.length(); i++) {
        int pref = p[i + patlen], suf = s[i + patlen - 1];
        if (pref + suf >= patlen - 1)
            cout<<i<<" ";
    }
    cout<<endl;
}
*/