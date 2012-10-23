//#include <iostream>
//#include <fstream>
//#include <string.h>
//#include <sstream>
//#include <queue>
//#define _N 201
//#define INF 1000000
//using namespace std;
////2599,2610,2947,2052,2367,2399,2029,2442,2505,3068
//int graph[_N][_N];
//bool in_set[_N];
//int dist[_N];
//int prev[_N];
//
//void readGraph();
//
//void Dijkstra();
//
//void output(int);
//
//int main()
//{
//    readGraph();
//    Dijkstra();
//    
////    for (int i = 0; i < _N; i++) {
////        if (graph[1][i]<INF) {
////            cout<<i<<" "<<graph[1][i]<<endl;
////        }
////    }
//    
////    for (int j = 0; j < _N; j++) 
////    {
////        //if (dist[j] != INF) 
////        {
////            cout<<j+1<<" "<<dist[j]<<endl;
////        }
////    }
//    
//    //output(7);
//    
//    cout<<dist[7]<<",";
//    cout<<dist[37]<<",";
//    cout<<dist[59]<<",";
//    cout<<dist[82]<<",";
//    cout<<dist[99]<<",";
//    cout<<dist[115]<<",";
//    cout<<dist[133]<<",";
//    cout<<dist[165]<<",";
//    cout<<dist[188]<<",";
//    cout<<dist[197]<<endl;
//    
//    return 0;
//}
//
//void readGraph()
//{
//    for (int i = 1; i < _N; i++) 
//    {
//        dist[i] = INF;
//        in_set[i] = 1;
//        prev[i] = -1;
//        for (int j = 1; j < _N; j++) 
//        {
//            graph[i][j] = INF;
//        }
//    }
//    
//    fstream fin;
//    fin.open("/Users/zishirs/Documents/workspace/test/test/dijkstraData.txt");
//    //for (int k = 1; k < _N; k++) 
//    while (fin.good())
//    {
//        string s;
//        getline(fin, s);
//        stringstream str;
//        int i,j,len;
//        char c;
//        str << s;
//        str >> i;
//        //i--;
//        //cout<<k<<endl;
//        while (str != 0)
//        {
//            str >> j >> c >> len;
//            //j--;
//            graph[i][j] = len;
//            graph[j][i] = len;
//        }
//        
//    }
//    fin.close();
//}
//
//void Dijkstra()
//{
//    dist[1] = 0;
//    prev[1] = -1;
//    
////    //BFS version: not work...
////    queue<int> aqueue;
////    int u;
////    aqueue.push(1);
////    in_set[1] = 0; //explored
////    
////    while (!aqueue.empty()) {
////        u = aqueue.front();
////        aqueue.pop();
////        for (int v = 1; v < _N; ++v) {
////            if (graph[u][v] < INF) {
////                if ((dist[u] + graph[u][v]) < dist[v]) {
////                    dist[v] = dist[u] + graph[u][v];
////                    prev[v] = u;
////                }
////                if ((dist[v] + graph[u][v]) < dist[u]) {
////                    dist[u] = dist[v] + graph[u][v];
////                    prev[u] = v;
////                }
////                if (in_set[v]) {
////                    in_set[v] = 0;
////                    aqueue.push(v);
////                }
////            }
////        }
////    }
////    for (int k = 1; k < _N; ++k) {
////        for (int v = 1; v < _N; ++v) {
////            if (graph[k][v] < INF) {
////                if ((dist[v] + graph[k][v]) < dist[k]) {
////                    dist[k] = dist[v] + graph[k][v];
////                    prev[k] = v;
////                }
////            }
////        }
////    }
//
//    for (int i = 1; i < _N; i++) 
//    {
//        int min_len = INF,u = -1;
//        for (int j = 1; j < _N; j++) 
//        {
//            if ((in_set[j])&&(dist[j] < min_len)) 
//            {
//                min_len = dist[j];
//                u = j;
//            }
//        }
//            
//        if (min_len == INF) 
//        {
//            break;
//        }
//        in_set[u] = 0;
//        for (int k = 1; k < _N; k++) 
//        {
//            if ((graph[u][k] < INF)&&(in_set[k]))
//            {
//                if ((dist[u] + graph[u][k]) < dist[k])
//                {
//                    dist[k] = dist[u] + graph[u][k];
//                    prev[k] = u;
//                }
//            }
//        }
//    }
//    
//}
//
//void output(int index)
//{
//    if (index < 0)
//        return;
//    output(prev[index]);
//    cout<<index<<endl;
//    
//}
    