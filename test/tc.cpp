#define __test__tc__
#ifndef __test__tc__

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>


//#include <tr1/unordered_map>
//#include <tr1/unordered_set>
#include <assert.h>

using namespace std;

#define ll long long

class SwappingDigits{
public:
    string minNumber(string);
};

int main() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        cout<<"Case #"<<index<<": "<<endl;
    }
    return 0;
}

#endif