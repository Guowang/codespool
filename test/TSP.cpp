#define __test__TSP__
#ifndef __test__TSP__


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tr1/unordered_map>
#include <cmath>
#include <time.h>

#define N 25
#define MAP tr1::unordered_map<size_t, double>
using namespace std;

int main() {
    fstream fin("/Users/zishirs/Documents/workspace/test/test/test.txt");
    int n;
    fin >> n;
    vector<double> x(n, 0.0), y(n, 0.0);
    for (size_t i = 0; i < n; ++i)
        fin >> x[i] >> y[i];
    vector<vector<double> > dist(N, vector<double>(N, 0.0));
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            dist[i][j] = sqrt((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]));
        }
    }
    
    cout<<"Start: \n";
    clock_t t = clock();
    double ret = INT_MAX;
    vector<MAP> cur(N, MAP()), next(N, MAP());
    MAP::iterator it, jt;
    //base cases
    for (size_t j = 1; j < N; ++j) {
        size_t num = 1;
        num |= 1<<j;
        cur[j].insert(pair<size_t, double>(num, dist[0][j]));
    }
    clock_t t1 = clock();
    //dp
    for (size_t m = 3; m <= N; ++m) {
        t1 = clock() - t1;
        cout<<m<<": "<<(float) t1 / CLOCKS_PER_SEC<<endl;
        t1 = clock();
        for (size_t j = 1; j < N; ++j) {
            for (it = cur[j].begin(); it != cur[j].end(); ++it) {
                size_t num = it->first;
                for (size_t k = 1; k < N; ++k) {
                    if ((num & (1<<k)) == 0) {
                        size_t knum = num | (1<<k);
                        jt = next[k].find(knum);
                        if (jt == next[k].end())
                            next[k].insert(pair<size_t, double>(knum, it->second + dist[k][j]));
                        else
                            jt->second = min(jt->second, it->second + dist[k][j]);
                    }
                }
            }
        }
        cur.swap(next);
        for (size_t j = 0; j < N; ++j) {
            next[j].clear();
        }
    }
    //final results
    for (size_t j = 1; j < N; ++j) {
        //should be 1
        //cout<<j<<": "<<cur[j].size()<<endl;
        for (it = cur[j].begin(); it != cur[j].end(); ++it) {
            ret = min(ret, it->second + dist[0][j]);
        }
    }
    cout<<ret<<endl;
    t = clock() - t;
    cout<<"Total: "<<(float) t / CLOCKS_PER_SEC <<" seconds."<<endl;
    return 0;
}

#endif /* defined(__test__TSP__) */
