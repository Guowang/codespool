/*
#include <iostream>
#include <inttypes.h>
#include <vector>
#include <stack>
#include <tr1/unordered_set>
#include <tr1/unordered_map>

using namespace std;

#define MOD 1000000007

void process();

tr1::unordered_set<string> getUniqueStrings(tr1::unordered_set<string>&);

bool isDecomp(string, tr1::unordered_set<string>&, bool);

int main() {
    process();
    return 0;
}

void process() {
    int N, M;
    cin>>N>>M;
    if (M == 0) {
        cout<<1<<endl;
        return;
    }
    vector<uint64_t> results(M + 1, 0), superstrings(M + 1, 0), duplicates(M + 1, 0), margin(M + 1, 0);
    results[0] = 1;
    tr1::unordered_set<string> input;
    for (int i = 0; i < N; i++) {
        string str;
        cin>>str;
        if (str.length() <= M)
            input.insert(str);
    }
    tr1::unordered_set<string> set = getUniqueStrings(input);
    tr1::unordered_set<string>::iterator iit, jit, kit;
    
    vector<tr1::unordered_set<string> > map(10);
    vector<tr1::unordered_set<string> > table(10);
    
    for (iit = set.begin(); iit != set.end(); ++iit) {
        superstrings[iit->length()]++;
        int i = (*iit)[0] - 'a';
        table[i].insert(*iit);
    }
    
    tr1::unordered_map<string, tr1::unordered_set<string> > dmap;
    tr1::unordered_map<string, tr1::unordered_set<string> >::iterator dit;
    for (int m = 0; m < 10; m++) {
        for (iit = table[m].begin(); iit != table[m].end(); ++iit) {
            for (jit = table[m].begin(); jit != table[m].end(); ++jit) {
                if (iit->length() < jit->length() && (iit->compare(jit->substr(0, iit->length())) == 0)) {
                    //cout<<"i: "<<*iit<<" j: "<<*jit<<endl;
                    stack<string> vi, vj;
                    vi.push(*iit);
                    vj.push(*jit);
                    while (!vi.empty() && !vj.empty()) {
                        string si = vi.top(), sj = vj.top(), t;
                        vi.pop();
                        vj.pop();
                        if (si.length() > sj.length()) {
                            t = si;
                            si = sj;
                            sj = t;
                        }
                        int k = sj[si.length()] - 'a';
                        for (kit = table[k].begin(); kit != table[k].end(); ++kit) {
                            string tsik = si + *kit, tsj = sj;
                            if (tsik.compare(tsj) == 0) {
                                //cout<<*iit<<" : "<<*jit<<" : "<<tsj<<endl;
                                if (dmap.find(tsj) == dmap.end()) {
                                    tr1::unordered_set<string> ts;
                                    ts.insert(*iit);
                                    ts.insert(*jit);
                                    dmap.insert(make_pair(tsj, ts));
                                }
                                else {
                                    dmap.find(tsj)->second.insert(*iit);
                                    dmap.find(tsj)->second.insert(*jit);
                                }
                            }
                            if (tsik.length() > tsj.length()) {
                                t = tsik;
                                tsik = tsj;
                                tsj = t;
                            }
                            if (tsik.compare(tsj.substr(0, tsik.length())) == 0 && tsik.length() != tsj.length() && tsj.length() <= M) {
                                vi.push(tsik);
                                vj.push(tsj);
                            }
                        }
                    }
                }
            }
        }
    }
    
    tr1::unordered_set<string> uniquedups;
    for (dit = dmap.begin(); dit != dmap.end(); ++dit) {
        int m = dit->first.length();
        bool flag = true;
        
        for (int i = 1; i < m; i++) {
            string sub = dit->first.substr(0, i), res = dit->first.substr(i, m - i);
            if (dmap.find(sub) != dmap.end() && isDecomp(res, set, false)) {
                flag = false;
                break;
            }
        }
        
        if (flag) {
            uniquedups.insert(dit->first);
            int size = dit->second.size();
            duplicates[m] += size - 1;
            //cout<<"d[m]: "<<m<<" : "<<duplicates[m]<<endl;
        }
    }
    
    for (dit = dmap.begin(); dit != dmap.end(); ++dit) {
        if (uniquedups.find(dit->first) == uniquedups.end()) {
            int found = 0;
            int m = dit->first.length();
            for (int i = 1; i < m; i++) {
                string sub = dit->first.substr(0, i), res = dit->first.substr(i, m - i);
                if (uniquedups.find(sub) != uniquedups.end() && isDecomp(res, set, false)) {
                    found++;
                    if (found > 1) {
                        margin[m]++;
                    }
                }
            }
        }
    }
    results[0] = 1;
    results[1] = superstrings[1];
    
    if (M > 1) {
        for (int i = 2; i <= M; i++) {
            for (int j = 1; j < i; j++)
                results[i] = (results[i] + superstrings[j] * results[i - j]) % MOD;
            results[i] = (results[i] + superstrings[i] + margin[i]) % MOD;
            for (int k = 3; k <= M; k++) {
                if (duplicates[k] != 0 && i >= k) {
                    //cout<<i<<" r[i]: "<<results[i]<<" d[k]: "<<duplicates[k]<<" r[i-k]: "<<results[i-k]<<endl;
                    results[i] = (results[i] - duplicates[k] * results[i - k]) % MOD;
                }
            }
        }
    }
    
    uint64_t total = 0;
    for (int i = 0; i <= M; i++){
        //cout<<i<<" : "<<results[i]<<endl;
        total = (total + results[i]) % MOD;
    }
    cout<<total<<endl;
    
    return;
}

tr1::unordered_set<string> getUniqueStrings(tr1::unordered_set<string>& input) {
    tr1::unordered_set<string> set;
    tr1::unordered_set<string>::iterator it;
    for (it = input.begin(); it != input.end(); ++it) {
        if (it->length() == 1)
            set.insert(*it);
        else if (!isDecomp(*it, input, true))
            set.insert(*it);
    }
    return set;
}

bool isDecomp(string s, tr1::unordered_set<string>& input, bool flag) {
    if(flag) {
        int len = s.length();
        if (len == 1) {
            if (input.find(s) != input.end()) return true;
            return false;
        }
        for (int i = 1; i < len; i++) {
            if (input.find(s.substr(0, i)) != input.end() && isDecomp(s.substr(i, len - i), input, false))
                return true;
        }
        return false;
    }
    else {
        if (input.find(s) != input.end()) return true;
        int len = s.length();
        if (len == 1) return false;
        
        for (int i = 1; i < len; i++) {
            if (input.find(s.substr(0, i)) != input.end() && isDecomp(s.substr(i, len - i), input, false))
                return true;
        }
        return false;
    }
}
*/



