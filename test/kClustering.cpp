#define __test__kClustering__
#ifndef __test__kClustering__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <tr1/unordered_map>
#include <time.h>
#define LEN 24
using namespace std;

struct vertex{
    bitset<LEN> label;
};

struct edge{
    int u, v, weight;
    edge(int uval, int vval, int wval) : u(uval), v(vval), weight(wval) {};
};

class WeightedUF {
    vector<int> id;
    vector<int> sz;
    int count;
public:
    WeightedUF(int N){
        id.resize(N);
        sz.resize(N);
        count = N;
        for (int i = 0; i < N; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getcount() { return count; }
    int find(int i) {
        while (i != id[i]) {
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }
    bool isconnected(int p, int q) { return find(p) == find(q); }
    void putunion(int p, int q) {
        int i = find(p);
        int j = find(q);
        if (i == j)
            return;
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        }
        else {
            id[j] = i;
            sz[i] += sz[j];
        }
        count--;
    }
};

int diff(vertex i, vertex j);
bool edgecomp(edge i, edge j) { return i.weight < j.weight; };
void process();
void process1();

int main() {
    process1();
    process();
    return 0;
}

void process() {
    int num, len;
    fstream fin;
    fin.open("/Users/zishirs/Documents/workspace/test/test/clustering2.txt");
    fin >> num >> len;
    tr1::unordered_map<size_t, int> map;
    vector<vertex> V(num);
    for (int i = 0; i < num; i++) {
        for (int j = len - 1; j >= 0; j--) {
            bool b;
            fin >> b;
            V[i].label[j] = b;
        }
        map.insert(pair<size_t, int>(V[i].label.to_ulong(), i));
    }
    fin.close();
    WeightedUF uf(num);
    for (int i = 0; i < num; i++) {
        //with no diff
        auto it = map.find(V[i].label.to_ulong());
        if (it != map.end()){
            uf.putunion(i, it->second);
        }
        //with 1 diff
        for (int j = len - 1; j >= 0; j--) {
            V[i].label.flip(j);
            it = map.find(V[i].label.to_ulong());
            if (it != map.end()) {
                uf.putunion(i, it->second);
            }
            V[i].label.flip(j);
        }
        //with 2 diff
        for (int j = 0; j < len; j++) {
            for (int k = j + 1; k < len; k++) {
                V[i].label.flip(j);
                V[i].label.flip(k);
                it = map.find(V[i].label.to_ulong());
                if (it != map.end()) {
                    uf.putunion(i, it->second);
                }
                V[i].label.flip(j);
                V[i].label.flip(k);
            }
        }
    }
    cout<<uf.getcount()<<endl;
}

int diff(vertex i, vertex j) {
    int count = 0;
    size_t sz = i.label.size();
    for (int k = 0; k < sz; k++) {
        if (i.label[k] != j.label[k])
            count++;
    }
    return count;
}

void process1(){
    int k = 4;
    vector<edge> E;
    fstream fin;
    fin.open("/Users/zishirs/Documents/workspace/test/test/clustering1.txt");
    int N;
    string s;
    stringstream str;
    getline(fin, s);
    str << s;
    str >> N;
    while (getline(fin, s)) {
        stringstream str;
        str << s;
        int u, v, w;
        str >> u >> v >> w;
        --u;
        --v;
        edge e(u, v, w);
        E.push_back(e);
    }
    fin.close();
    sort(E.begin(), E.end(), edgecomp);
    size_t sz = E.size();
    WeightedUF uf(N);
    int i, w;
    for (i = 0; i < sz; i++) {
        int u = E[i].u, v = E[i].v;
        if (!uf.isconnected(u, v) && uf.getcount() > k)
            uf.putunion(u, v);
        if (uf.getcount() == k)
            break;
    }
    for (int j = i; j < sz; j++) {
        int u = E[j].u, v = E[j].v;
        if (!uf.isconnected(u, v)) {
            w = E[j].weight;
            break;
        }
    }
    cout<<w<<endl;
}
#endif