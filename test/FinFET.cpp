#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

double f(double x)
{
	double y;
	double k=1.3806503e-23, q=1.60217646e-19, T=300, ni=1e10*1e6, eps_0=8.8541878e-12, eps_GaN=8.9*eps_0, eps_ox=9*eps_0, kT_q=k*T/q;
	double T_GaN=20e-9, Lg=100e-9, t_ox=4e-9, Cox=eps_ox/t_ox, Vgs=0.2, Vds=0.1, Vfb=0, mu=500/1e4, Ny=5;

	double Vch(Ny);

	for (int i = 0; i < Ny; i++) 
	{
		Vch(i)=Vds*(i+1)/Ny;
	}
	y = log(x)-log(cos(x))-(Vgs-Vfb-Vch(iy))/(2*kT_q)+log(2/T_GaN*pow((2*eps_GaN*kT_q/ni),0.5))+2*eps_GaN/T_GaN/Cox*x*tan(x));
	return y;
}

int main(){

	double k=1.3806503e-23, q=1.60217646e-19, T=300, ni=1e10*1e6, eps_0=8.8541878e-12, eps_GaN=8.9*eps_0, eps_ox=9*eps_0, kT_q=k*T/q;
	double T_GaN=20e-9, Lg=100e-9, t_ox=4e-9, Cox=eps_ox/t_ox, Vgs=0.2, Vds=0, Vfb=0, mu=500/1e4, Ny=5;

	double Vch(Ny), phi_0(Ny),phi_s(Ny),beta(Ny),Q_(Ny);

	for (int i = 0; i < Ny; i++) 
	{
		Vch(i)=Vds*(i+1)/Ny;
	}

	//for (int iy = 0; iy < Ny; iy++) 
	//{
	//	double a,b,c,x;
	//	a = 1e-2;
	//	b = 1e-3;
	//	c = (a + b)/2;
	//	x = c;

	//	while ( abs(f(x)) > 1e-10)
	//	{		
	//		if (f(a) * f(c) < 0) 
	//			b = c;
	//		else
	//			a = c;
	//		c = (a + b) / 2;
	//		x = c;
	//	}
	//	phi_0(iy)=kT_q*pow(log((2*x/T_GaN),2*2)*eps_GaN/kT_q/q/ni)+Vch(iy);
	//	phi_s(iy)=2*kT_q*(log(beta(iy)-log(cos(x))))+log(2/T_GaN*pow((2*eps_GaN*kT_q/ni),0.5));
	//}

	//double Q_s=Cox*(Vgs-Vfb-phi_s(0));
	//double f_s=pow(Q_s,2)/2/Cox+2*kT_q*Q_s-5*pow(kT_q,2)*eps_GaN/T_GaN*log(Q_s+5*kT_q*eps_GaN/T_GaN);

	//double Q_d=Cox*(Vgs-Vfb-phi_s(Ny-1));
	//double f_d=pow(Q_d,2)/2/Cox+2*kT_q*Q_s-5*pow(kT_q,2)*eps_GaN/T_GaN*log(Q_d+5*kT_q*eps_GaN/T_GaN);

	//double Id=2*mu/Lg*(f_s-f_d);

	//cout << Id <<endl;
	//system("pause");
    return 0;
}
