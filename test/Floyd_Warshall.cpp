#define __test__BellmanFord__
#ifndef __test__BellmanFord__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tr1/unordered_map>

using namespace std;

void APSP();

int main() {
    APSP();
    return 0;
}

void APSP(){
    fstream fin("/Users/zishirs/Documents/workspace/test/test/large.txt");
    size_t n, m, s, e;
    int w;
    fin >> n >> m;
    vector<vector<int> > E(n + 1, vector<int>(n + 1, INT_MAX));
    for (size_t i = 0; i < m; ++i) {
        fin >> s >> e >> w;
        E[s][e] = w;
    }
    for (size_t i = 1; i <= n; ++i) {
        E[i][i] = 0;
    }
    cout<<"input\n";
    vector<vector<int> > cur(n + 1, vector<int>(n + 1, INT_MAX)), prev(n + 1, vector<int>(n + 1, INT_MAX));
    
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            if (E[i][j] != INT_MAX)
                prev[i][j] = E[i][j];
        }
    }
    cout<<"init\n";
    for (size_t k = 1; k <= n; ++k) {
        for (size_t i = 1; i <= n; ++i) {
            for (size_t j = 1; j <= n; ++j) {
                cur[i][j] = max(prev[i][j], prev[i][k] + prev[k][j]);
            }
        }
        if (k != n)
            cur.swap(prev);
    }
    cout<<"calc\n";
    for (size_t i = 1; i <= n; ++i) {
        if (cur[i][i] < 0) {
            cout<<"negative loop"<<endl;
            return;
        }
    }
    cout<<"-loop?";
    int minlen = INT_MAX;
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            cout.width(4);
            cout<<cur[i][j];
            if (i != j && minlen > cur[i][j])
                minlen = cur[i][j];
        }
        cout<<endl;
    }
    cout<<minlen<<endl;
}
#endif /* defined(__test__BellmanFord__) */
