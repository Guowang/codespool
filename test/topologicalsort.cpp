//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <tr1/unordered_map>
//#include <tr1/unordered_set>
//#include <stack>
//#include <queue>
//#include <vector>
//
//using namespace std;
//
//struct vertex
//{
//    tr1::unordered_set<int> out_vertices;
//    tr1::unordered_set<int> incoming_vertices;
//};
//
//struct edge
//{
//    int from_index;
//    int to_index;
//};
//
//class graph
//{
//    public:
//    tr1::unordered_map<int, vertex> v;
//    tr1::unordered_map<int,edge> e;
//    queue<int> sorted_list;
//    void readGraph();
//    void topsort();
//    void output();
//};
//
//int main()
//{
//    graph ag;
//    ag.readGraph();
//    ag.topsort();
//    ag.output();
//    
//    return 0;
//}
//
//void graph::readGraph()
//{
//    fstream fin;
//    fin.open("/Users/zishirs/Documents/workspace/test/test/graph_test.txt");
//    int i = 0;
//    while (fin.good()) 
//    {
//        string s;
//        int from_index, to_index;
//        stringstream str;
//        getline(fin,s);
//        str << s;
//        str >> from_index >>to_index;
//        edge edge1;
//        edge1.from_index = from_index;
//        edge1.to_index = to_index;
//        pair<int, edge> edge_input (i,edge1);
//        i++;
//        e.insert(edge_input);
//        tr1::unordered_map<int, vertex>::iterator it;
//        it = v.find(from_index);
//        if (it == v.end()) 
//        {
//            vertex from;
//            from.out_vertices.empty();
//            from.out_vertices.insert(to_index);
//            from.incoming_vertices.empty();
//            pair<int, vertex> f (from_index,from);
//            v.insert(f);
//        }
//        else
//        {
//            it->second.out_vertices.insert(to_index);
//        }
//        it = v.find(to_index);
//        if (it == v.end()) 
//        {
//            vertex to;
//            to.out_vertices.empty();
//            to.incoming_vertices.empty();
//            to.incoming_vertices.insert(from_index);
//            pair<int, vertex> t (to_index,to);
//            v.insert(t);
//        }
//        else
//        {
//            it->second.incoming_vertices.insert(from_index);
//        }
//    }
//    //cout<<v.size()<<endl;
//    //cout<<e.size()<<endl;
//    fin.close();
//}
//
//void graph::topsort()
//{
//    sorted_list.empty();
//    stack<int> set;
//    tr1::unordered_map<int, vertex>::iterator it;
//    for (it = v.begin(); it != v.end(); ++it) 
//    {
//        if (it->second.incoming_vertices.empty()) 
//        {
//            //cout<<it->first<<endl;
//            set.push(it->first);
//        }
//    }
//    //cout<<set.size()<<endl;
//    while (!set.empty()) 
//    {
//        int index = set.top();
//        set.pop();
//        sorted_list.push(index);
//        
//        it = v.find(index);
//        tr1::unordered_set<int>::iterator int_it;
//        for (int_it = it->second.out_vertices.begin(); int_it != it->second.out_vertices.end(); ++int_it) 
//        {
//            tr1::unordered_map<int,vertex>::iterator v_it;
//            v_it = v.find(*int_it);
//            
//            for (tr1::unordered_map<int, edge>::iterator e_it = e.begin(); e_it != e.end(); ++e_it) 
//            {
//                if ((e_it->second.from_index == index)&&(e_it->second.to_index == *int_it)) 
//                {
//                    e.erase(e_it);
//                }
//            }
//            
//            v_it->second.incoming_vertices.erase(index);
//            if (v_it->second.incoming_vertices.empty()) 
//            {
//                set.push(*int_it);
//            }
//        }
//    }
//}
//
//void graph::output()
//{
//    if (e.empty()) 
//    {
//        while (!sorted_list.empty()) 
//        {
//            cout<<sorted_list.front()<<endl;
//            sorted_list.pop();
//        }
//    }
//    else
//    {
//        cout<<"Error."<<endl;
//    }
//}

//7   11
//7   8
//5   11
//3   8
//3   10
//11  2
//11  9
//11  10
//8   9   