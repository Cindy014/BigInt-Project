#ifndef _BIGINTPRO_H_
#define _BIGINTPRO_H_
#include<iostream>
using namespace std;
class BigInt{
    bool isZero;
    size_t len;
    size_t size;
    char* s;
    bool isNeg;
public:
    BigInt():isZero(0),len(0),size(10),isNeg(false),s(new char[size]){}
    BigInt(const int x);
    BigInt(const char* s1);
    BigInt(const BigInt& x);
    ~BigInt(){delete[] s;}
    static BigInt absAdd(const BigInt& a,const BigInt& b);//新技能：静态函数 不和对象绑定
    static BigInt absSub(const BigInt& a,const BigInt& b);
    static int absCompare(const BigInt& a,const BigInt& b);
    static BigInt absMul(const BigInt& a,const BigInt& b);
    BigInt& operator=(const BigInt& x);
    bool operator!=(const BigInt& x)const;
    bool operator==(const BigInt& x)const;
    bool operator<(const BigInt& x)const;
    bool operator<=(const BigInt& x)const;
    bool operator>(const BigInt& x)const;
    bool operator>=(const BigInt& x)const;
    friend ostream& operator<<(ostream& os,const BigInt& x);
    BigInt& operator+=(const BigInt& right);
    friend BigInt operator+(const BigInt& left,const BigInt& right);
    BigInt& operator*=(const BigInt& right);
    friend BigInt operator*(const BigInt& left,const BigInt& right);
    BigInt& operator-=(const BigInt& right);
    friend BigInt operator-(const BigInt& left,const BigInt& right);
};
#endif
