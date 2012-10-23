#include <iostream>
using namespace std;
class Rational
{
    friend istream& operator >> (istream&, Rational&);
    friend ostream& operator << (ostream&, Rational&);
public:
    Rational();
    Rational(int, int);
    ~Rational();
    
    void setRational(int, int);
    
    int getDominant();
    int getDenominantor();
    void setDominant(int);
    void setDenominator(int);
    
    Rational add(Rational);
    Rational subtract(Rational);
    Rational multiply(Rational);
    void print();
    
    Rational& operator = (const Rational&);
    Rational operator + (Rational);
    Rational operator - (Rational);
    Rational operator * (Rational);
    Rational operator / (Rational);
    
    
private:
    int dominant;
    int denominator;
    int get_gcd(int x, int y);
};

