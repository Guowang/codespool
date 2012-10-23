//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <stdlib.h>
//#include <stdio.h>
//#include <vector>
//#include <stack>
//#include <list>
//#include <algorithm>
//#define _N 875714   //nodes: 875714; to: 456; from: 6326
////434821,968,459,313,211
//
//using namespace std;
//
//struct vertex
//{
//    bool visited,tvisited;
//    vector<int> edge,tedge;
//    
//    vertex()
//    {
//        visited = 0;
//        tvisited = 0;
//        edge.empty();
//        tedge.empty();
//    }
//};
//
//stack<int> prime_stack;
//list<int> results;
//
//vertex graph[_N];
//int count_SCC;
//void readGraph();
//void DFS(int i);
//void tDFS(int i);
//
//int main()
//{
//    //vertex * graph_ptr = (vertex*)malloc(sizeof(vertex)*(_N));
//    //memset(graph, NULL, _N);
//    readGraph();
//    prime_stack.empty();
//    results.empty();
//    count_SCC = 0;
//    
//    for (int i = 0; i < _N; i++) 
//    {
//        DFS(i);
//    }
//    
////    for (vector<int>::reverse_iterator it = prime_stack.rbegin(); it < prime_stack.rend();++it) 
////    {
////        if (!graph[*it].tvisited)
////        {
////            count_SCC = 1;
////            tDFS(*it);
////            results.push_back(count_SCC);
////        }
////        
////    }
//    while (!prime_stack.empty())
//    {
//        int it;
//        it = prime_stack.top();
//        prime_stack.pop();
//        if (!graph[it].tvisited)
//        {
//            count_SCC = 1;
//            tDFS(it);
//            results.push_back(count_SCC);
//        }
//        
//    }
//
//    
//    results.sort();
//    
////    int sum = 0;
////    for (list<int>::iterator lit = results.begin(); lit != results.end(); lit++) 
////    {
////        sum += *lit;
////    }
////    cout<<sum<<endl;
//    
//    list<int>::iterator intit;
//    intit= results.end();
//    intit--;
//    for (int j = 0; j < 5; j++) 
//    {
//        cout<<*intit<<endl;
//        intit--;
//    }
//    
//    return 0;
//}
//
//void readGraph()
//{
//    //read in each line, first - 1 is the node index, second - 1 push into out_nodes
//    ifstream fin;
//    fin.open("/Users/zishirs/Documents/workspace/test/test/SCC.txt");
//    
//    string s;
//    
//    while (getline(fin,s)) 
//    {
//        stringstream str;
//        int node_index, out_index;
//        str << s;
//        str >> node_index >> out_index;
//        node_index--;
//        out_index--;
//        
//        graph[node_index].edge.push_back(out_index);
//        graph[out_index].tedge.push_back(node_index);
//    }
//    
//    fin.close();
//}
//
//void DFS(int i)
//{
//    if (!graph[i].visited) 
//    {
//        graph[i].visited = 1;
//        for (vector<int>::iterator it = graph[i].edge.begin(); it < graph[i].edge.end(); it++) 
//        {
//            if (!graph[*it].visited)
//                DFS(*it);
//        }
//        prime_stack.push(i);
//    }
//}
//
//void tDFS(int i)
//{
//    if (!graph[i].tvisited) 
//    {
//        graph[i].tvisited = 1;
//        for (vector<int>::iterator it = graph[i].tedge.begin(); it < graph[i].tedge.end(); it++) 
//        {
//            if (!graph[*it].tvisited)
//            {
//                tDFS(*it);
//                count_SCC++;
//            }
//                
//        }
//
//    }
//}

//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//int main ()
//{
//    vector<int> av;
//    for (int i = 0; i < 10; ++i) {
//        av.push_back(i);
//    }
//    for (vector<int>::iterator it = av.begin(); it != av.end(); ++it) {
//        cout<<*it<<"\t";
//    }
//    cout<<endl;
//    for (vector<int>::reverse_iterator it = av.rbegin(); it != av.rend(); ++it) {
//        cout<<*it<<"\t";
//    }
//    cout<<endl;
//    return 0;
//}