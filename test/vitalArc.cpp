#define __test__vitalArc__
#ifndef __test__vitalArc__
#include <climits>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tr1/unordered_map>

using namespace std;
/*
7 10
0 1 1
1 2 1
2 3 1
3 4 1
4 5 1
2 4 5
0 2 4
1 3 2
0 6 5
4 6 1
0 5
5
0 1
1 2
2 3
3 4
4 5
*/

struct vertex{
    int ds, dt, island_id;
    vector<int> adjacent;
    bool visited;
    vertex() : ds(INT_MAX), dt(INT_MAX), visited(false){};
};

//define: u->S < v->D
struct edge{
    int u, v;
    int weight, rank;
    string s;
    edge() : u(INT_MAX), v(INT_MAX), weight(INT_MAX), s(""){};
};

int S, D, OPT;
vector<vertex> V;
vector<edge> E;
//define: u < v
tr1::unordered_map<string, int> edge_map;
vector<int> bridges;
tr1::unordered_map<int, int> bridge_map;
vector<int> bridge_ends;
tr1::unordered_map<int, int> end_map;
vector<int> bypass;

//update ds;
void dsDijkstra(int s);

//update dt;
void dtDijkstra(int s);

//find all bridges
void findBridges();

//update island id
void getIslandID();

//fill in bypass value
void getBypass();

//helper functions
inline string toS(int i) {ostringstream os; os << i; return os.str();};
class ncomp{
    bool reverse;
public:
    ncomp(const bool & flag = false) {reverse = flag;};
    bool operator()(int i, int j){
        if (reverse)
            return V[i].dt > V[j].dt;
        else
            return V[i].ds > V[j].ds;
    };
};
class ucomp{
    bool reverse;
public:
    ucomp(const bool & flag = false) {reverse = flag;};
    bool operator()(int i, int j){
        if (reverse)
            return V[E[i].u].ds > V[E[j].u].ds;
        else
            return V[E[i].u].ds < V[E[j].u].ds;
    };
};
class vcomp{
    bool reverse;
public:
    vcomp(const bool & flag = false) {reverse = flag;};
    bool operator()(int i, int j){
        if (reverse)
            return V[E[i].v].ds > V[E[j].v].ds;
        else
            return V[E[i].v].ds < V[E[j].v].ds;
    };
};


void DFS(int i, int index);

int main(){
    int N, M, Q;
    cin >> N >> M;
    vertex node;
    V.assign(N, node);
    E.resize(M);
    int u, v, w;
    for (int i = 0; i < M; i++) {
        int temp;
        cin >> u >> v >> w;
        if (u > v) {
            temp = u;
            u = v;
            v = temp;
        }
        //update edges
        E[i].u = u;
        E[i].v = v;
        E[i].weight = w;
        E[i].s = toS(u) + '+' + toS(v);
        edge_map.insert(make_pair(E[i].s, i));
        //update vertex
        V[u].adjacent.push_back(v);
        V[v].adjacent.push_back(u);
    }
    
    cin >> S >> D;
    dsDijkstra(S);
    dtDijkstra(D);
    OPT = V[D].ds;
    findBridges();
    getIslandID();
    getBypass();
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int temp;
        cin >> u >> v;
        if (u > v) {
            temp = u;
            u = v;
            v = temp;
        }
        
        tr1::unordered_map<int, int>::iterator it = bridge_map.find(edge_map.find(toS(u) + '+' + toS(v))->second);
        if (it != bridge_map.end()) {
            int k = it->second;
            if (bypass[k] != INT_MAX)
                cout<<bypass[k]<<endl;
            else
                cout<<"Infinity"<<endl;
        }
        else
            cout<<V[D].ds<<endl;
    }
    return 0;
}

void dsDijkstra(int s){
    int sz = V.size();
    for (int i = 0; i < sz; i++)
        V[i].visited = false;
    V[s].ds = 0;
    typedef priority_queue<int, vector<int>, ncomp> mintype;
    mintype minheap(ncomp(false));
    minheap.push(s);
    while (!minheap.empty()) {
        int u = minheap.top();
        minheap.pop();
        if (V[u].ds == INT_MAX)
            break;
        if (V[u].visited)
            continue;
        V[u].visited = true;
        vector<int>::iterator iit;
        for (iit = V[u].adjacent.begin(); iit != V[u].adjacent.end(); ++iit) {
            int v = *iit;
            if (!V[v].visited) {
                int edge;
                if (u < v)
                    edge = edge_map.find(toS(u) + '+' + toS(v))->second;
                else
                    edge = edge_map.find(toS(v) + '+' + toS(u))->second;
                //cout<<"u: "<<u<<" ds: "<<V[u].ds<<" v: "<<v<<" edge: "<<E[edge].weight<<endl;
                if (V[v].ds > E[edge].weight + V[u].ds) {
                    V[v].ds = E[edge].weight + V[u].ds;
                    minheap.push(v);
                    //cout<<"push: "<<v<<" top: "<<minheap.top()<<" ds: "<<V[minheap.top()].ds<<endl;
                }
            }
        }
    }
}

