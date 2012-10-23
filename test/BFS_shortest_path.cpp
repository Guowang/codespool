//#include <iostream>
//#include <vector>
//#include <queue>
//#include <tr1/unordered_map>
//#define _N 10
//#define n _N*_N
//#define INF 100
//
//using namespace std;
//
//struct vertex
//{
//    bool visited;
//    vector<int> head_vertex;
//};
//
//class graph
//{
//    tr1::unordered_map<int, vertex> v;
//public:
//    int dist[n];
//    int prev[n];
//    void readGraph();
//    void BFS();
//    void output(int);
//};
//
//bool inbound(int,int);
//int main ()
//{
//    graph ag;
//    ag.readGraph();
//    ag.BFS();
//    ag.output(99);
//    return 0;
//}
//
//bool inbound(int i, int j)
//{
//    return (i >=0 && i < _N && j >= 0 && j < _N);
//}
//
//void graph::readGraph()
//{
//    int A[_N][_N] = {1,1,1,1,1,0,0,1,1,0,  0,1,1,0,1,1,0,0,1,1, 0,1,0,1,1,1,1,1,0,1, 1,0,0,1,1,0,1,1,1,0, 1,0,1,1,1,0,0,1,1,0,  0,1,0,1,1,1,1,1,0,1, 0,1,1,0,1,1,0,0,1,0, 1,0,1,1,0,1,0,1,0,0,  1,1,1,1,0,0,0,0,1,0, 1,1,0,0,1,0,0,1,1,1};
//    
//    for (int i = 0; i < _N; ++i) {
//        for (int j = 0; j < _N; ++j) {
//            cout<<A[i][j]<<"\t";
//        }
//        cout<<endl;
//    }
//    cout<<endl;
//    
//    for (int i = 0; i < _N; ++i) {
//        for (int j = 0; j < _N; ++j) {
//            vertex node;
//            node.visited = 0;
//            dist[i*_N + j] = INF;
//            prev[i*_N + j] = -1;
//            //matrix...
//            if (A[i][j]) {
//                if (inbound(i-1, j-1)) {
//                    if (A[i-1][j-1])
//                        node.head_vertex.push_back((i-1)*_N + j-1);
//                }
//                if (inbound(i-1, j)) {
//                    if (A[i-1][j])
//                        node.head_vertex.push_back((i-1)*_N + j);
//                }
//                if (inbound(i-1, j+1)) {
//                    if (A[i-1][j+1])
//                        node.head_vertex.push_back((i-1)*_N + j+1);
//                }
//                if (inbound(i, j-1)) {
//                    if (A[i][j-1])
//                        node.head_vertex.push_back((i)*_N + j-1);
//                }
//                if (inbound(i, j+1)) {
//                    if (A[i][j+1])
//                        node.head_vertex.push_back((i)*_N + j+1);
//                }
//                if (inbound(i+1, j-1)) {
//                    if (A[i+1][j-1])
//                        node.head_vertex.push_back((i+1)*_N + j-1);
//                }
//                if (inbound(i+1, j)) {
//                    if (A[i+1][j])
//                        node.head_vertex.push_back((i+1)*_N + j);
//                }
//                if (inbound(i+1, j+1)) {
//                    if (A[i+1][j+1])
//                        node.head_vertex.push_back((i+1)*_N + j+1);
//                }
//            }
//            pair<int, vertex> ap (i*_N + j, node);
//            v.insert(ap);
//        }
//    }
//   
//}
//
//void graph::BFS()
//{
//    queue<int> aqueue;
//    aqueue.push(0);
//    dist[0] = 0;
//    
//    while (!aqueue.empty()) {
//        int u;
//        u = aqueue.front();
//        aqueue.pop();
//        tr1::unordered_map<int, vertex>::iterator it;
//        it = v.find(u);
//        it->second.visited = 1;
//        for (vector<int>::iterator intit = it->second.head_vertex.begin(); intit != it->second.head_vertex.end(); ++intit) {
//            tr1::unordered_map<int, vertex>::iterator v_it;
//            v_it = v.find(*intit);
//            if (!v_it->second.visited) {
//                v_it->second.visited = 1;
//                aqueue.push(*intit);
//                dist[*intit] = dist[u] + 1;
//                prev[*intit] = u;
//            }
//        }
//    }
////    for (int i = 0; i < _N; ++i) {
////        for (int j = 0; j < _N; ++j)
////            cout<<prev[i*_N + j]<<"\t";
////        cout<<endl;
////    }
////    cout<<endl;
//}
//
//void graph::output(int i)
//{
//    if (i < 0) {
//        return;
//    }
//    else {
//        output(prev[i]);
//        cout<<i<<"\t";
//    }
//}