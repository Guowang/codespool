//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <string.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <tr1/unordered_map>
//
//using namespace std;
//
//struct Node{
//public:
//    int val;
//    int a;
//    int b;
//    Node(int value, int aval, int bval) : val(value), a(aval), b(bval) {};
//};
//
//vector<vector<int> > fourSum(vector<int>&, int);
//
//bool isValid(vector<int>, tr1::unordered_map<int, int>);
//
//string getString(vector<int>);
//
//int main() {
//    //5,5,3,5,1,-5,1,-2
//    //-1,0,1,2,-1,-4
//    int A[] = {-1,0,1,2,-1,-4};
//    int len = sizeof(A) / sizeof(A[0]);
//    vector<int> v(A, A + len);
//    int target = -1;
//    vector<vector<int> > results = fourSum(v, target);
//    for (vector<vector<int> >::iterator it = results.begin(); it != results.end(); ++it) {
//        for (vector<int>::iterator intit = it->begin(); intit != it->end(); ++intit) 
//            cout<<*intit<<" ";
//        cout<<endl;
//    }
//    return 0;
//}
//
//vector<vector<int> > fourSum(vector<int> &num, int target) {
//    
//    vector<vector<int> > results;
//    tr1::unordered_map<int, int> numMap;
//    tr1::unordered_map<int, vector<Node> > n2SumMap;
//    tr1::unordered_map<string, int> resultMap;
//    int mid = target / 2;
//    
//    if (num.size() < 4) return results;
//    
//    sort(num.begin(), num.end());
//    
//    for (vector<int>::iterator i_it = num.begin(); i_it != num.end(); ++i_it) {
//        tr1::unordered_map<int, int>::iterator fit = numMap.find(*i_it);
//        if (fit == numMap.end())
//            numMap.insert(make_pair(*i_it, 1));
//        else
//            fit->second++;
//        
//        vector<int>::iterator kit = i_it;
//        kit++;
//        for (vector<int>::iterator j_it = kit; j_it != num.end(); ++j_it) {
//            int sum = *i_it + *j_it;
//            Node node(sum, *i_it, *j_it);
//            tr1::unordered_map<int, vector<Node> >::iterator m_it = n2SumMap.find(sum);
//            if (m_it == n2SumMap.end()) {
//                vector<Node> nodeV;
//                nodeV.push_back(node);
//                n2SumMap.insert(make_pair(sum, nodeV));
//            }
//            else {
//                bool flag = false;
//                for (vector<Node>::iterator v_it = m_it->second.begin(); v_it != m_it->second.end(); ++v_it) {
//                    if (v_it->a == *i_it) {
//                        flag = true;
//                        break;
//                    }
//                }
//                if (!flag)
//                    m_it->second.push_back(node);
//            }
//        }
//            
//    }
//    
//    int sum = 0, count = 0;
//    for (vector<int>::reverse_iterator rit = num.rbegin(); rit != num.rend(); ++rit) {
//        sum += *rit;
//        count++;
//        if (count == 4)
//            break;
//    }
//    if (sum < target) return results;
//    
//    for (tr1::unordered_map<int, vector<Node> >::iterator m_it = n2SumMap.begin(); m_it != n2SumMap.end(); ++m_it)
//        if (m_it->first <= mid) {
//            int r = target - m_it->first;
//            tr1::unordered_map<int, vector<Node> >::iterator f_it = n2SumMap.find(r);
//            if (f_it != n2SumMap.end()) {
//                for (vector<Node>::iterator i_it = m_it->second.begin(); i_it != m_it->second.end(); ++i_it)
//                    for (vector<Node>::iterator j_it = f_it->second.begin(); j_it != f_it->second.end(); ++j_it) {
//                        vector<int> s;
//                        s.push_back(i_it->a);
//                        s.push_back(i_it->b);
//                        s.push_back(j_it->a);
//                        s.push_back(j_it->b);
//                        sort(s.begin(), s.end());
//                        if (isValid(s, numMap)) {
//                            /*
//                            string str = getString(s);
//                            tr1::unordered_map<string, int>::iterator r_it = resultMap.find(str);
//                            if (r_it == resultMap.end()) {
//                                results.push_back(s);
//                                resultMap.insert(make_pair(str, 0)); 
//                            }
//                             */
//                            if (find(results.begin(), results.end(), s) == results.end())
//                                results.push_back(s);
//                        }
//                    }
//
//            }
//        }
//    return results;
//}
//
//bool isValid(vector<int> v, tr1::unordered_map<int, int> numMap) {
//    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
//        int count = 1;
//        for (vector<int>::iterator j_it = it + 1; j_it != v.end(); ++j_it)
//            if (*it == *j_it)
//                count++;
//        tr1::unordered_map<int, int>::iterator m_it = numMap.find(*it);
//        if (m_it->second < count)
//            return false;
//    }
//    return true;
//}
//
//string getString(vector<int> v) {
//    string s = "";
//    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
//        int n = *it;
//        if (n == 0)
//            s = s + '0';
//        else {
//            if (n < 0) {
//                s = s + '-';
//                n = -n;
//            }
//            while (n > 0) {
//                char c = '0' + n % 10;
//                s = s + c;
//                n /= 10;
//            }
//        }
//        s = s + ',';
//    }
//    return s;
//}