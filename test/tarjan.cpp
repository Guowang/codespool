//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <cstdlib>
//#include <stdio.h>
//#include <stack>
//#include <list>
//#include <algorithm>
//#define _N 875714   //nodes: 875714
//#define MAX 456 //maximum number of outward nodes from each node: 456; average: 5; total edges: 5105043
////434821
////968
////459
////313
////211
//
//using namespace std;
//
//void readGraph();
//void visit(int);
//
//int c;
//stack<int> prime_stack;
//list<int> results;
//int N[_N],L[_N],length[_N];
//bool visited[_N],in_stack[_N];
//int crazy[_N][MAX];
//
//int main()
//{
//    readGraph();
//    c = 0;
//    prime_stack.empty();
//    results.empty();
//    
//    for (int verit = 0; verit < _N; ++verit) 
//    {
//        if(!visited[verit])
//            visit(verit);
//    }
//    
//    results.sort();
//    list<int>::iterator intit = results.end();
//    intit--;
//    for (int j = 0; j < 5; j++) 
//    {
//        cout<<*intit<<endl;
//        intit--;
//    }
//    
////    //total number of nodes in all SCCs 
////    list<int>::iterator intit1;
////    unsigned int sum = 0;
////    for (intit1 = results.begin(); intit1 != results.end(); ++intit1) 
////    {
////        sum += *intit1;
////    }
////    cout<<sum<<endl;
//    
//    return 0;
//}
//
//void readGraph()
//{
//    //initialization: push in 875714 nodes, from 0 ~ 875713; set flag in_stack in each node to 0.
//    for (int i = 0; i < _N; i++) 
//    {
//        length[i] = 0;
//        visited[i] = 0;
//        in_stack[i] = 0;
//    }
//    
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
//        
//        node_index--;
//        out_index--;
//        crazy[node_index][length[node_index]]= out_index;
//        length[node_index] += 1;
//    }
//    
//    fin.close();
//}
//
//void visit(int node_v)
//{
//    //mark node_v to visited
//    visited[node_v] = true;
//    //a depth search index v.index, which numbers the nodes consecutively in the order in which they are discovered
//    N[node_v] = c;
//    //v.lowlink that is equal to the smallest index of some node reachable from v, and always less than v.index, or equal to v.index if no other node is reachable from v
//    L[node_v] = c;
//    c++;
//    
//    //push v into stack
//    prime_stack.push(node_v);
//    in_stack[node_v] = true;
//    
//    //for each w in out_nodes(node_v)
//    for (int intit = 0; intit < length[node_v]; ++intit) 
//    {
//        int wit;
//        wit = crazy[node_v][intit];   //node_w index
//
//        if (!visited[wit])  //node_w unvisited
//        {
//            visit(wit);
//            //check lower_link number
//            if (L[node_v] > L[wit]) 
//            {
//                L[node_v] = L[wit];
//            }
//        }
//        else
//        {
//            if (in_stack[wit]) //node_w is in stack
//            {
//                //check lower reachable index
//                if (L[node_v] > N[wit]) 
//                {
//                    L[node_v] = N[wit];
//                }
//            }
//        }
//    }
//    
//    //check if SC components found
//    if (L[node_v] == N[node_v]) 
//    {
//        //pop vertices off stacks down to node_v
//        int count = 0,top_index = 0;
//        while (prime_stack.top() != node_v) 
//        {
//            top_index = prime_stack.top(); 
//            prime_stack.pop();
//            count++;
//            in_stack[top_index] = 0;
//        }
//        top_index = prime_stack.top();
//        prime_stack.pop();
//        count++;
//        in_stack[top_index] = 0;
//        results.push_back(count);
//    }
//}