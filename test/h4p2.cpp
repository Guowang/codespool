//// CSE20232/60732 homework 4 problem 2 by Guowang Li
//#include <iostream>
//#include <math.h>
//
//using namespace std;
//
//int get_gcd(int, int);
//
//bool is_prime(int);
//
//int main (){
//	//test get_gcd()
//    
//    int a, b, gcd;
//    
//    cout<<"Input two integers: "<<endl;
//    cin>>a>>b;
//    
//    gcd = get_gcd(a, b);
//    cout<<"The greatest common divider is: "<<gcd<<endl;
//    
//    //test is_prime();
//    int x;
//    cout<<"Input an integer:"<<endl;
//    cin>>x;
//    
//    if (is_prime(x)) 
//        cout<<"It is prime."<<endl;
//    else
//        cout<<"It is not prime."<<endl;
//    
//	return 0;
//}
//
//int get_gcd(int x, int y)
//{
//    if (x == y) 
//    {
//        return x;
//    }
//    else
//    {
//        int smaller = x;
//        if (smaller > y)
//            smaller = y;
//        return get_gcd(smaller, abs(x - y));
//    }
//}
//
//bool is_prime(int x)
//{
//    if ((x == 1)||(x == 2))
//        return 1;
//    else
//    {
//        int max = sqrt(x);
//        for (int i = 2; i <= max; i++) 
//        {
//            if (x % i == 0) 
//            {
//                return 0;
//            }
//        }
//        return 1;
//    }
//}