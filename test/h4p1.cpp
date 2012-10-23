////CSE20232/60732 homework 4 problem 1 by Guowang Li
//#define _USE_MATH_DEFINES
//#include <iostream>
//#include <math.h>
//
//using namespace std;
//
//void find_polar(double, double, double &, double &);
//
//int main (){
//	double x, y, rho, theta;
//
//	cout << "Input the x coordinate x: " << endl;
//	cin >> x;
//	cout << "Input the y coordinate y:" << endl;
//	cin >> y;
//	
//    find_polar(x, y, rho, theta);
//	
//	return 0;
//}
//
//void find_polar (double x, double y, double & rho, double & theta)
//{
//    rho = sqrt(y*y + x*x);
//    
//	if (x == 0)
//	{
//		if (y == 0)
//		{
//			theta = 0;
//			cout << "The point is at the origin." << endl;
//			cout << "The polar coordinates are: r = " << rho << " and theta ([0, 360) in degree) = " << theta << endl;
//		}
//		else if (y > 0)
//		{
//			theta = 90;
//			cout << "The point is at +y axis." << endl;
//			cout << "The polar coordinates are: r = " << rho << " and theta ([0, 360) in degree) = " << theta << endl;
//		}
//		else 
//		{
//			theta = 270;
//			cout << "The point is at -y axis." << endl;
//			cout << "The polar coordinates are: r = " << rho << " and theta ([0, 360) in degree) = " << theta << endl;
//		}
//	}
//    
//	else
//	{
//		if ((x > 0) && (y == 0))
//		{
//			theta = 0;
//			cout << "The point is at +x axis." << endl;
//			cout << "The polar coordinates are: r = " << rho << " and theta ([0, 360) in degree) = " << theta << endl;
//		}
//		else if ((x > 0) && (y > 0))
//		{
//			theta = atan(y / x) / M_PI *180;
//			cout << "The point is in the first quadrant." << endl;
//			cout << "The polar coordinates are: r = " << rho << " and theta ([0, 360) in degree) = " << theta << endl;
//            
//		}
//		else if ((x > 0) && (y < 0))
//		{
//			theta = (2 * M_PI + atan(y / x)) / M_PI *180;
//			cout << "The point is in the fouth quadrant." << endl;
//			cout << "The polar coordinates are: r = " << rho << " and theta ([0, 360) in degree) = " << theta << endl;
//		}
//		else if ((x < 0) && (y == 0))
//		{
//			theta = 180;
//			cout << "The point is at -x axis." << endl;
//			cout << "The polar coordinates are: r = " << rho << " and theta ([0, 360) in degree) = " << theta << endl;
//		}
//		else if ((x < 0) && (y > 0))
//		{
//			theta = (M_PI + atan(y / x)) / M_PI *180;
//			cout << "The point is in the second quadrant." << endl;
//			cout << "The polar coordinates are: r = " << rho << " and theta ([0, 360) in degree) = " << theta << endl;
//		}
//		else
//		{
//			theta = (M_PI + atan(y / x)) / M_PI *180;
//			cout << "The point is in the third quadrant." << endl;
//			cout << "The polar coordinates are: r = " << rho << " and theta ([0, 360) in degree) = " << theta << endl;
//		}
//	}
//}