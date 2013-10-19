#define __test__BigInt__
#ifndef __test__BigInt__
#include<math.h>
#include<iostream>
#include <iomanip>
using namespace std;
const int SIZE = 10000;
const int UNIT = 10000; 
//2
//3
//7
//43
//1807
//3263443
//10650056950807
//113423713055421844361000443
//12864938683278671740537145998360961546653259485195807

//2
//1
//4
//36
//1764
//3261636
//10650053687364
//113423713055411194304049636
//12864938683278671740537145884937248491231415124195364

class HugeInt{
	friend ostream &operator <<(ostream&,HugeInt&);
public:
	HugeInt(int value = 0);
	HugeInt& operator= (const HugeInt&);
	HugeInt operator+ (const HugeInt&);
	HugeInt operator- (const HugeInt&);
	HugeInt operator* (const HugeInt&);
private:
	int integer[SIZE];			
	int length;			
};

ostream &operator <<(ostream &out, HugeInt &op)
{
    if (op.length == 0) {
        out << 0;
        return out;
    }
    else {
        out<<op.integer[op.length - 1];
        int w = (int) log10((double)UNIT);
        for (int i = op.length - 2; i >= 0; i--) {
            out<<setw(w)<<setfill('0')<<op.integer[i];
        }
        return out;
    }
    
}

HugeInt::HugeInt(int value)
{
    length = 0;
    int v = value;
    for (int i = 0; i < SIZE; i++)
        integer[i] = 0;
    for (int j = v; j != 0; j /= UNIT)
        integer[length++] = j % UNIT;
}

HugeInt& HugeInt::operator=(const HugeInt& op)
{
    for (int i = 0; i < SIZE; i++)
        integer[i] = 0;
    for (int i = 0; i < op.length; i++) {
        integer[i] = op.integer[i];
    }
    length = op.length;
    return *this;
}

HugeInt HugeInt::operator+(const HugeInt& op)
{
    int carry = 0, temp;
    HugeInt r;
    r.length = (length > op.length)?length:op.length;
    for (int i = 0; i < r.length; i++) {
        temp = integer[i] + op.integer[i] + carry;
        r.integer[i] = temp % UNIT;
        carry = temp / UNIT;
    }
    
    if (carry != 0) {
        r.integer[r.length++] = carry;
    }
    
    return r;
}

HugeInt HugeInt::operator-(const HugeInt& op)
{
    int carry = 0;
    HugeInt r;
    r.length = (length > op.length)?length:op.length;
    for (int i = 0; i < r.length; i++) {
        r.integer[i] = integer[i] - op.integer[i] - carry;
        if (r.integer[i] < 0) {
            r.integer[i] += UNIT;
            carry = 1;
        }
        else
            carry = 0;
    }
    int l = r.length;
    for (int j = l - 1; j >= 0; j--) {
        if (r.integer[j] == 0) {
            r.length--;
        }
        else
            break;
    }
    if (carry != 0) {
        return HugeInt();
    }
    else
        return r;
}

HugeInt HugeInt::operator*(const HugeInt& op)
{
    int carry = 0, temp, i, j;
    HugeInt r;
    r.length = length + op.length;
    for (i = 0; i < op.length; i++) {
        for (j = 0; j < length; j++) {
            temp = integer[j] * op.integer[i] + carry;
            r.integer[j + i] += temp % UNIT;
            carry = temp / UNIT;
        }
        if (carry != 0) {
            r.integer[i + j] += carry;
            carry = 0;
        }
    }
    
    for (int k = r.length - 1; k >= 0; k--) {
        if (r.integer[k] == 0) {
            r.length--;
        }
        else
            break;
    }
    return r;
}


int main(){
	HugeInt a[18],b(2),c(1), d;
	a[0] = b;
	int n;
	cin>>n;
	cout<<a[0]<<endl;
	HugeInt temp(1);
	for(int i = 1; i < n; i++){
		temp = temp * a[i-1];
		a[i] = temp + c;
        d = a[i];
		cout<<d<<endl;
	}
	return 0;
}

const int MAXD = 1005, DIG = 9, BASE = 1000000000;
const unsigned long long BOUND = numeric_limits <unsigned long long> :: max () - (unsigned long long) BASE * BASE;

struct bignum
{
    int D, digits [MAXD / DIG + 2];
    
    inline void trim ()
    {
        while (D > 1 && digits [D - 1] == 0)
            D--;
    }
    
    inline void init (long long x)
    {
        memset (digits, 0, sizeof (digits));
        D = 0;
        
        do
        {
            digits [D++] = x % BASE;
            x /= BASE;
        }
        while (x > 0);
    }
    
    inline bignum (long long x)
    {
        init (x);
    }
    
    inline bignum (int x = 0)
    {
        init (x);
    }
    
    inline bignum (char *s)
    {
        memset (digits, 0, sizeof (digits));
        int len = strlen (s), first = (len + DIG - 1) % DIG + 1;
        D = (len + DIG - 1) / DIG;
        
        for (int i = 0; i < first; i++)
            digits [D - 1] = digits [D - 1] * 10 + s [i] - '0';
        
        for (int i = first, d = D - 2; i < len; i += DIG, d--)
            for (int j = i; j < i + DIG; j++)
                digits [d] = digits [d] * 10 + s [j] - '0';
        
        trim ();
    }
    
