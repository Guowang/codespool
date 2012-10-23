//#include <iostream>
//#include <stdlib.h>
//using namespace std; 
//
//void print(int s[], int n);
//int f(int n, int k, int d[]);
//void comb(int d[],int count[],int k,int change);
//
//
//void print(int s[], int n)
//{
//	if (n > 0)
//	{
//		print(s, n-s[n]);
//		cout << s[n] << endl;
//	}
//}
//
//int f(int n, int k, int d[])
//{
//	if ((k < 0) || (n < 0))
//		return 0;
//	else if (n == 0)
//		return 1;
//	else
//		return f(n,k - 1,d) + f(n - d[k],k,d);
//}
//
//void comb(int d[],int count[],int k,int change)
//{
//	if (k == 0)
//	{
//		if(change%d[0]==0)
//		{
//			count[0]=change/d[0];
//			cout << "25: " << count[3] << " 10: " << count[2] << " 5: " << count[1] << " 1: " << count[0] << endl;
//		}
//	}
//	else
//	{
//		for (int i=0;i<=change/d[k];++i)
//		{
//			count[k]=i;
//			comb(d,count,k-1,change-d[k]*i);
//		}
//
//	}
//}
//
//int main()
//{
//	const int n = 400;
//	int s[n];
//	int c[n];
//	const int k = 4;
//	int d[k]={1,5,10,25};
//	int change, p;
//	int i;
//    std::cin >> change;
//
//	c[0] = 0;
//	s[0] = 0;
//
//	for (p = 1;p <= change; ++p)
//	{
//		c[p] = p;
//		s[p] = 1;
//		for (i = 0; i < k; ++i)
//		{
//			if (d[i] <= p)
//			{
//				if ((1 + c[p - d[i]]) < c[p])
//				{
//					c[p] = 1 + c[p - d[i]];
//					s[p] = d[i];
//				}
//			}
//		}
//	}
//
//	cout << "Min no. of coins: " << c[change] << endl;
//	cout << "It is: " << endl;
//	print(s, change);
//
//	int combos = 0;
//	 for (int q = 0; q <= change / 25; q++)
//    {
//    	int total_less_q = change - q * 25;
//    	for (int d = 0; d <= total_less_q / 10; d++)
//    	{
//    		int total_less_q_d = total_less_q - d * 10;
//    		for (int n = 0; n <= total_less_q_d / 5; n++)
//    		{
//    			int p = total_less_q_d - n * 5;
//				cout << "25: " << q << " 10: " << d << " 5: " << n << " 1: " << p << endl;
//    			combos++;
//    		}
//    	}
//    }
//	cout << combos << endl;
//	//cout << c[change] << endl;
//	//cout << s[change] << endl;
//	//print(s, change);
//
//	cout << "Verification: " << f(change,k-1,d) << endl;
//
//	int count[4] = {0};
//	comb(d,count,k-1,change);
//
//	return 0;
//}