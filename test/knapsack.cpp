#define __test__knapsack
#ifndef __test__knapsack

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tr1/unordered_map>

using namespace std;

struct item {
    int val, w;
};

bool wcomp(item i, item j);

void process();

int main() {
    process();
    return 0;
}

bool wcomp(item i, item j) {
    return i.w < j.w;
}

void process() {
    fstream fin;
    fin.open("/Users/zishirs/Documents/workspace/test/test/knapsack2.txt");
    int size, N;
    fin >> size >> N;
    vector<item> v(N);
    tr1::unordered_map<size_t, size_t> cur, next;
    for (int i = 0; i < N; ++i) {
        fin >> v[i].val >> v[i].w;
    }
    fin.close();
    /*
    next.insert(pair<size_t, size_t>(0, 0));
    for (int i = 0; i < N; i++) {
        //swap
        tr1::unordered_map<size_t, size_t> temp;
        temp = cur;
        cur = next;
        next = temp;
     
        next.clear();
        tr1::unordered_map<size_t, size_t>::iterator it = cur.begin();
        for (it = cur.begin(); it != cur.end(); ++it)
            next.insert(*it);
        for (it = cur.begin(); it != cur.end(); ++it) {
            size_t weight = v[i].w + it->first, value = v[i].val + it->second;
            if (weight <= size) {
                tr1::unordered_map<size_t, size_t>::iterator jit = next.find(weight);
                if (jit == next.end())
                    next.insert(pair<size_t, size_t>(weight, value));
                else if (jit->second < value)
                    jit->second = value;
            }
        }
    }
    auto iit = next.begin();
    size_t maxval = iit->second;
    
    for (iit = next.begin(); iit != next.end(); ++iit) {
        if (maxval < iit->second)
            maxval = iit->second;
    }
    cout<<maxval<<endl;
    */
    vector<tr1::unordered_map<size_t, size_t> > map(N + 1);
    map[0].insert(pair<size_t, size_t>(0, 0));
    for (int i = 0; i < N; i++) {
        for (auto it = map[i].begin(); it != map[i].end(); ++it)
            map[i + 1].insert(*it);
        for (auto it = map[i].begin(); it != map[i].end(); ++it) {
            size_t weight = v[i].w + it->first, value = v[i].val + it->second;
            if (weight <= size) {
                auto jit = map[i + 1].find(weight);
                if (jit == map[i + 1].end())
                    map[i + 1].insert(pair<size_t, size_t>(weight, value));
                else if (jit->second < value)
                    jit->second = value;
            }
        }
    }
    auto iit = map[N].begin();
    size_t maxval = iit->second;
    
    for (iit = map[N].begin(); iit != map[N].end(); ++iit) {
        if (maxval < iit->second)
            maxval = iit->second;
    }
    cout<<maxval<<endl;
    /*
    vector<vector<size_t> > m(N + 1, vector<size_t>(size + 1, 0));
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= size; j++) {
            if (m[i][j] < m[i - 1][j])
                m[i][j] = m[i - 1][j];
            if (j >= v[i - 1].w && m[i][j] < m[i - 1][j - v[i - 1].w] + v[i - 1].val)
                m[i][j] = m[i - 1][j - v[i - 1].w] + v[i - 1].val;
        }
    }
    cout<<m[N][size]<<endl;
    */
    
    //optimal bst
    int n = 7;
    double p[8] = {0, 0.2, 0.05, 0.17, 0.1, 0.2, 0.03, 0.25};
    
    vector<vector<double> > matrix(n + 1, vector<double>(n + 1, 0));
    for (int s = 0; s < n; s++) {
        for (int i = 1; i <= n; i++) {
            if (i + s <= n)
            matrix[i][i + s] = INT_MAX;
            double pval = 0.0;
            for (int k = i; k <= i + s; k++)
                if (k <= n)
                    pval += p[k];
                
            for (int r = i; r <= i + s; r++) {
                double val = pval;
                if (r - 1 <= n)
                    val += matrix[i][r - 1];
                if (r + 1 <= n && i + s <= n)
                    val += matrix[r + 1][i + s];
                if (matrix[i][i + s] > val)
                    matrix[i][i + s] = val;
            }
        }
    }
    
    for (int i = n; i >= 0; i--) {
        for (int j = n; j >= 0; j--) {
            cout<<matrix[i][j]<<"    ";
        }
        cout<<endl;
    }
    item * pi = NULL;
    item ** ptrRef = & pi;
    cout<< ((*ptrRef) == NULL) <<endl;
}

#endif