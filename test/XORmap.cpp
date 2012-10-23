//#include <iostream>
//#include <fstream>
//#include <queue>
//
//using namespace std;
//
//struct _XOR
//{
//    int L;
//    int R;
//    int T;
//    int B;
//};
//
//int _N;
//
//int step = 0;
//
//bool graph[2002][2002];
//
//bool corners[2001][2001];
//
//queue<_XOR> results;
//
//void input();
//
//bool find_square();
//
//bool find_tri();
//
//void all_white();
//
//void output();
//
//void check();
//
//int main ()
//{
//    input();
//    
//    all_white();
//    
//    check();
//    
//    output();
//    
//    return 0;
//}
//
//void input()
//{
//    fstream fin;
//    fin.open("/Users/zishirs/Documents/workspace/test/test/xor10.in");
//    fin >> _N;
//    
//    for (int i = 0; i <= _N; i++) {
//        for (int j = 0; j <= _N; j++) {
//            if ((i >=1 )&&(j >= 1)&&(i <= _N)&&(j <= _N)) {
//                fin >> graph[i][j];
//            }
//            if ((i == 0)||(j == 0)||(i == _N + 1 )||(j == _N + 1)) {
//                graph[i][j] = 0;
//            }
//            
//        }
//    }
//    //generate corners[_N+1][_N+1]
//    int count = 0;
//    for (int i = 0; i <= _N; i++) {
//        for (int j = 0; j <= _N; j++) {
//            count = 0;
//            if (graph[i][j])
//                count++;
//            if (graph[i+1][j])
//                count++;
//            if (graph[i][j+1])
//                count++;
//            if (graph[i+1][j+1])
//                count++;
//            if ((count == 1)||(count == 3)) 
//                corners[i][j] = 1;
//            else
//                corners[i][j] = 0;
//        }
//    }
//    fin.close();
//}
//
//bool find_square()
//{
//    _XOR op;
//    // i is t, j is l
//    // try to find r and b with L, R, T, B == 1 as corners
//    int i, j, r, b;
//    for (i = 0; i < _N; i++) {
//        for (j = 0; j < _N; j++) {
//            //if (i,j) is a corner
//            if (corners[i][j]) {
//                //find r
//                for (int k = j + 1; k <= _N; k++) {
//                    if (corners[i][k]) {
//                        r = k;
//                        //find b
//                        for (int m = i + 1; m <= _N; m++) {
//                            if (corners[m][j]) {
//                                b = m;
//                                if (corners[b][r]) {
//                                    step++;
//                                    op.L = j;
//                                    op.R = r;
//                                    op.T = i;
//                                    op.B = b;
//                                    corners[op.T][op.L] ^= 1; // = !corners[op.T][op.L];
//                                    corners[op.T][op.R] ^= 1; // = !corners[op.T][op.R];
//                                    corners[op.B][op.L] ^= 1; // = !corners[op.B][op.L];
//                                    corners[op.B][op.R] ^= 1; // = !corners[op.B][op.R];
//                                    results.push(op);
//                                    return 1;
//                                }
//                            }
//
//                        }
//                    }
//                }
//            }
//        }
//    }
//    return 0;
//}
//                    
//bool find_tri()
//{
//    _XOR op;
//    int i, j, r, b;
//    for (i = 0; i < _N; i++) {
//        for (j = 0; j < _N; j++) {
//            if (corners[i][j]) {
//                for (int k = 0; k <= _N; k++) {
//                    if ((corners[i][k])&&(k != j)) {
//                        r = k;
//                        break;
//                    }
//                }
//                for (int m = 0; m <= _N; m++) {
//                    if ((corners[m][j])&&(m != i)) {
//                        b = m;
//                        break;
//                    }
//                }
//                step++;
//                op.L = (j<r)?j:r;
//                op.R = (j<r)?r:j;
//                op.T = (i<b)?i:b;
//                op.B = (i<b)?b:i;
//                corners[op.T][op.L] ^= 1; // = !corners[op.T][op.L];
//                corners[op.T][op.R] ^= 1; // = !corners[op.T][op.R];
//                corners[op.B][op.L] ^= 1; // = !corners[op.B][op.L];
//                corners[op.B][op.R] ^= 1; // = !corners[op.B][op.R];
//                results.push(op);
//                return 1;
//            }
//        }
//    }
//    return 0;
//}
//void all_white()
//{
//    step = 0;
//    
//    while (1) 
//    {
//        bool white = 1;
//        for (int i = 0; i <= _N; i++) {
//            for (int j = 0; j <= _N; j++) {
//                if (corners[i][j]) {
//                    white = 0;
//                    break;
//                }
//            }
//        }
//        if (white) {
//            break;
//        }
//        
//        bool square_found;
//        square_found = find_square();
//        if (!square_found) {
//            bool tri_found;
//            tri_found = find_tri();
//            if (!tri_found) {
//                cout<<"NO tri?"<<endl;
//            }
//        }
//    }
//        
//}
//    
//
//void output()
//{
//    cout<<step<<endl;
//    while (!results.empty()) {
//        cout<<results.front().L+1<<"\t"<<results.front().R<<"\t"<<results.front().T+1<<"\t"<<results.front().B<<endl;
//        results.pop();
//    }
//}
//
//void check()
//{
//    queue<_XOR> try_op;
//    try_op = results;
//    bool try_map[2001][2001];
//    
//    for (int i = 1; i <= _N; i++) {
//        for (int j = 1; j <= _N; j++) {
//            try_map[i][j] = 0;
//        }
//    }
//    
//    while (!try_op.empty()) {
//        for (int i = try_op.front().T+1; i <= try_op.front().B; i++) {
//            for (int j = try_op.front().L+1; j <= try_op.front().R; j++) {
//                try_map[i][j] = !try_map[i][j];
//            }
//        }
//        try_op.pop();
//    }
//    
//    bool try_flag;
//    try_flag = 0;
//    
//    for (int i = 1; i <= _N; i++) {
//        for (int j = 1; j <= _N; j++) {
//            if (try_map[i][j] != graph[i][j]) {
//                try_flag = 1;
//            }
//        }
//    }
//    
//    if (try_flag) {
//        cout<<"Error."<<endl;
//    }
//}