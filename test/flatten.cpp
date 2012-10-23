//#include <iostream>
//#include <queue>
//
//using namespace std;
//
//struct move
//{
//    int p; // index
//    int m; // num of moved coins
//};
//
//int _N; // num of columns
//int avg; // goal
//int min_step = 0; // step required
//int c[201]; // columns
//int diff[201]; // difference in num of coins from avg
//int opt[201]; // sum of m for each p
//queue<move> results; // store move
//
//void input();
//void flatten();
//void output();
//
//int main()
//{
//    input();
//    flatten();
//    output();
//    
//    return 0;
//}
//
//void input()
//{
//    int sum = 0;
//    cin >> _N;
//    for (int i = 1; i <= _N; i++) 
//    {
//        cin >> c[i];
//        sum += c[i];
//    }
//    avg = sum / _N;
//    for (int i = 1; i <= _N; i++) 
//    {
//        diff[i] = c[i] - avg;
//    }
//    
//}
//
//void flatten()
//{
//    // calculate opt[i]: one solution with opt[1] = 0
//    opt[1] = 0;
//    opt[2] = -diff[1];
//    int min_opt;
//    min_opt = (opt[1] < opt[2])?opt[1]:opt[2];
//    
//    for (int i = 2; i < _N; i++) 
//    {
//        opt[i+1] = -diff[i] - opt[i-1] + 2*opt[i];
//        if (opt[i+1] < min_opt) 
//        {
//            min_opt = opt[i+1];
//        }
//    }
//    // make sure opt[i] >= 0
//    for (int i = 1; i <= _N; i++) 
//    {
//        opt[i] -= min_opt;
//        cout<<opt[i]<<endl;
//    }
//    // greedy method
//    while (1) 
//    {
//        //check whether finished
//        bool flag = 0;
//        for (int i = 1; i <= _N; i++) 
//        {
//            if (c[i] != avg) 
//            {
//                flag = 1;
//            }
//        }
//        if (flag == 0)
//            break;
//        // max_m: maximum num of coins to move; 
//        // max_p: where the max_m move is
//        int max_m, max_p;
//        int temp_m, temp_p;
//        
//        if ((c[1] >= opt[1])&&(c[1] >= 1))
//        {
//            temp_m = opt[1];
//            max_m = opt[1];
//            temp_p = 1;
//            max_p = 1;
//        }
//        else
//        {
//            temp_m = c[1];
//            max_m = c[1];
//            temp_p = 1;
//            max_p = 1;
//        }
//        
//        if ((c[_N] >= opt[_N])&&(c[_N] >= 1))
//        {
//            temp_m = opt[_N];
//        }
//        else
//        {
//            temp_m = c[_N];
//        }
//        if (temp_m >= max_m) 
//        {
//            if (temp_m > max_m)
//            {
//                max_m = temp_m;
//                max_p = _N;
//            }
//            else
//            {
//                if (opt[_N] > opt[temp_p]) 
//                {
//                    max_m = temp_m;
//                    max_p = _N;
//                }
//            }
//        }
//        for (int i = 2; i < _N; i++) 
//        {
//            if ((c[i] >= 2*opt[i])&&(c[i] >= 2))
//            {
//                temp_m = opt[i];
//                temp_p = i;
//            }
//            else
//            {
//                temp_m = c[i]/2;
//                temp_p = i;
//            }
//            if (temp_m >= max_m) 
//            {
//                if (temp_m > max_m) 
//                {
//                    max_m = temp_m;
//                    max_p = i;
//                }
//                else
//                {
//                    if (opt[i] > opt[max_p]) 
//                    {
//                        max_m = temp_m;
//                        max_p = i;
//                    }
//                }
//                
//            }
//        }
//        
//        // update c[i] after one move
//        if (max_p == 1) 
//        {
//            c[1] -= max_m;
//            c[2] += max_m;
//        }
//        else
//        {
//            if (max_p == _N) 
//            {
//                c[_N] -= max_m;
//                c[_N - 1] += max_m;
//            }
//            else
//            {
//                c[max_p] -= 2*max_m;
//                c[max_p - 1] += max_m;
//                c[max_p + 1] += max_m;
//            }
//        }
//        //update opt[]
//        opt[max_p] -= max_m;
//        
//        // push this move to queue
//        move move_1;
//        move_1.p = max_p;
//        move_1.m = max_m;
//        results.push(move_1);
//        
//        min_step++;
//    }
//}
//
//void output()
//{
//    cout<<min_step<<endl;
//    while (!results.empty()) 
//    {
//        cout<<results.front().p<<"\t"<<results.front().m<<endl;
//        results.pop();
//    }
//}

