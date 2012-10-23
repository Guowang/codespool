//#include <iostream>
//
//using namespace std;
//
//template <class T>
//void partition(T *, int, T);
//
//int main() {
//    
//    int arr[] = {7,0,2,3,1,2,5,9,6,2,4};
//    int len = sizeof(arr)/sizeof(arr[0]);
//
//    partition(arr, len, 3);
//    
//    for (int i = 0; i < len; i++) {
//        cout<< arr[i] << " ";
//    }
//    cout<<endl;
//    
//    return 0;
//}
//
//template <class T>
//void partition(T* arr, int n, T key) {
//    
//    int less = -1, cur = 0, more = n;
//    T temp;
//    
//    while (cur < more) {
//        if (arr[cur] < key) {
//            temp = arr[cur];
//            arr[cur++] = arr[++less];
//            arr[less] = temp;
//        }
//        else if (arr[cur] > key) {
//            temp = arr[cur];
//            arr[cur] = arr[--more];
//            arr[more] = temp;
//        }
//        else if (arr[cur] == key) {
//            ++cur;
//        }
//    }
//}