//#include <iostream>
//#include <fstream>
//#include <cstring>
//#include <sstream>
//#include <tr1/unordered_map>
//
//using namespace std;
//
//tr1::unordered_map<int, bool> hash_map;
//
//int count_num = 0;
//
//
//void input_map();
//bool valid[1501];
//int count_t;
//void count_sum();
//
//int main ()
//{
//    input_map();
//    count_sum();
//    cout<<count_t<<endl;
//    return 0;
//}
//
//void input_map()
//{
//    fstream fin;
//    string s;
//    fin.open("/Users/zishirs/Documents/workspace/test/test/HashInt.txt");
//    while (fin.good()) {
//        getline(fin,s);
//        stringstream str;
//        str << s;
//        int num;
//        str >> num;
//        if (num < 4001) {
//            tr1::unordered_map<int, bool>::iterator it;
//            it = hash_map.find(num);
//            if (it != hash_map.end()) {
//                it->second = 1;
//            }
//            else {
//                hash_map.insert(pair<int,bool>(num,0));
//            }
//            //cout<<num<<endl;
//        }
//        
//    }
//    fin.close();
//    //cout<<hash_map.size()<<endl;
//}
//
//void count_sum()
//{
//    int i = 0;
//    for (int k = 2500; k <= 4000; k++) {
//        //cout<<k<<endl;
//        valid[i] = 0;
//        for (tr1::unordered_map<int, bool>::iterator it = hash_map.begin(); it != hash_map.end(); it++) {
//            if (it->first < k/2) {
//                tr1::unordered_map<int, bool>::iterator fit;
//                fit = hash_map.find(k - it->first);
//                if (fit != hash_map.end()) {
//                    if ((k - it->first) == it->first) {
//                        if (it->second) {
//                            count_num++;
//                            valid[i] = 1;
//                            //cout<<it->first<<"\t"<<fit->first<<endl;
//                        }
//                    }
//                    else {
//                        count_num++;
//                        valid[i] = 1;
//                        //cout<<it->first<<"\t"<<fit->first<<endl;
//                    }
//                }
//
//            }
//        }
//        i++;
//    }
//    
//    count_t = 0;
//    for (int i = 0; i < 1501; i++) {
//        if (valid[i]) {
//            count_t++;
//        }
//    }
//}