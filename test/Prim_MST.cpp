#define __test__Prim_MST__
#ifndef __test__Prim_MST__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <tr1/unordered_map>
#include <tr1/unordered_set>

using namespace std;

vector<int> dist;

class vertex {
public:
    int id;
    tr1::unordered_set<int> adj;
    vertex() {
        id = -1;
        adj.clear();
    };
    vertex(const vertex& vv){
        id = vv.id;
        adj.clear();
        for (tr1::unordered_set<int>::const_iterator iit = vv.adj.begin(); iit != vv.adj.end(); ++iit)
            adj.insert(*iit);
    };
    vertex& operator=(const vertex& vv) {
        id = vv.id;
        adj.clear();
        for (tr1::unordered_set<int>::const_iterator iit = vv.adj.begin(); iit != vv.adj.end(); ++iit)
            adj.insert(*iit);
        return *this;
    }
    int compareTo(const vertex& v) {
        if (dist[id] < dist[v.id])
            return -1;
        if (dist[id] > dist[v.id])
            return 1;
        return 0;
    }
};

template <typename Key>
class IndexMinPQ {
    int NMAX;
    int N;
    vector<int> pq;
    vector<int> qp;
    vector<Key> keys;
    IndexMinPQ(const IndexMinPQ& obj){};
    IndexMinPQ& operator=(const IndexMinPQ& obj){};
public:
    IndexMinPQ(int NMAXval) {
        if (NMAX < 0) return;
        this->NMAX = NMAXval;
        keys.resize(NMAXval + 1);
        pq.resize(NMAXval + 1);
        qp.resize(NMAXval + 1);
        for (int i = 0; i <= NMAX; i++)
            qp[i] = -1;
    }
    bool isEmpty() { return N == 0; }
    bool contains(int i) {
        if (i < 0 || i >= NMAX) return false;
        return qp[i] != -1;
    }
    int size() { return N; }
    bool greater(int i, int j) { return keys[pq[i]].compareTo(keys[pq[j]]) > 0; }
    void exch(int i, int j) {
        int swap = pq[i];
        pq[i] = pq[j];
        pq[j] = swap;
        qp[pq[i]] = i;
        qp[pq[j]] = j;
    }
    void swim(int k) {
        while (k > 1 && greater(k/2, k)) {
            exch(k, k/2);
            k = k/2;
        }
    }
    void sink(int k) {
        while (2*k <= N) {
            int j = 2*k;
            if (j < N && greater(j, j + 1))
                j++;
            if (!greater(k, j))
                break;
            exch(k, j);
            k = j;
        }
    }
    void insert(int i, Key keyval) {
        if (i < 0 || i >= NMAX)
            return;
        if (contains(i)){
            return;
        }
        N++;
        qp[i] = N;
        pq[N] = i;
        keys[i] = keyval;
        swim(N);
    }
    int minIndex() {
        if (N == 0) return -1;
        return pq[1];
    }
    Key minKey() {
        return keys[pq[1]];
    }
    int delMin() {
        if (N == 0) {
            return -1;
        }
        int min = pq[1];
        exch(1, N--);
        sink(1);
        qp[min] = -1;
        pq[N+1] = -1;
        return min;
    }
    Key keyof(int i) {
        if (i < 0 || i >= NMAX || !contains(i))
            return NULL;
        return keys[i];
    }
    void changekey(int i, Key keyval) {
        if (i < 0 || i >= NMAX || !contains(i))
            return;
        keys[i] = keyval;
        swim(qp[i]);
        sink(qp[i]);
    }
    void decreasekey(int i, Key keyval) {
        if (i < 0 || i >= NMAX || !contains(i))
            return;
        if (keys[i].compareTo(keyval) < 0)
            return;
        keys[i] = keyval;
        swim(qp[i]);
    }
    void increasekey(int i, Key keyval) {
        if (i < 0 || i >= NMAX || !contains(i))
            return;
        if (keys[i].compareTo(keyval) > 0)
            return;
        keys[i] = keyval;
        sink(qp[i]);
    }
    void deletekey(int i) {
        if (i < 0 || i >= NMAX || !contains(i))
            return;
        int index = qp[i];
        exch(index, N);
        N--;
        swim(index);
        sink(index);
        qp[i] = -1;
    }
};

struct edge {
    int i, j, w;
};

class edgecomp{
    bool reverse;
public:
    edgecomp(const bool & flag = false) {reverse = flag;};
    bool operator()(edge ei, edge ej){
        if (reverse)
            return ei.w > ej.w;
        else
            return ei.w < ej.w;
    };
};

struct job {
    double w, len;
};

inline string toS(int i) {ostringstream conv; conv << i; return conv.str();};
bool diffcomp(job i, job j) {
    if ((i.w - i.len) > (j.w - j.len))
        return true;
    if ((i.w - i.len) < (j.w - j.len))
        return false;
    return i.w > j.w;
}
bool divcomp(job i, job j) { return (i.w / i.len) > (j.w / j.len);}

void process();
void heapprocess();
void bfprocess();
void jobprocess();

int main() {
    process();
    heapprocess();
    bfprocess();
    jobprocess();
    return 0;
}


