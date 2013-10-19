/*
#include <iostream>
#include <vector>

using namespace std;

void addOne(vector<bool>&, bool&);

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int len = sizeof(arr) / sizeof(arr[0]);
    vector<int> v(arr, arr + len);
    bool flag = true;
    vector<bool> num(len, false);
    unsigned int i = 0;
    while (flag) {
        vector<int> out;
        addOne(num, flag);
        cout<<i++<<": ";
        for (int j = 0; j < len; j++)
            if (num[j])
                cout<<arr[j]<<" ";
        cout<<endl;
    }
    return 0;
}

void addOne(vector<bool>& num, bool& flag){
    bool car = true;
    unsigned int len = num.size();
    int i;
    for (i = len - 1; i >= 0; i--) {
        bool temp = num[i];
        num[i] = num[i] ^ car;
        car = temp & car;
        if (!car)
            break;
    }
    if (car && i == -1)
        flag = false;
}
*/