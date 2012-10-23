//#include<math.h>
//#include<iostream>
//#include <iomanip>
//using namespace std;
//const int SIZE = 10000;
//const int UNIT = 10000; 
////2
////3
////7
////43
////1807
////3263443
////10650056950807
////113423713055421844361000443
////12864938683278671740537145998360961546653259485195807
//
////2
////1
////4
////36
////1764
////3261636
////10650053687364
////113423713055411194304049636
////12864938683278671740537145884937248491231415124195364
//
//class HugeInt{
//	friend ostream &operator <<(ostream&,HugeInt&);
//public:
//	HugeInt(int value = 0);
//	HugeInt& operator= (const HugeInt&);
//	HugeInt operator+ (const HugeInt&);
//	HugeInt operator- (const HugeInt&);
//	HugeInt operator* (const HugeInt&);
//private:
//	int integer[SIZE];			
//	int length;			
//};
//
//ostream &operator <<(ostream &out, HugeInt &op)
//{
//    if (op.length == 0) {
//        out << 0;
//        return out;
//    }
//    else {
//        out<<op.integer[op.length - 1];
//        int w = (int) log10((double)UNIT);
//        for (int i = op.length - 2; i >= 0; i--) {
//            out<<setw(w)<<setfill('0')<<op.integer[i];
//        }
//        return out;
//    }
//    
//}
//
//HugeInt::HugeInt(int value)
//{
//    length = 0;
//    int v = value;
//    for (int i = 0; i < SIZE; i++)
//        integer[i] = 0;
//    for (int j = v; j != 0; j /= UNIT)
//        integer[length++] = j % UNIT;
//}
//
//HugeInt& HugeInt::operator=(const HugeInt& op)
//{
//    for (int i = 0; i < SIZE; i++)
//        integer[i] = 0;
//    for (int i = 0; i < op.length; i++) {
//        integer[i] = op.integer[i];
//    }
//    length = op.length;
//    return *this;
//}
//
//HugeInt HugeInt::operator+(const HugeInt& op)
//{
//    int carry = 0, temp;
//    HugeInt r;
//    r.length = (length > op.length)?length:op.length;
//    for (int i = 0; i < r.length; i++) {
//        temp = integer[i] + op.integer[i] + carry;
//        r.integer[i] = temp % UNIT;
//        carry = temp / UNIT;
//    }
//    
//    if (carry != 0) {
//        r.integer[r.length++] = carry;
//    }
//    
//    return r;
//}
//
//HugeInt HugeInt::operator-(const HugeInt& op)
//{
//    int carry = 0;
//    HugeInt r;
//    r.length = (length > op.length)?length:op.length;
//    for (int i = 0; i < r.length; i++) {
//        r.integer[i] = integer[i] - op.integer[i] - carry;
//        if (r.integer[i] < 0) {
//            r.integer[i] += UNIT;
//            carry = 1;
//        }
//        else
//            carry = 0;
//    }
//    int l = r.length;
//    for (int j = l - 1; j >= 0; j--) {
//        if (r.integer[j] == 0) {
//            r.length--;
//        }
//        else
//            break;
//    }
//    if (carry != 0) {
//        return HugeInt();
//    }
//    else
//        return r;
//}
//
//HugeInt HugeInt::operator*(const HugeInt& op)
//{
//    int carry = 0, temp, i, j;
//    HugeInt r;
//    r.length = length + op.length;
//    for (i = 0; i < op.length; i++) {
//        for (j = 0; j < length; j++) {
//            temp = integer[j] * op.integer[i] + carry;
//            r.integer[j + i] += temp % UNIT;
//            carry = temp / UNIT;
//        }
//        if (carry != 0) {
//            r.integer[i + j] += carry;
//            carry = 0;
//        }
//    }
//    
//    for (int k = r.length - 1; k >= 0; k--) {
//        if (r.integer[k] == 0) {
//            r.length--;
//        }
//        else
//            break;
//    }
//    return r;
//}
//
//
//int main(){
//	HugeInt a[18],b(2),c(1), d;
//	a[0] = b;
//	int n;
//	cin>>n;
//	cout<<a[0]<<endl;
//	HugeInt temp(1);
//	for(int i = 1; i < n; i++){
//		temp = temp * a[i-1];
//		a[i] = temp + c;
//        d = a[i];
//		cout<<d<<endl;
//	}
//	return 0;
//}