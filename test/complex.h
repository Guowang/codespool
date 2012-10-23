#include <iostream>
using namespace std;

template <typename T>
class Complex {
public:
  /*Complex();
  Complex(double, double);
  ~Complex();
  void setComplex(double, double);

  double getRealPart();
  double getImagPart();
  void setRealPart(double);
  void setImagPart(double);

  Complex add(Complex);
  Complex subtract(Complex);
  Complex multiply(Complex);
  double magnitude();
  void print();
   */
    void t(T t0);

        

private:
  double realPart;
  double imagPart;
};

template <typename T>
void Complex <T>::t(T t0)
{
    std::cout << t0 << std::endl;
}