void process() {
    int N, M;
    vector<vertex> V;
    tr1::unordered_map<string, int> E;
    vector<bool> inset;
    fstream fin;
    fin.open("/Users/zishirs/Documents/workspace/test/test/edges.txt");
    if (fin.good()) {
        fin >> N >> M;
        V.resize(N);
        dist.resize(N);
        inset.resize(N);
        for (int i = 0; i < N; i++) {
            V[i].id = i;
            dist[i] = INT_MAX;
            inset[i] = false;
        }
        for (int i = 0; i < M; i++) {
            int ii, jj, weight;
            fin >> ii >> jj >> weight;
            ii--;
            jj--;
            V[ii].adj.insert(jj);
            V[jj].adj.insert(ii);
            E.insert(pair<string, int>(toS(ii) + "+" + toS(jj), weight));
            E.insert(pair<string, int>(toS(jj) + "+" + toS(ii), weight));
        }
    }
    fin.close();
    //initialization
    inset[0] = true;
    IndexMinPQ<vertex> minpq(N);
    for (int i = 1; i < N; i++) {
        if (V[i].adj.find(0) != V[i].adj.end()) {
            int w = E.find(toS(0) + "+" + toS(i))->second;
            if (dist[i] > w) {
                dist[i] = w;
            }
        }
        minpq.insert(i, V[i]);
    }
    int sum = 0;
    while (!minpq.isEmpty()) {
        int min = minpq.delMin();
        sum += dist[min];
        //cout<<min<<" : "<<dist[min]<<endl;
        inset[min] = true;
        for (auto it = V[min].adj.begin(); it != V[min].adj.end(); ++it) {
            int j = *it;
            int w = E.find(toS(min) + "+" + toS(j))->second;
            if (!inset[j] && w < dist[j]) {
                dist[j] = w;
                minpq.decreasekey(j, V[j]);
            }
        }
    }
    cout<<sum<<endl;
}

void heapprocess() {
    int N, M;
    vector<edge> E;
    vector<bool> inset;
    fstream fin;
    fin.open("/Users/zishirs/Documents/workspace/test/test/edges.txt");
    if (fin.good()) {
        fin >> N >> M;
        inset.resize(N);
        E.resize(M);
        for (int i = 0; i < N; i++) {
            inset[i] = false;
            dist[i] = INT_MAX;
        }
        for (int i = 0; i < M; i++) {
            int ii, jj, weight;
            fin >> ii >> jj >> weight;
            ii--;
            jj--;
            E[i].i = ii;
            E[i].j = jj;
            E[i].w = weight;
        }
    }
    fin.close();
    //initialization
    inset[0] = true;
    int count = 1, sum = 0;
    typedef priority_queue<edge, vector<edge>, edgecomp> mintype;
    mintype pq(edgecomp(true));
    for (int i = 0; i < M; i++)
        pq.push(E[i]);
    bool flag;
    vector<edge> collect;
    while (count < N) {
        edge e = pq.top();
        pq.pop();
        flag = false;
        if ((inset[e.i] && !inset[e.j])) {
            inset[e.j] = true;
            sum += e.w;
            count++;
            flag = true;
        }
        else if (!inset[e.i] && inset[e.j]) {
            inset[e.i] = true;
            sum += e.w;
            count++;
            flag = true;
        }
        else if (!inset[e.i] && !inset[e.j])
            collect.push_back(e);
        if (flag) {
            for (vector<edge>::iterator it = collect.begin(); it != collect.end(); ++it)
                pq.push(*it);
            collect.clear();
        }
    }
    cout<<sum<<endl;
}

void bfprocess() {
    int N, M;
    vector<edge> E;
    vector<bool> inset;
    fstream fin;
    fin.open("/Users/zishirs/Documents/workspace/test/test/edges.txt");
    if (fin.good()) {
        fin >> N >> M;
        inset.resize(N);
        E.resize(M);
        for (int i = 0; i < N; i++) {
            inset[i] = false;
            dist[i] = INT_MAX;
        }
        for (int i = 0; i < M; i++) {
            int ii, jj, weight;
            fin >> ii >> jj >> weight;
            ii--;
            jj--;
            E[i].i = ii;
            E[i].j = jj;
            E[i].w = weight;
        }
    }
    fin.close();
    //initialization
    inset[0] = true;
    int count = 0, sum = 0;
    while (count < N) {
        int minedge = INT_MAX, index = -1;
        for (int i = 0; i < M; i++) {
            edge e = E[i];
            if ((inset[e.i] && !inset[e.j] && e.w < minedge)) {
                minedge = e.w;
                index = i;
            }
            else if (!inset[e.i] && inset[e.j] && e.w < minedge) {
                minedge = e.w;
                index = i;
            }
        }
        if (!inset[E[index].i]) {
            inset[E[index].i] = true;
        }
        if (!inset[E[index].j]) {
            inset[E[index].j] = true;
        }
        sum += E[index].w;
        count++;
    }
    cout<<sum<<endl;
}

void jobprocess() {
    fstream fin;
    fin.open("/Users/zishirs/Documents/workspace/test/test/jobs.txt");
    if (fin.good()) {
        int N;
        fin >> N;
        vector<job> v(N);
        for (int i = 0; i < N; i++) {
            int w, l;
            fin >> w >> l;
            v[i].w = w;
            v[i].len = l;
        }
        sort(v.begin(), v.end(), diffcomp);
        size_t t = 0, sum = 0;
        for (int i = 0; i < N; i++) {
            t += v[i].len;
            sum += t * v[i].w;
        }
        //for (int i = 0; i < N; i++)
            //cout<< i << ": " << v[i].w << " ' " << v[i].len << " ' " << v[i].w - v[i].len <<endl;
        cout<<t<<" : "<<sum<<endl;
        sort(v.begin(), v.end(), divcomp);
        t = 0, sum = 0;
        for (int i = 0; i < N; ++i) {
            t += v[i].len;
            sum += t * v[i].w;
        }
        //for (int i = 0; i < N; i++)
            //cout<< i << ": " << v[i].w << " ' " << v[i].len << " ' " << v[i].w / v[i].len <<endl;
        cout<<t<<" : "<<sum<<endl;
    }
    fin.close();
}
#endif /* defined(__test__Prim_MST__) */