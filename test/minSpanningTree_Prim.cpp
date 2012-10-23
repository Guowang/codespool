//#include <iostream>
//#include <fstream>
//#include <string.h>
//#include <sstream>
//#include <vector>
//#include <tr1/unordered_map>
//#include <algorithm>
//#define INF 10000;
//using namespace std;
//
//
//struct vertex
//{
//    char index;
//    vector<char> adj;
//    char pi;
//    bool in_Q;
//    int key;
//    
//};
//
//struct edge
//{
//    int weight;
//    char v_1;
//    char v_2;
//};
//
//class graph
//{
//public:
//    vector<vertex> v;
//    vector<edge> e;
//    vector<vertex> Q;
//    
//    void readGraph();
//    void MST_PRIM();
//    void output();
//
//};
//
//bool operator < (vertex&, vertex&);
//
//int main ()
//{
//    graph ag;
//    ag.readGraph();
//    ag.MST_PRIM();
//    ag.output();
//    return 0;
//}
//
//void graph::readGraph()
//{
//    fstream fin;
//    fin.open("/Users/zishirs/Documents/workspace/test/test/graph_test.txt");
//    v.empty();
//    e.empty();
//    Q.empty();
//    while (fin.good())
//    {
//        string s;
//        getline(fin, s);
//        stringstream str;
//        char vi, vo;
//        int w;
//        str << s;
//        str >> vi >> vo >> w;
//        
//        edge e1, e2;
//        e1.v_1 = vi;
//        e1.v_2 = vo;
//        e1.weight = w;
//        e2.v_1 = vo;
//        e2.v_2 = vi;
//        e2.weight = w;
//        e.push_back(e1);
//        e.push_back(e2);
//        
//        bool flag_i = 0, flag_o = 0;
//        for (vector<vertex>::iterator it = v.begin(); it < v.end(); it++) {
//            if (it->index == vi) {
//                flag_i = 1;
//                it->adj.push_back(vo);
//                //cout<<vi<<"\t"<<vo<<"\t"<<w<<endl;
//            }
//            if (it->index == vo) {
//                flag_o = 1;
//                it->adj.push_back(vi);
//                //cout<<vi<<"\t"<<vo<<"\t"<<w<<endl;
//            }
//
//        }  
//        if (!flag_i) {
//            vertex v1;
//            v1.index = vi;
//            v1.adj.push_back(vo);
//            v1.in_Q = 1;
//            v1.pi = '?';
//            v1.key = INF;
//            v.push_back(v1);
//            //cout<<vi<<"\t"<<vo<<"\t"<<w<<endl;
//        }
//        if (!flag_o) {
//            vertex v2;
//            v2.index = vo;
//            v2.adj.push_back(vi);
//            v2.in_Q = 1;
//            v2.pi = '?';
//            v2.key = INF;
//            v.push_back(v2);
//            //cout<<vi<<"\t"<<vo<<"\t"<<w<<endl;
//        }
//    }
//    //cout<<v.size()<<endl;
//    fin.close();
//
//}
//
//bool operator < (vertex& v1, vertex& v2) {return (v1.key > v2.key);}
//
//void graph::MST_PRIM()
//{
//    Q = v;
//    Q.begin()->key = 0;
//    make_heap(Q.begin(),Q.end());
//    //cout<<Q.begin()->index<<endl;
//    while (Q.size()) {
//        make_heap(Q.begin(),Q.end());
//        vertex u;
//        u = Q.front();
//        //cout<<"sort: "<<u.index<<endl;
//        vector<vertex>::iterator vit;
//        for (vit = v.begin(); vit < v.end(); vit++) {
//            if (vit->index == u.index) {
//                //cout<<vit->index<<endl;
//                vit->pi = u.pi;
//                vit->in_Q = 0;
//                break;
//            }
//        }  
//        pop_heap(Q.begin(),Q.end());
//        Q.pop_back();
//        
//        for (vector<char>::iterator it = u.adj.begin(); it < u.adj.end(); it++) {
//            vector<vertex>::iterator vit;
//            for (vit = Q.begin(); vit < Q.end(); vit++) {
//                if (vit->index == *it) {
//                    break;
//                }
//            }  
//            vector<edge>::iterator eit;
//            int weight;
//            for (eit = e.begin(); eit < e.end(); eit++) {
//                if ((eit->v_1 == u.index)&&(eit->v_2 == *it)) {
//                    weight = eit->weight;
//                    break;
//                }
//            }
//            if ((vit->key > weight)&&(vit->in_Q)) {
//                vit->key = weight;
//                vit->pi = u.index;
//            }
//        }
//    }
//}
//
//void graph::output()
//{
//    vector<vertex>::iterator vit;
//    for (vit = v.begin(); vit < v.end(); vit++) {
//        cout<<vit->index<<"\t"<<vit->pi<<endl;
//    } 
//}