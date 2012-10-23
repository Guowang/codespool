//#include <iostream>
//#include <stdlib.h>
//#include <cmath>
//
//using namespace std;
//
//struct node
//{
//    int low;
//    int high;
//    double sum;
//};
//
//node crossing_subarray(double A[], int low, int mid, int high)
//{
//    int left_most,right_most,i,j;
//    double left_sum,right_sum,sum;
//    node node1;
//    
//    sum=A[mid];
//    left_sum=A[mid];
//    left_most=mid;
//    for (i=mid-1;i>=low;i--)
//    {
//        sum=sum+A[i];
//        if(sum>left_sum)
//        {
//            left_sum=sum;
//            left_most=i;
//        }
//    }
//    
//    sum=0;
//    right_sum=0;
//    right_most=mid;
//    for (j=mid+1;j<=high;j++)
//    {
//        sum=sum+A[j];
//        if(sum>right_sum)
//        {
//            right_sum=sum;
//            right_most=j;
//        }
//    }
//    
//    sum=left_sum+right_sum;
//    
//    node1.low = left_most;
//    node1.high = right_most;
//    node1.sum = sum;
//    
//    return node1;
//}
//
//node find_max_subarray(double A[], int low, int high)
//{
//    int left_low,right_low,crossing_low,left_high,right_high,crossing_high,mid;
//    double left_sum,right_sum,crossing_sum,sum;
//    node node1,left,right,crossing;
//    node1.low = low;
//    node1.high = high;
//    node1.sum = A[low];
//    
//    if (low==high)
//    {
//        return node1;
//    }
//    else 
//    {
//        mid=(low+high)/2;
//        left = find_max_subarray(A,low,mid);
//        right = find_max_subarray(A,mid+1,high);
//        crossing = crossing_subarray(A,low,mid,high);
//        
//        if ((left.sum > right.sum) && (left.sum > crossing.sum))
//            return left;
//        else 
//            if (right.sum > crossing.sum)
//                return right;
//            else
//                return crossing;
//    }
//    
//}
//
//
//int main()
//{
//    double A[]={13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-2215,-4,7};
//    int n=sizeof(A)/sizeof(A[0]);
//    int low=0,high=n;
//    node sum;
//    
//    
//    sum=find_max_subarray(A,low,high);
//    
//    cout<<sum.low<<endl;
//    cout<<sum.high<<endl;
//    cout<<sum.sum<<endl;
//    
//    return 0;
//}