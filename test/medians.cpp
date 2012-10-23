//#include <iostream>
//#include <fstream>
//#include <cstring>
//#include <sstream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//vector<int> MAX_HEAP;
//vector<int> MIN_HEAP;
//
//int medians[10000];
//
//void input();
//
//void median(int,int);
//
//void output();
//
//bool min_comp (int,int);
//
//int main()
//{
//    input();
//    output();
//    return 0;
//}
//
//void input()
//{
//    fstream fin;
//    fin.open("/Users/zishirs/Documents/workspace/test/test/Median.txt");
//    string s;
//    for (int i = 0; i < 10000; i++) {
//        getline(fin,s);
//        stringstream str;
//        str << s;
//        int num;
//        str >> num;
//        if (i == 0) {
//            MAX_HEAP.push_back(num);
//            medians[0] = num;
//        }
//        if (i == 1) {
//            if (num >= MAX_HEAP.front()) {
//                MIN_HEAP.push_back(num);
//                medians[1] = num;
//            }
//            else {
//                medians[1] = num;
//                MIN_HEAP.push_back(MAX_HEAP.front());
//                MAX_HEAP.pop_back();
//                MAX_HEAP.push_back(num);
//            }
//        }
//        if (i > 1)
//            median(num,i);
//    }
//}
//
//void median(int num,int i)
//{
//    if (MAX_HEAP.size() == MIN_HEAP.size()) {
//        if ((num >= MAX_HEAP.front())&&(num <= MIN_HEAP.front())) {
//            medians[i] = num;
//            MAX_HEAP.push_back(num);
//            push_heap(MAX_HEAP.begin(), MAX_HEAP.end());
//        }
//        else {
//            if(num < MAX_HEAP.front()) {
//                medians[i] = MAX_HEAP.front();
//                MAX_HEAP.push_back(num);
//                push_heap(MAX_HEAP.begin(), MAX_HEAP.end());
//            }
//            else {
//                // num > MIN_HEAP.front()
//                medians[i] = MIN_HEAP.front();
//                MAX_HEAP.push_back(MIN_HEAP.front());
//                push_heap(MAX_HEAP.begin(), MAX_HEAP.end());
//                pop_heap(MIN_HEAP.begin(),MIN_HEAP.end(),min_comp);
//                MIN_HEAP.pop_back();
//                MIN_HEAP.push_back(num);
//                push_heap(MIN_HEAP.begin(),MIN_HEAP.end(),min_comp);
//            }
//        }
//    }
//    else {
//        //MAX_HEAP.size() = MIN_HEAP.size() + 1
//        if (num >= MAX_HEAP.front()) {
//            medians[i] = MAX_HEAP.front();
//            MIN_HEAP.push_back(num);
//            push_heap(MIN_HEAP.begin(),MIN_HEAP.end(),min_comp);
//        }
//        else {
//            // num < MAX_HEAP.front()
//            MIN_HEAP.push_back(MAX_HEAP.front());
//            push_heap(MIN_HEAP.begin(), MIN_HEAP.end(), min_comp);
//            pop_heap(MAX_HEAP.begin(), MAX_HEAP.end());
//            MAX_HEAP.pop_back();
//            MAX_HEAP.push_back(num);
//            push_heap(MAX_HEAP.begin(), MAX_HEAP.end());
//            medians[i] = MAX_HEAP.front();
//        }
//    }
//}
//
//bool min_comp (int i,int j) { return (i > j); }
//
//void output()
//{
//    int sum = 0;
//    for (int i = 0; i < 10000; i++) {
//        //cout<<medians[i]<<endl;
//        sum += medians[i];
//    }
//    
//    sum %= 10000;
//    
//    cout << sum <<endl;
//}