    inline char *str ()
    {
        trim ();
        char *buf = new char [DIG * D + 1];
        int pos = 0, d = digits [D - 1];
        
        do
        {
            buf [pos++] = d % 10 + '0';
            d /= 10;
        }
        while (d > 0);
        
        reverse (buf, buf + pos);
        
        for (int i = D - 2; i >= 0; i--, pos += DIG)
            for (int j = DIG - 1, t = digits [i]; j >= 0; j--)
            {
                buf [pos + j] = t % 10 + '0';
                t /= 10;
            }
        
        buf [pos] = '\0';
        return buf;
    }
    
    inline bool operator < (const bignum &o) const
    {
        if (D != o.D)
            return D < o.D;
        
        for (int i = D - 1; i >= 0; i--)
            if (digits [i] != o.digits [i])
                return digits [i] < o.digits [i];
        
        return false;
    }
    
    inline bool operator == (const bignum &o) const
    {
        if (D != o.D)
            return false;
        
        for (int i = 0; i < D; i++)
            if (digits [i] != o.digits [i])
                return false;
        
        return true;
    }
    
    inline bignum operator << (int p) const
    {
        bignum temp;
        temp.D = D + p;
        
        for (int i = 0; i < D; i++)
            temp.digits [i + p] = digits [i];
        
        for (int i = 0; i < p; i++)
            temp.digits [i] = 0;
        
        return temp;
    }
    
    inline bignum operator >> (int p) const
    {
        bignum temp;
        temp.D = D - p;
        
        for (int i = 0; i < D - p; i++)
            temp.digits [i] = digits [i + p];
        
        for (int i = D - p; i < D; i++)
            temp.digits [i] = 0;
        
        return temp;
    }
    
    inline bignum range (int a, int b) const
    {
        bignum temp = 0;
        temp.D = b - a;
        
        for (int i = 0; i < temp.D; i++)
            temp.digits [i] = digits [i + a];
        
        return temp;
    }
    
    inline bignum operator + (const bignum &o) const
    {
        bignum sum = o;
        int carry = 0;
        
        for (sum.D = 0; sum.D < D || carry > 0; sum.D++)
        {
            sum.digits [sum.D] += (sum.D < D ? digits [sum.D] : 0) + carry;
            
            if (sum.digits [sum.D] >= BASE)
            {
                sum.digits [sum.D] -= BASE;
                carry = 1;
            }
            else
                carry = 0;
        }
        
        sum.D = max (sum.D, o.D);
        sum.trim ();
        return sum;
    }
    
    inline bignum operator - (const bignum &o) const
    {
        bignum diff = *this;
        
        for (int i = 0, carry = 0; i < o.D || carry > 0; i++)
        {
            diff.digits [i] -= (i < o.D ? o.digits [i] : 0) + carry;
            
            if (diff.digits [i] < 0)
            {
                diff.digits [i] += BASE;
                carry = 1;
            }
            else
                carry = 0;
        }
        
        diff.trim ();
        return diff;
    }
    
    inline bignum operator * (const bignum &o) const
    {
        bignum prod = 0;
        unsigned long long sum = 0, carry = 0;
        
        for (prod.D = 0; prod.D < D + o.D - 1 || carry > 0; prod.D++)
        {
            sum = carry % BASE;
            carry /= BASE;
            
            for (int j = max (prod.D - o.D + 1, 0); j <= min (D - 1, prod.D); j++)
            {
                sum += (unsigned long long) digits [j] * o.digits [prod.D - j];
                
                if (sum >= BOUND)
                {
                    carry += sum / BASE;
                    sum %= BASE;
                }
            }
            
            carry += sum / BASE;
            prod.digits [prod.D] = sum % BASE;
        }
        
        prod.trim ();
        return prod;
    }
    
    inline double double_div (const bignum &o) const
    {
        double val = 0, oval = 0;
        int num = 0, onum = 0;
        
        for (int i = D - 1; i >= max (D - 3, 0); i--, num++)
            val = val * BASE + digits [i];
        
        for (int i = o.D - 1; i >= max (o.D - 3, 0); i--, onum++)
            oval = oval * BASE + o.digits [i];
        
        return val / oval * (D - num > o.D - onum ? BASE : 1);
    }
    
    inline pair <bignum, bignum> divmod (const bignum &o) const
    {
        bignum quot = 0, rem = *this, temp;
        
        for (int i = D - o.D; i >= 0; i--)
        {
            temp = rem.range (i, rem.D);
            int div = (int) temp.double_div (o);
            bignum mult = o * div;
            
            while (div > 0 && temp < mult)
            {
                mult = mult - o;
                div--;
            }
            
            while (div + 1 < BASE && !(temp < mult + o))
            {
                mult = mult + o;
                div++;
            }
            
            rem = rem - (o * div << i);
            
            if (div > 0)
            {
                quot.digits [i] = div;
                quot.D = max (quot.D, i + 1);
            }
        }
        
        quot.trim ();
        rem.trim ();
        return make_pair (quot, rem);
    }
    
    inline bignum operator / (const bignum &o) const
    {
        return divmod (o).first;
    }
    
    inline bignum operator % (const bignum &o) const
    {
        return divmod (o).second;
    }
    
    inline bignum power (int exp) const
    {
        bignum p = 1, temp = *this;
        
        while (exp > 0)
        {
            if (exp & 1) p = p * temp;
            if (exp > 1) temp = temp * temp;
            exp >>= 1;
        }
        
        return p;
    }
};

inline bignum gcd (bignum a, bignum b)
{
    bignum t;
    
    while (!(b == 0))
    {
        t = a % b;
        a = b;
        b = t;
    }
    
    return a;
}
#endif