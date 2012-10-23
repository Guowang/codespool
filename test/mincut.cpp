//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <cstdlib>
//#include <time.h>
//#include <stdio.h>
//#include <vector>
//
//
//using namespace std;
//
//struct verticeNode
//{
//    int node_index;
//    vector<int> adjecent_nodes;
//};
//
//struct edge
//{
//    int head_index;
//    int rear_index;
//};
//
//class graph
//{
//    public:
//    vector<verticeNode> v;
//    vector<edge> e;
//    
//    void readGraph();
//    void contraction();
//    
//};
//
//
//int main()
//{
//    graph ag;
//    ag.readGraph();
//    
////    unsigned int i;
////    vector<unsigned int> myvector;
////    vector<unsigned int>::iterator iit;
////    
////    // set some values (from 1 to 10)
////    for (i=1; i<=10; i++) myvector.push_back(i);
////    
////    for (iit=myvector.begin(); iit<myvector.end(); iit++)
////    {
////        myvector.erase(iit);
////        --iit;
////        cout << "Size: "<<myvector.size()<<" Value: "<<*iit<<endl;
////    }
//    
//    
//    
//    int min=ag.e.size();
//    
//    for (int i=0; i<20; ++i) 
//    {
//        graph ag_copy = ag;
//        ag_copy.contraction();
//        
//        if (min > ag_copy.e.size()) 
//        {
//            min = ag_copy.e.size();
//        }
//    }
//    cout<<min<<endl;
//    return 0;
//}
//
//void graph::readGraph()
//{
//    ifstream fin;
//    fin.open("/Users/zishirs/Documents/workspace/test/test/kargerMinCut.txt");
//    
//    string s;
//    
//    while (getline(fin,s)) {
//        
//        stringstream str;
//        verticeNode node1;
//        edge edge1;
//        int adj_nodes;
//        
//        str << s;
//        str >> node1.node_index;
//        
//        while (str >> adj_nodes) 
//        {
//            edge1.head_index = node1.node_index;
//            edge1.rear_index = adj_nodes;
//            if (edge1.head_index < edge1.rear_index) 
//            {
//                e.push_back(edge1);
//            }
//            
//            node1.adjecent_nodes.push_back(adj_nodes);
//        }
//        v.push_back(node1);
//    }
//
//    fin.close();
//}
//
//void graph::contraction()
//{
//    while (v.size()>2) 
//    {
//        //randomly pick up an edge
//        int i,j;
//        srand(time(0));
//        int random_n=0;
//        random_n = (int)rand() % e.size();
//        vector<edge>::iterator eit;
//        eit = e.begin() + random_n;
//        i = eit->head_index;
//        j = eit->rear_index;
//        
//        vector<verticeNode>::iterator run,nit_i,nit_j;
//        for (run = v.begin(); run < v.end(); run++) 
//        {
//            if(run->node_index == i)
//                nit_i = run;
//            if(run->node_index == j)
//                nit_j = run;
//        }
//        
//        //all adjecent nodes in j copy to i
//        vector<int>::iterator anodes;
//        for (anodes = nit_j->adjecent_nodes.begin(); anodes < nit_j->adjecent_nodes.end(); anodes++) 
//        {
//            int out = *anodes;
//            nit_i->adjecent_nodes.push_back(out);
//        }
//        
//        //for j's each adjecent node, replace j to i
//        for (anodes = nit_j->adjecent_nodes.begin(); anodes < nit_j->adjecent_nodes.end(); anodes++) 
//        {
//            int output = *anodes;
//            vector<verticeNode>::iterator nit_k,runner;
//            for (runner = v.begin(); runner < v.end(); runner++) 
//            {
//                if(runner->node_index == output)
//                {
//                    nit_k = runner;
//                }
//            }
//            vector<int>::iterator bnodes;
//            for (bnodes = nit_k->adjecent_nodes.begin(); bnodes < nit_k->adjecent_nodes.end(); bnodes++) 
//            {
//                if (*bnodes == nit_j->node_index) 
//                {
//                    *bnodes = nit_i->node_index;
//                }
//            }
//            
//        }
//        
//        //remove self-loop in i
//        for (anodes = nit_i->adjecent_nodes.begin(); anodes < nit_i->adjecent_nodes.end(); ++anodes) 
//        {
//            if (*anodes == nit_i->node_index) 
//            {
//                nit_i->adjecent_nodes.erase(anodes--);
//            }
//            
//        }
//        
//        //update e: for each edge containing j, replace with i, remove self-loop
//        for (vector<edge>::iterator eeit = e.begin(); eeit < e.end(); eeit++) 
//        {
//            if (eeit->head_index == nit_j->node_index) 
//            {
//                eeit->head_index = nit_i->node_index;
//            }
//            else 
//            {
//                if(eeit->rear_index == nit_j->node_index)
//                {
//                    eeit->rear_index = nit_i->node_index;
//                }
//            }
//            
//            if (((eeit->head_index == nit_i->node_index)) && ((eeit->rear_index == nit_i->node_index))) 
//            {
//                e.erase(eeit--);
//            }
//        }
//        
//        //delete j
//        v.erase(nit_j);
//        
//    }
//    
//}
