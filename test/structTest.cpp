#define __test__structtest
#ifndef __test__structtest
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

typedef struct{
    double k;
} torgle_register;

union id {
    char c[20];
    int n;
};

class A {
public:
    int a;
    A(): a(0){};
    virtual ~A(){cout<<"A"<<endl;};
    virtual void f(A& aa){cout<<"FA"<<endl;};
};
class B: public A {
public:
    double b;
    B(): b(0.1){};
    ~B(){cout<<"B"<<endl;};
    void f(A& bb){cout<<"FB"<<endl;};
    void f(B& bb){cout<<"BFB"<<endl;};
};
class stock{
public:
    const int l = 1;
    int len;
    vector<int> quiz;
    stock(int n): l(n), quiz(){};
    stock(){};
    operator double() const {return (double) l;};
    void* operator new(size_t){;};
    virtual void isA(){};
    inline double mul() throw(){;};
};
inline double func(int a = 1, int b = 0) {return a*a;}

enum spectrum {red, orange, yellow};

template<typename T>
void Swap(T, T);

template <> void Swap(int, int);

void g1(int&);
void g2(int const &);

int main(int argv, char* argc[]) {
    int n = -2147483648;
    //for (int i = 0; n != 0, i < 32; n >>= 1, i++)
        //cout<<i<<": "<<(n & 1)<<endl;
    cout<<boolalpha<<(n == -n)<<endl;
    ios_base::fmtflags oldfmt = cout.setf(ios_base::internal, ios_base::adjustfield);
    cout.setf(oldfmt, ios_base::adjustfield);
    cout.setf(ios_base::fixed);
    cout.precision(2);
    //cout.setf(ios_base::showpoint);
    cout.width(9);
    cout<<fixed << showpoint << 2.0<<left;
    cout<<4.0<<":"<<endl;
    spectrum band = spectrum(2);
    torgle_register a;
    double (*pf)(int, int) = func;
    //char c[5] = {'d', 'o', 'g'};
    //cout<< c << endl;
    Swap(1,2);
    Swap(1.1, 2.2);
    void (*p)(int,int);
    p = Swap;
    p(3.1,2.1);
    
    Swap('a','c');
    int one = 1;
    const int & onep = one;
    int aa = onep;
    aa = 2;
    cout<<"one: "<<one<<" aa: "<<aa<<1024*32<<endl;
    
    double d = 1.1;
    double *pd = &d;
    //cout<<*((int*)pd)<<endl;
    cout<<*pd<<endl;
    {A aA; B aB; B* pA; pA = &aB; pA->f(aB);}
    return 0;
}

template<typename T>
void Swap(T a, T b){cout<<"T"<<endl;}

template <> void Swap(int a, int b){
    cout<<"int: "<<a<<endl;
}

template void Swap(char a, char b){
    cout<<"char"<<endl;
}
void g1(int& n) {
    ;
}
void g2(const int & n){
    int s = n;
    g1(s);
}
#endif