/*
#include <iostream>
#include <inttypes.h>
#include <vector>
#include <tr1/unordered_set>

using namespace std;

#define MOD 1000000007

void process();

tr1::unordered_set<string> getUniqueStrings(tr1::unordered_set<string>&);

bool isDecomp(string, tr1::unordered_set<string>&);

int main() {
    process();
    return 0;
}

void process() {
    int N, M;
    cin>>N>>M;
    if (M == 0) {
        cout<<1<<endl;
        return;
    }
    vector<uint64_t> results(M + 1, 0);
    results[0] = 1;
    tr1::unordered_set<string> input;
    for (int i = 0; i < N; i++) {
        string str;
        cin>>str;
        if (str.length() <= M)
            input.insert(str);
    }
    tr1::unordered_set<string> set = getUniqueStrings(input);
    tr1::unordered_set<string>::iterator it;
    vector<tr1::unordered_set<string> > cols(10, tr1::unordered_set<string>());
    vector<vector<tr1::unordered_set<string> > > rows(10, cols);
    vector<vector<vector<tr1::unordered_set<string> > > > table(M + 1, rows);
    vector<uint64_t> superstrings(M + 1);
    vector<vector<string> > ss(M + 1);
    for (it = set.begin(); it != set.end(); ++it) {
        superstrings[it->length()]++;
        int i = (*it)[0] - 'a', j = (*it)[it->length() - 1] - 'a';
        table[it->length()][i][j].insert(*it);
        ss[it->length()].push_back(*it);
    }
    
    results[1] = superstrings[1];
    
    if (M > 1) {
        for (int m = 2; m <= M; m++) {
            for (int k = 1; k < m; k++) {
                vector<string>::iterator iit;
                tr1::unordered_set<string>::iterator jit;
                for (iit = ss[k].begin(); iit != ss[k].end(); ++iit) {
                    for (int i = 0; i < 10; i++) {
                        for (int j = 0; j < 10; j++) {
                            for (jit = table[m - k][i][j].begin(); jit != table[m - k][i][j].end(); ++jit) {
                                string str = *iit + *jit;
                                int i1 = str[0] - 'a';
                                if (table[m][i1][j].find(str) == table[m][i1][j].end()) {
                                    table[m][i1][j].insert(str);
                                    results[m] = (results[m] + 1) % MOD;
                                }
                            }
                        }
                    }
                }
            }
            results[m] = (results[m] + superstrings[m]) % MOD;
        }
    }
    
    uint64_t total = 0;
    for (int i = 0; i <= M; i++){
        cout<<i<<" : "<<results[i]<<endl;
        total = (total + results[i]) % MOD;
    }
    cout<<total<<endl;
    
    return;
}

tr1::unordered_set<string> getUniqueStrings(tr1::unordered_set<string>& input) {
    tr1::unordered_set<string> set;
    tr1::unordered_set<string>::iterator it;
    for (it = input.begin(); it != input.end(); ++it) {
        if (it->length() == 1)
            set.insert(*it);
        else if (!isDecomp(*it, input))
            set.insert(*it);
    }
    return set;
}

bool isDecomp(string s, tr1::unordered_set<string>& input) {
    if (s.length() == 1) {
        if (input.find(s) == input.end()) return false;
        return true;
    }
    for (int i = 1; i < s.length(); i++) {
        if (isDecomp(s.substr(0,i), input) && isDecomp(s.substr(i,s.length() - i), input))
            return true;
    }
    return false;
}
*/