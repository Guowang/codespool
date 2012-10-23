/*
#include <iostream>
using namespace std;
#include <cmath>
#include "complex.h"

Complex::Complex()
{
  setComplex(0.0, 0.0);
}

Complex::Complex(double rp, double ip)
{
  setComplex(rp, ip);
}

Complex::~Complex()
{
}

void Complex::setComplex(double rp, double ip)
{
  setRealPart(rp);
  setImagPart(ip);
}

double Complex::getRealPart() 
{
  return realPart; 
}

double Complex::getImagPart() 
{
  return imagPart;
}

void Complex::setRealPart(double rp)
{
  realPart = rp;
}

void Complex::setImagPart(double ip)
{
  imagPart = ip;
}

Complex Complex::add(Complex x) 
{
  return Complex( realPart + x.realPart, imagPart + x.imagPart );
}

Complex Complex::subtract(Complex x)
{
  return Complex( realPart - x.realPart, imagPart - x.imagPart );
}

Complex Complex::multiply(Complex x) 
{
  return Complex( realPart*x.realPart - imagPart*x.imagPart,
                  realPart*x.imagPart + imagPart*x.realPart );
}

double Complex::magnitude()
{
  return sqrt( realPart*realPart + imagPart*imagPart );
}

void Complex::print()
{
  cout << realPart << " + " << imagPart << " i";
}

*/
#include "complex.h"
#include <iostream>
/*
template <typename T>
void Complex <T>::t(T t0)
{
    std::cout << t0 << std::endl;
}
 */