//#include <iostream>
//#define 	MAX_LENGTH	201
//#define 	MAX_PATH	10001
//using namespace std;
//
//short a[MAX_LENGTH]; 		/* holds data 			*/
//long v[MAX_LENGTH];		/* holds no of presses 		*/
//short M;			/* no. of buckets 		*/
//short N;			/* height 			*/
//short nze;			/* number of non-zero entries 	*/
//short step = 0;                	/* holds no. of steps so far 	*/
//short ent[MAX_PATH];
//long nofp[MAX_PATH];
//short nfp;			/* bool : nothing can be fully  *
//                     * pressed			*/
//
//void get_input()
//{
//    register short i;
//    long total = 0;
////    FILE *ifp;
////    ifp = f_fopen("FLAT.INP", "r");
////    fscanf(ifp,"%hd\n", &M);
//    cin >> M;
//    for (i = 1; i <= M; i++) { cin >> a[i]; total += a[i]; }
//    N = total / M;
////    fclose(ifp);
//}
//
//void press_info()
//{
//    long min = 0;
//    register short i;
//    if ((N - a[1]) > 0)  {
//        v[2] = N - a[1];
//        v[1] = 0;
//    }
//    else {
//        v[1] = a[1] - N;
//        v[2] = 0;
//    }
//    for (i = 2; i < M; i++) {
//        v[i+1] = N - a[i] - v[i-1] + (2 * v[i]) ;
//        if (v[i+1] < min) min = v[i+1];
//    }
//    if (min < 0) 					
//        for (i = 1 ; i <= M; i++) v[i] -= min;
//    for (i = 2; i <= M-1; i++) v[i] *= 2;
//    for (i = 1; i <= M; i++) if (v[i]) nze++;
//}
//
//void write_it(short e, long n)
//{
//    ent[++step] = e;
//    nofp[step] = n;
//}
//
//short MPC(short e) 			/* maximum pressable chip */
//{
//    if ((e == 1) || (e == M)) return a[e];
//    return (a[e] % 2) ? a[e] - 1 : a[e];
//}
//
//short eval(short e)
//{
//    if (e == 1) return ((5 * a[1]) / 3);
//    else if (e == M) return ((5 * a[M]) / 3);
//    else return MPC(e);
//}
//
//short eval2(short e)
//{
//    if (e == 1) return ( v[2] ? 4 * a[1] : a[1] );
//    else if (e == M) return ( v[M-1] ? 4 * a[M] : a[M] );
//    else {
//        short carpan = 0;
//        carpan += ( v[e-1] ? 1 :0 );
//        carpan += ( v[e+1] ? 1 :0 );
//        return (MPC(e) * (2 + carpan) / 2);
//    }
//}
//
//short find_2nd() 			/* assumes no pile can be fully pressed */
//{
//    register short i;
//    short max = 0, ent = 0;
//    if ((a[1] && v[1]) && (((a[1] + a[2]) > v[2]) && v[2])) { ent = 1; max = a[1];}
//    for (i = 2; i < M ; i++) 
//        if (a[i] && v[i])
//            if (((((MPC(i) / 2) + a[i - 1]) >= v[i - 1]) && v[i - 1]) || \
//                ((((MPC(i) / 2) + a[i + 1]) >= v[i + 1]) && v[i + 1])) 
//                if (MPC(i) > max) {ent = i; max = MPC(i); }
//    if ((a[M] && v[M]) && (((a[M] + a[M - 1]) > v[M - 1]) && v[M - 1]))
//        if (a[M] > max) return M;
//    return ent;
//}
//
//
//void flatten()
//{
//    register short i;
//    short value, entry, no_chip, temp;
//    //FILE *sol;
//    while (nze > 0) {
//        value = 0;
//        nfp = 0;
//        for (i = 1; i <= M; i++) {
//            if (a[i] && v[i]) {
//                if (a[i] >= v[i]) {
//                    entry = i;
//                    no_chip = v[i];
//                    --nze;
//                    nfp = 1;
//                    break;
//                }
//                if (eval(i) > value) {
//                    value = eval(i);
//                    entry = i;
//                    no_chip = MPC(i);
//                }
//                if (eval(i) == value)
//                    if (eval2(i) > eval2(entry)) {
//                        entry = i;
//                        no_chip = MPC(i);
//                    }
//            }
//        }
//        if (!nfp) 
//            if ((temp = find_2nd())) {
//                entry = temp;
//                no_chip = MPC(entry);
//            }
//        v[entry] -= no_chip;
//        a[entry] -= no_chip;
//        if (entry == M) { a[entry - 1] += no_chip;  write_it(entry,no_chip);}
//        else if (entry == 1) { a[2] += no_chip; write_it(entry,no_chip);}
//        else {
//            a[entry - 1] += (no_chip / 2);
//            a[entry + 1] += (no_chip / 2);
//            write_it(entry,no_chip / 2);
//        }
//    }
////    sol = f_fopen("SOLUTION.TXT","w");
////    fprintf(sol,"%hd\n", step);
////    printf("%hd\n", step);
////    fclose(sol);
//    
//}
//
//void putitout()
//{
//    short i;
////    FILE *ofp;
////    ofp = f_fopen("FLAT.OUT","w");
////    fprintf(ofp,"%hd\n", step);
//    cout<<step<<endl;
//    for (i = 1; i <= step; i++)
//        cout<<ent[i]<<"\t"<<nofp[i]<<endl;
//}
//
//
//int main()
//{
//    get_input();
//    press_info();
//    flatten();
//    putitout();
//    return 0;
//}