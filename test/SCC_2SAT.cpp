#define __test__SCC_2SAT__
#ifndef __test__SCC_2SAT__


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <tr1/unordered_set>

using namespace std;

size_t c;
vector<vector<size_t> > V;
vector<size_t> N, L;
stack<size_t> S;
vector<bool> visited, inStack;

inline size_t getN(size_t i) {return (i % 2 == 0) ? i + 1 : i - 1;};
void Tarjan_SCC(size_t index);

int main() {
    fstream fin("/Users/zishirs/Documents/workspace/test/test/2sat6.txt");
    int n;
    fin >> n;
    n *= 2;
    V.resize(n, vector<size_t>());
    N.resize(n, INT_MAX);
    L.resize(n, INT_MAX);
    visited.resize(n, false);
    inStack.resize(n, false);
    c = 0;
    int u, v;
    while (fin.good()) {
        fin >> u >> v;
        if (!fin.good())
            break;
        if (u < 0)
            u = 2*abs(u) - 1;
        else
            u = 2*abs(u) - 2;
        if (v < 0)
            v = 2*abs(v) - 1;
        else
            v = 2*abs(v) - 2;
        V[u].push_back(getN(v));
        V[v].push_back(getN(u));
    }
    
    for (size_t i = 0; i < V.size(); ++i) {
        if (!visited[i])
            Tarjan_SCC(i);
    }
    
    cout<<"1"<<endl;
    return 0;
}

void Tarjan_SCC(size_t index) {
    if (visited[index])
        return;
    visited[index] = true;
    N[index] = c;
    L[index] = c;
    c++;
    S.push(index);
    inStack[index] = true;
    
    for (size_t i = 0; i < V[index].size(); ++i) {
        size_t j = V[index][i];
        if (!visited[j]) {
            Tarjan_SCC(j);
            L[index] = min(L[index], L[j]);
        }
        else if (inStack[j])
            L[index] = min(L[index], N[j]);
    }
    
    if (N[index] == L[index]) {
        tr1::unordered_set<size_t> set;
        while (S.top() != index) {
            set.insert(S.top());
            if (set.find(getN(S.top())) != set.end()) {
                cout<<"0"<<endl;
                exit(1);
            }
            inStack[S.top()] = false;
            S.pop();
        }
        inStack[index] = false;
        S.pop();
        set.insert(index);
        if (set.find(getN(index)) != set.end()) {
            cout<<"0"<<endl;
            exit(1);
        }
    }
}
#endif /* defined(__test__SCC_2SAT__) */
