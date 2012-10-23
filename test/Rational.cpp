//#include <iostream>
//#include <cmath>
//#include "Rational.h"
//
//using namespace std;
//
//Rational::Rational()
//{
//    dominant = 0;
//    denominator = 1;
//}
//
//Rational::Rational(int p, int q)
//{
//    setRational(p, q);
//}
//
//Rational::~Rational()
//{
//    ;
//}
//
//void Rational::setRational(int p, int q)
//{
//    if (q == 0) 
//    {
//        cout<<"Invalid input."<<endl;
//    }
//    else
//    {
//        int x = get_gcd(p, q);
//        dominant = p / x;
//        denominator = q / x;
//    }
//}
//
//int Rational::getDominant() 
//{
//    return dominant; 
//}
//
//int Rational::getDenominantor() 
//{
//    return denominator;
//}
//
//void Rational::setDominant(int p)
//{
//    int x = get_gcd(p, denominator);
//    dominant = p / x;
//    denominator = denominator / x;
//}
//
//void Rational::setDenominator(int q)
//{
//    if (q == 0) 
//    {
//        cout<<"Invalid input."<<endl;
//    }
//    else
//    {
//        int x = get_gcd(dominant, q);
//        dominant = dominant / x;
//        denominator = q / x;
//    }
//
//}
//
//Rational Rational::add(Rational x) 
//{
//    int new_dominant, new_denominant;
//    new_dominant = dominant * x.denominator + denominator * x.dominant;
//    new_denominant = denominator * x.denominator;
//    return Rational( new_dominant, new_denominant );
//}
//
//Rational Rational::subtract(Rational x)
//{
//    int new_dominant, new_denominant;
//    new_dominant = dominant * x.denominator - denominator * x.dominant;
//    new_denominant = denominator * x.denominator;
//    return Rational( new_dominant, new_denominant );
//}
//
//Rational Rational::multiply(Rational x) 
//{
//    int new_dominant, new_denominant;
//    new_dominant = dominant * x.dominant;
//    new_denominant = denominator * x.denominator;
//    return Rational( new_dominant, new_denominant );
//
//}
//
//void Rational::print()
//{
//    cout << dominant << " / " << denominator << endl;
//}
//
//int Rational::get_gcd(int x, int y)
//{
//    x = abs(x);
//    y = abs(y);
//    
//    if ((x == 0)||(y == 0)) 
//    {
//        return 1;
//    }
//    else
//    {
//        if (x == y) 
//        {
//            return x;
//        }
//        else
//        {
//            int smaller = x;
//            if (smaller > y)
//                smaller = y;
//            return get_gcd(smaller, abs(x - y));
//        }
//    }
//}
//istream& operator >> (istream& in, Rational& r)
//{
//    int p, q;
//    char c;
//    in >> p >> c >> q;
//    r.setDominant(p);
//    r.setDenominator(q);
//    return in;
//}
//
//ostream& operator << (ostream& out, Rational& r)
//{
//    out << r.dominant << "/" << r.denominator;
//    return out;
//}
//
//Rational& Rational::operator = (const Rational& r)
//{
//    if (&r != this) {
//        dominant = r.dominant;
//        denominator = r.denominator;
//        return *this;
//    }
//    return *this;
//}
//Rational Rational::operator + (Rational r)
//{
//    int new_dominant, new_denominant;
//    new_dominant = dominant * r.denominator + denominator * r.dominant;
//    new_denominant = denominator * r.denominator;
//    return Rational( new_dominant, new_denominant );
//}
//Rational Rational::operator - (Rational r)
//{
//    int new_dominant, new_denominant;
//    new_dominant = dominant * r.denominator - denominator * r.dominant;
//    new_denominant = denominator * r.denominator;
//    return Rational( new_dominant, new_denominant );
//}
//Rational Rational::operator * (Rational r)
//{
//    int new_dominant, new_denominant;
//    new_dominant = dominant * r.dominant;
//    new_denominant = denominator * r.denominator;
//    return Rational( new_dominant, new_denominant );
//}
//
//Rational Rational::operator / (Rational r)
//{
//    int new_dominant, new_denominant;
//    new_dominant = dominant * r.denominator;
//    new_denominant = denominator * r.dominant;
//    return Rational( new_dominant, new_denominant );
//}