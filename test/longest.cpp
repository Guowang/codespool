//#include <iostream>
//#include <stdlib.h>
//
//using namespace std;
//
//int main()
//{
//	double arr[]={0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
//	//0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15
//	int n = sizeof(arr)/sizeof(arr[0]), L=1, lastindex=0,i,j;
//	int dp[16]={1},prev[16]={-1};
//
//	for (i=1;i<n;++i)
//	{
//		dp[i]=1;
//		for(j=0;j<i;++j)
//		{
//			if ((1+dp[j]>dp[i]) && (arr[j]<arr[i]))
//			{
//				dp[i]=1+dp[j];
//				prev[i]=j;
//			}
//			if(dp[i]>L)
//			{
//				L=dp[i];
//				lastindex=i;
//			}
//		}
//	}
//
//	cout << "L: "<< L << endl;
//	int index = lastindex;
//	for (int k=0;k<L;++k)
//	{
//		cout << arr[index] << endl;
//		index = prev[index];
//	}
//
//	int length, low, high, mid;
//	int M[17] = {-1}, P[17] = {-1};
//	length = 1;
//	M[1] = 0;
//
//
//	for (i=1;i<n;++i)
//	{
//		low = 0;
//		high = length;
//		
//		if (arr[M[high]] < arr[i])
//		{
//			j = high;
//		}
//		else
//		{
//			while ((high - low) > 1)
//			{
//				mid = (low + high)/2;
//				if (arr[M[mid]] < arr[i])
//					low = mid;
//				else
//					high = mid;
//			}
//			j = low;
//		}
//
//		P[i] = M[j];
//		if ((j == length) || (arr[i] < arr[M[j+1]]))
//		{
//			M[j+1]=i;
//			if (length < j+1)
//				length  = j+1;
//		}
//
//	}
//	index = M[length];
//	cout << "M: " << length << endl;
//	//cout << M[6] << endl;
//	for (int k=0;k<length;++k)
//	{
//		cout << arr[index] << endl;
//		index = P[index];
//	}
//	
//	return 0;
//}


//#include <vector>
//using namespace std;
//
///* Finds longest strictly increasing subsequence. O(n log k) algorithm. */
//void find_lis(vector<int> &a, vector<int> &b)
//{
//  vector<int> p(a.size());
//  int u, v;
//
//  if (a.empty()) return;
//
//  b.push_back(0);
//
//  for (size_t i = 1; i < a.size(); i++) {
//      if (a[b.back()] < a[i]) {
//          p[i] = b.back();
//          b.push_back(i);
//          continue;
//      }
//
//      for (u = 0, v = b.size()-1; u < v;) {
//          int c = (u + v) / 2;
//          if (a[b[c]] < a[i]) u=c+1; else v=c;
//      }
//
//      if (a[i] < a[b[u]]) {
//          if (u > 0) p[i] = b[u-1];
//          b[u] = i;
//      }   
//  }
//
//  for (u = b.size(), v = b.back(); u--; v = p[v]) b[u] = v;
//}
//
///* Example of usage: */
//#include <cstdio>
//int main()
//{
//  int a[] = {5, 1, 9, 3, 8, 11, 4, 5, 6, 4, 19, 7, 1, 7 };
//  vector<int> seq(a, a+sizeof(a)/sizeof(a[0]));
//  vector<int> lis;
//        find_lis(seq, lis);
//
//  for (size_t i = 0; i < lis.size(); i++)
//      printf("%d ", seq[lis[i]]);
//        printf("\n");    
//
//  system("pause");
//  return 0;
//}