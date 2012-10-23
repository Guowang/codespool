//#include <iostream>
//#include <sstream>
//#include <vector>
//#include <stdio.h>
//#include <ctype.h>
//#define MAX 300
//#define INF 214748364
//using namespace std;
//
//struct vertex
//{
//    bool color;
//    int remaining_t;
//    int tiB;
//    int tiP;
//};
//
//struct graph
//{
//    vertex v[MAX];
//    int e[MAX][MAX];
//    int begin_index,end_index;
//    int vertex_num;
//    int time_spent[MAX];
//    int prev[MAX];
//    bool in_set[MAX];
//    
//    int waiting_time(int t,int index_i,int index_j);
//    void Dijkstra();
//    void readGraph();
//    void output(int index);
//    graph()
//    {
//        for (int i = 0; i < MAX; ++i) 
//        {
//            time_spent[i] = INF;
//            prev[i] = -1;
//            in_set[i] = 1;
//            for (int j = 0; j < MAX; ++j) 
//            {
//                e[i][j] = INF;
//            }
//        }
//    };
//    
//};
//
//int main ()
//{
//    graph ag;
//    ag.readGraph();
//    ag.Dijkstra();
//    if (ag.time_spent[ag.end_index] != INF)
//        cout<<ag.time_spent[ag.end_index]<<endl;
//    else
//        cout<<0<<endl;
//    //ag.output(ag.end_index);
//    return 0;
//}
//
//
//int graph::waiting_time(int t,int index_i,int index_j)
//{
//    int temp_i = (t - v[index_i].remaining_t + v[index_i].tiB + v[index_i].tiP)%(v[index_i].tiB + v[index_i].tiP);
//    bool index_i_color;
//    int index_i_remaining_t;
//    
//    if (v[index_i].color == 0)
//    {
//        if (temp_i < v[index_i].tiP) 
//        {
//            index_i_color = 1;
//            index_i_remaining_t = v[index_i].tiP - temp_i;
//        }
//        else
//        {
//            index_i_color = 0;
//            index_i_remaining_t = v[index_i].tiB + v[index_i].tiP - temp_i;
//        }
//    }
//    else
//    {
//        if (temp_i < v[index_i].tiB) 
//        {
//            index_i_color = 0;
//            index_i_remaining_t = v[index_i].tiB - temp_i;
//        }
//        else
//        {
//            index_i_color = 1;
//            index_i_remaining_t = v[index_i].tiP + v[index_i].tiB - temp_i;
//        }
//    }
//
//    int temp_j = (t - v[index_j].remaining_t + v[index_j].tiB + v[index_j].tiP)%(v[index_j].tiB + v[index_j].tiP);
//    bool index_j_color;
//    int index_j_remaining_t;
//    
//    if (v[index_j].color == 0)
//    {
//        if (temp_j < v[index_j].tiP) 
//        {
//            index_j_color = 1;
//            index_j_remaining_t = v[index_j].tiP - temp_j;
//        }
//        else
//        {
//            index_j_color = 0;
//            index_j_remaining_t = v[index_j].tiB + v[index_j].tiP - temp_j;
//        }
//    }
//    else
//    {
//        if (temp_j < v[index_j].tiB) 
//        {
//            index_j_color = 0;
//            index_j_remaining_t = v[index_j].tiB - temp_j;
//        }
//        else
//        {
//            index_j_color = 1;
//            index_j_remaining_t = v[index_j].tiP + v[index_j].tiB - temp_j;
//        }
//    }
//
//    
//    int wait_t;
//    if (index_i_color == index_j_color) 
//    {
//        return 0;
//    }
//    else
//    {
//        if (index_i_remaining_t != index_j_remaining_t) 
//        {
//            wait_t = index_i_remaining_t;
//            if (index_i_remaining_t > index_j_remaining_t)
//                wait_t = index_j_remaining_t;
//            return wait_t;
//        }
//        else
//        {
//            if (!index_i_color) //blue
//            {
//                if (v[index_i].tiP != v[index_j].tiB) 
//                {
//                    wait_t = v[index_i].tiP;
//                    if (v[index_i].tiP > v[index_j].tiB)
//                        wait_t = v[index_j].tiB;
//                    return wait_t + index_i_remaining_t;
//
//                }
//                else
//                {
//                    if (v[index_i].tiB != v[index_j].tiP) 
//                    {
//                        wait_t = v[index_i].tiB;
//                        if (v[index_i].tiB > v[index_j].tiP)
//                            wait_t = v[index_j].tiP;
//                        return wait_t + index_i_remaining_t + v[index_i].tiP;
//                    }
//                    else
//                        return -1;
//                }
//            }
//            else
//            {
//                if (v[index_i].tiB != v[index_j].tiP) 
//                {
//                    wait_t = v[index_i].tiB;
//                    if (v[index_i].tiB > v[index_j].tiP)
//                        wait_t = v[index_j].tiP;
//                    return wait_t + index_i_remaining_t;
//                    
//                }
//                else
//                {
//                    if (v[index_i].tiP != v[index_j].tiB) 
//                    {
//                        wait_t = v[index_i].tiP;
//                        if (v[index_i].tiP > v[index_j].tiB)
//                            wait_t = v[index_j].tiB;
//                        return wait_t + index_i_remaining_t + v[index_i].tiB;
//                    }
//                    else
//                        return -1;
//                }
//
//            }
//        }
//    }
//    
//}
//
//void graph::readGraph()
//{
//    int begin_in=0,end_in=0,n=0,edge_num=0;
//    cin >> begin_in >> end_in;
//    cin >> n >> edge_num;
//    //cout<<begin_in<<" "<<end_in<<" "<<n<<" "<<edge_num<<endl;
//    //getchar();
//    //scanf("%d%d%d%d",&begin,&end,&n,&m);
//    begin_in--;
//    end_in--;
//    begin_index = begin_in;
//    end_index = end_in;
//    vertex_num = n;
//    string s;
//    stringstream str;
//    for (int i = 0; i < n; ++i) 
//    {
//        
//        char c;
//        int remaining_t,tiB,tiP;
//        while (!isalpha(c = getchar())) ;
//        cin >> remaining_t >> tiB >> tiP;
//        //scanf("%d%d%d", &remaining_t, &tiB, &tiP);
//        v[i].remaining_t = remaining_t;
//        v[i].tiB = tiB;
//        v[i].tiP = tiP;
//        //cout<<i<<endl;
//        //cout<<c<<" "<<v[i].remaining_t<<" "<<v[i].tiB<<" "<<v[i].tiP<<endl;
//        //cout<<c<<endl;
//        //getline(cin,s);
//        //str << s;
//        //while (!isalpha(c = getchar())) ;
//        //str >> c >> v[i].remaining_t >> v[i].tiB >> v[i].tiP;
//        if (c == 'B')
//            v[i].color = 0;
//        else
//            v[i].color = 1;
//        
//        //cin >> v[i].remaining_t >> v[i].tiB >> v[i].tiP;
//        //scanf("%d%d%d",&v[i].remaining_t,&v[i].tiB,&v[i].tiP);
//    }
//    
//    for (int j = 0; j < edge_num; ++j) 
//    //int j = 0;
//    //while (getline(cin,s))
//    {
//        //j++;
//        int index_i,index_j,t;
//        scanf("%d%d%d", &index_i, &index_j, &t);
//        //cin >> index_i >> index_j >> t;
//        //str << s;
//        //str >> index_i >> index_j >> t;
//        index_i--;
//        index_j--;
//        e[index_i][index_j] = t;
//        e[index_j][index_i] = t;
//        //cout<<"j: "<<j<<endl;
//        //cout<<e[index_j][index_i]<<endl;
//    }
//    
//}
//
//void graph::output(int index)
//{
//    if (index < 0)
//        ;
//    else
//    {
//        output(prev[index]);
//        cout<< index + 1 <<endl;
//    }
//}
//
//void graph::Dijkstra()
//{
//    time_spent[begin_index] = 0;
//    prev[begin_index] = -1;
//    
//    for (int i = 0; i < vertex_num; ++i) 
//    {
//        int min_t = INF,u = -1;
//        for (int j = 0; j < vertex_num; ++j) 
//        {
//            if ((in_set[j]) && (min_t > time_spent[j])) 
//            {
//                min_t = time_spent[j];
//                u = j;
//            }
//            
//        }
//        if ((min_t == INF)||(u == end_index))
//            break;
//        in_set[u] = 0;
//        
//        for (int k = 0; k < vertex_num; ++k) 
//        {
//            if ((in_set[k])&&(e[u][k]!=INF)) 
//            {
//                int w_t = waiting_time(time_spent[u], u, k);
//                int alt = time_spent[u] + w_t + e[u][k];
//                if ((alt < time_spent[k])&&(w_t != -1)) 
//                {
//                    time_spent[k] = alt;
//                    prev[k] = u;
//                }
//            }
//        }
//        
//    }
//}
