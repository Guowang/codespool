//#include <iostream>
//#include <algorithm>
//#include <time.h>
//
//using namespace std;
//
//int main()
//{
//    const int N = 100000000;
//    const int K = 100;
//    
//    cout<<"generating numbers..."<<flush;
//    int* v = new int[N];
//    int queue[K];
//    for (int i=0; i<N; ++i)
//        v[i] = mrand48();
//    cout<<"done\n";
//    
//    cout<<"heap..."<<flush;
//    clock_t t0 = clock();
//    {
//        int size = 0;
//        for (int i=0; i<N; ++i)
//        {
//            int x = v[i];
//            int index;
//            if (size == 0)
//            {
//                index = 0;
//            } else if (size < 100)
//            {
//                index = size++;
//                while (index > 0)
//                {
//                    int parent = (index - 1) >> 1;
//                    int e = queue[parent];
//                    if (x >= e)
//                        break;
//                    queue[index] = e;
//                    index = parent;
//                }
//            } else
//            {
//                index = 0;
//                int half = size >> 1;
//                while (index < half)
//                {
//                    int child = (index << 1) + 1;
//                    int c = queue[child];
//                    int right = child + 1;
//                    if (right < size && c > queue[right])
//                        c = queue[child = right];
//                    if (x - c <= 0)
//                        break;
//                    queue[index] = c;
//                    index = child;
//                }
//            }
//            queue[index] = x;
//        }
//    }
//    cout<<clock()-t0<<endl;
//    sort(queue, queue+K);
//    for (int i=0; i<K; ++i)
//        cout<<queue[i]<<' ';
//    cout<<endl;
//    
//    cout<<"silly...";
//    t0=clock();
//    {
//        copy(v, v+K, queue);
//        sort(queue, queue+K);
//        for (int i=K; i<N; ++i)
//            if (v[i] > queue[0]) {
//                queue[0] = v[i];
//                sort(queue, queue+K);
//            }
//    }
//    cout<<clock()-t0<<endl;
//    sort(queue, queue+K);
//    for (int i=0; i<K; ++i)
//        cout<<queue[i]<<' ';
//    cout<<endl;
//    
//    cout<<"sort..."<<flush;
//    t0=clock();
//    sort(v, v+N);
//    cout<<endl;
//    cout<<"Kth="<<v[N-K]<<endl;
//    cout<<clock()-t0<<endl;
//    for (int i=N-K; i<N; ++i)
//        cout<<v[i]<<' ';
//    cout<<endl;    
//}