void dtDijkstra(int s){
    int sz = V.size();
    for (int i = 0; i < sz; i++)
        V[i].visited = false;
    V[s].dt = 0;
    typedef priority_queue<int, vector<int>, ncomp> mintype;
    mintype minheap(ncomp(true));
    minheap.push(s);
    while (!minheap.empty()) {
        int u = minheap.top();
        minheap.pop();
        if (V[u].dt == INT_MAX)
            break;
        if (V[u].visited)
            continue;
        V[u].visited = true;
        vector<int>::iterator iit;
        for (iit = V[u].adjacent.begin(); iit != V[u].adjacent.end(); ++iit) {
            int v = *iit;
            if (!V[v].visited) {
                int edge;
                if (u < v)
                    edge = edge_map.find(toS(u) + '+' + toS(v))->second;
                else
                    edge = edge_map.find(toS(v) + '+' + toS(u))->second;
                if (V[v].dt > E[edge].weight + V[u].dt) {
                    V[v].dt = E[edge].weight + V[u].dt;
                    minheap.push(v);
                }
            }
        }
    }
}

//find all bridges
void findBridges(){
    
    vector<int> optimal;
    //find all optimal edges
    int sz = E.size();
    for (int i = 0; i < sz; i++) {
        int temp;
        if (V[E[i].u].ds > V[E[i].v].ds){
            temp = E[i].u;
            E[i].u = E[i].v;
            E[i].v = temp;
        }
        if (V[E[i].u].ds + E[i].weight + V[E[i].v].dt == OPT)
            optimal.push_back(i);
    }
    
    //find all bridges
    vector<bool> isBridge(sz, true);
    int opsz = optimal.size();
    ucomp uobj;
    sort(optimal.begin(), optimal.end(), uobj);
    for (int i = 0; i < opsz - 1; i++) {
        if (V[E[optimal[i]].v].ds > V[E[optimal[i + 1]].u].ds)
            isBridge[optimal[i]] = false;
    }
    vcomp vobj;
    sort(optimal.begin(), optimal.end(), vobj);
    for (int i = 1; i < opsz; i++) {
        if (V[E[optimal[i]].u].ds < V[E[optimal[i - 1]].v].ds)
            isBridge[optimal[i]] = false;
    }
    
    for (int i = 0; i < opsz; i++) {
        if (isBridge[optimal[i]]) {
            //cout<<"B: "<<E[optimal[i]].s<<endl;
            bridges.push_back(optimal[i]);
        }
    }
    sort(bridges.begin(), bridges.end(), uobj);
    bridge_ends.push_back(S);
    end_map.insert(make_pair(S, 0));
    int bgsz = bridges.size();
    for (int i = 0; i < bgsz; i++) {
        bridge_ends.push_back(E[bridges[i]].v);
        end_map.insert(make_pair(E[bridges[i]].v, i+1));
        bridge_map.insert(make_pair(bridges[i], i));
    }
}

//update island id
void getIslandID(){
    int sz = V.size();
    for (int i = 0; i < sz; i++)
        V[i].visited = false;
    int bgendsz = bridge_ends.size();
    for (int i = 0; i < bgendsz; i++)
        DFS(bridge_ends[i], i);
}

//
void DFS(int i, int index){
    if (!V[i].visited){
        V[i].visited = true;
        V[i].island_id = index;
        vector<int>::iterator iit;
        for (iit = V[i].adjacent.begin(); iit != V[i].adjacent.end(); ++iit) {
            if (!V[*iit].visited && (end_map.find(*iit) == end_map.end())) {
                int u = i, v = *iit;
                if (u > v) {
                    int temp = u;
                    u = v;
                    v = temp;
                }
                int edge = edge_map.find(toS(u) + '+' + toS(v))->second;
                if (E[edge].weight + V[i].ds == V[*iit].ds) {
                    DFS(*iit, index);
                }
            }
        }
    }
}
//fill in bypass value
void getBypass(){
    int bgsz = bridges.size(), sz = E.size();
    bypass.assign(bgsz, INT_MAX);
    for (int l = 0; l < sz; l++) {
        if (bridge_map.find(l) == bridge_map.end()) {
            int i = V[E[l].u].island_id, j = V[E[l].v].island_id;
            if (i != INT_MAX && j != INT_MAX) {
                int u = E[l].u, v = E[l].v;
                if (V[u].island_id > V[v].island_id) {
                    int temp = u;
                    u = v;
                    v = temp;
                }
                i = V[u].island_id, j = V[v].island_id;
                for (int m = i; m < j; m++) {
                    if (bypass[m] > V[u].ds + E[l].weight + V[v].dt) {
                        bypass[m] = V[u].ds + E[l].weight + V[v].dt;
                    }
                }
            }
        }
    }
}
#endif