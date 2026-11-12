#include"BigIntpro.h"
#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
BigInt::BigInt(const char* s1) {
    int start=0; 
    isNeg = false;
    if(s1[0]=='-') {
        isNeg = true;
        start = 1; 
    }
    while (s1[start] == '0' && s1[start+1] != '\0') {
        start++;
    }
    len = strlen(s1 + start);
    size = len + 1;
    s = new char[size];   
    for(size_t i = 0; i < size; i++) {
        s[i] = s1[start + i]; 
    }
    isZero = (len == 1 && s[0] == '0');  
    if(isZero) isNeg = false;
}
BigInt::BigInt(const BigInt& x){
    len=x.len;
    size=len+1;
    isZero=x.isZero;
    isNeg=x.isNeg;
    s=new char[size];
    for(size_t i=0;i<size;i++) s[i]=x.s[i];
}
BigInt::BigInt(const int x){
    if(x==0){
        len=1;
        size=2;
        s=new char[2];
        s[0]='0';
        s[1]='\0';
        isZero=true;
        isNeg=false;
        return;
    }
    isZero=false;
    isNeg=false;
    size_t temp=abs(x);
    len=0;
    while(temp>0){
        len++;
        temp/=10;
    }
    size=len+1;
    s=new char[size];
    s[len]='\0';
    temp=x;
    for(int i=len-1;i>=0;i--){
        s[i]=(temp%10)+'0';
        temp/=10;
    }
    if(x<0) isNeg=true; 
}
BigInt& BigInt::operator=(const BigInt& x){
    if(this!=&x){
        len=x.len;
        size=x.size;
        isZero=x.isZero;
        isNeg=x.isNeg;
        delete[] s;
        s=new char[size];
        for(int i=0;i<=len;i++){
            s[i]=x.s[i];
        }
    }
    return *this;
}


BigInt BigInt::absAdd(const BigInt& a, const BigInt& b){
    const BigInt* longer;
    const BigInt* shorter;
    if(a.len > b.len){
        longer = &a;
        shorter = &b;
    } else {
        shorter = &a;
        longer = &b;
    }
    char* temp = new char[longer->len + 2]; 
    temp[longer->len + 1] = '\0';

    int i = longer->len - 1;
    int j = shorter->len - 1;
    int k = longer->len;
    int carry = 0;
    while(j >= 0){
        int sum = (longer->s[i] - '0') + (shorter->s[j] - '0') + carry;
        temp[k] = (sum % 10) + '0';
        carry = sum / 10;
        i--; j--; k--;
    }
    while(i >= 0){
        int sum = (longer->s[i] - '0') + carry;
        temp[k] = (sum % 10) + '0';
        carry = sum / 10;
        i--; k--;
    }
    if(carry > 0){
        temp[k] = carry + '0';
    } else {
        k++;
    }
    BigInt sum(temp + k); 
    delete[] temp;    
    return sum;    
}
int BigInt::absCompare(const BigInt& a,const BigInt& b){
    if(a.len>b.len) return 1;
    if(a.len<b.len) return -1;
    for(int i=0;i<a.len;i++){
        if(a.s[i]>b.s[i]) return 1;
        if(a.s[i]<b.s[i]) return -1;
    }
    return 0;
}
BigInt BigInt::absSub(const BigInt& a,const BigInt& b){
    const BigInt* longer;
    const BigInt* shorter;
    if(BigInt::absCompare(a,b)==1){
        longer=&a;
        shorter=&b;
    }
    else if(BigInt::absCompare(a,b)==-1){
        longer=&b;
        shorter=&a;
    }
    else return BigInt("0");
    char* temp = new char[longer->len + 1]; 
    temp[longer->len] = '\0';

    int i = longer->len - 1;
    int j = shorter->len - 1;
    int k = longer->len-1;
    int borrow = 0;
    while(j >= 0){
        int vala=(longer->s[i]-'0')-borrow;
        int valb=shorter->s[j]-'0';
        if(vala<valb){
            vala+=10;
            borrow=1;
        }
        else borrow=0;
        temp[k]=vala-valb+'0';
        i--; j--; k--;
    }
    while(i >= 0){
        int vala = (longer->s[i] - '0') - borrow;
        if(vala<0){
            vala+=10;
            borrow=1;
        }
        else borrow=0;
        temp[k] = vala+'0';
        i--; k--;
    }
    int start=0;
    while(temp[start]=='0'&&start<longer->len-1) start++;
    BigInt result(temp + start); 
    if(BigInt::absCompare(a,b)==-1) result.isNeg=true;
    delete[] temp;    
    return result;    
}
BigInt BigInt::absMul(const BigInt& a, const BigInt& b) {
    if (a.isZero || b.isZero) {
        return BigInt("0");
    }
    const BigInt* longer;
    const BigInt* shorter;
    if (a.len > b.len) {
        longer = &a;
        shorter = &b;
    } else {
        shorter = &a;
        longer = &b;
    }
    char* temp = new char[longer->len + 2]; 
    BigInt tempInt("0");
    int zeroCount = 0;
    for(int j = shorter->len - 1; j >= 0; j--) {
        int rowMax = longer->len + 1; 
        for(int m = 0; m < rowMax; m++) {
            temp[m] = '0';
        }
        temp[rowMax] = '\0'; 
        int k = longer->len;
        int carry = 0;
        for(int i = longer->len - 1; i >= 0; i--) {
            int prod = (longer->s[i] - '0') * (shorter->s[j] - '0') + carry;
            temp[k] = (prod % 10) + '0';
            carry = prod / 10;
            k--;
        }
        if(carry > 0) {
            temp[k] = carry + '0';
        }
        BigInt tempInt2(temp); 
        if(zeroCount > 0) {
            int newLen = tempInt2.len + zeroCount;
            char* newS = new char[newLen + 1];
            for(int m = 0; m < tempInt2.len; m++) {
                newS[m] = tempInt2.s[m];
            }
            for(int m = tempInt2.len; m < newLen; m++) {
                newS[m] = '0';
            }
            newS[newLen] = '\0';
            tempInt2 = BigInt(newS);
            delete[] newS;
        }
        tempInt = tempInt + tempInt2;
        zeroCount++;
    }
    
    delete[] temp; 
    return tempInt;
}


bool BigInt::operator==(const BigInt& x)const{
    if(BigInt::absCompare(*this,x)==0&&isNeg==x.isNeg) return true;
    else return false;
}
bool BigInt::operator!=(const BigInt& x)const{
    if(BigInt::absCompare(*this,x)!=0) return true;
    else if (BigInt::absCompare(*this,x)==0&&isNeg!=x.isNeg) return true;
    else return false;
}
bool BigInt::operator<(const BigInt& x)const{
    if(isNeg==true&&x.isNeg==false) return true;
    else if(isNeg==false&&x.isNeg==false&&BigInt::absCompare(*this,x)==-1) return true;
    else if(isNeg==true&&x.isNeg==true&&BigInt::absCompare(*this,x)==1) return true;
    else return false;
}
bool BigInt::operator<=(const BigInt& x)const{
    if(isNeg==true&&x.isNeg==false) return true;
    else if(isNeg==false&&x.isNeg==false&&BigInt::absCompare(*this,x)==-1) return true;
    else if(isNeg==true&&x.isNeg==true&&BigInt::absCompare(*this,x)==1) return true;
    else if(BigInt::absCompare(*this,x)==0) return true;
    else return false;
}
bool BigInt::operator>(const BigInt& x)const{
    if(isNeg==false&&x.isNeg==true) return true;
    else if(isNeg==true&&x.isNeg==true&&BigInt::absCompare(*this,x)==-1) return true;
    else if(isNeg==false&&x.isNeg==false&&BigInt::absCompare(*this,x)==1) return true;
    else return false;
}
bool BigInt::operator>=(const BigInt& x)const{
    if(isNeg==false&&x.isNeg==true) return true;
    else if(isNeg==true&&x.isNeg==true&&BigInt::absCompare(*this,x)==-1) return true;
    else if(isNeg==false&&x.isNeg==false&&BigInt::absCompare(*this,x)==1) return true;
    else if(BigInt::absCompare(*this,x)==0) return true;
    else return false;
}
ostream& operator<<(ostream& os, const BigInt& x){
    if(x.isNeg) os << "-";
    for(size_t i = 0; i < x.len; i++) os << x.s[i];
    return os;
}

BigInt operator+(const BigInt& left,const BigInt& right){
    if(left.isNeg==false&&right.isNeg==false) return BigInt::absAdd(left,right);
    else if(left.isNeg==true&&right.isNeg==true){
        BigInt temp=BigInt::absAdd(left,right);
        temp.isNeg=true;
        return temp;
    }
    else if(left.isNeg==false&&right.isNeg==true) return BigInt::absSub(left,right);
    else if(left.isNeg==true&&right.isNeg==false) return BigInt::absSub(right,left);
    else return BigInt("0");
}
BigInt& BigInt::operator+=(const BigInt& right){
    *this=*this+right;
    return *this;
}
BigInt operator-(const BigInt& left,const BigInt& right){
    if(left.isNeg==false&&right.isNeg==false) return BigInt::absSub(left,right);
    else if(left.isNeg==true&&right.isNeg==true) return BigInt::absSub(right,left);
    else if(left.isNeg==false&&right.isNeg==true) return BigInt::absAdd(left,right);
    else if(left.isNeg==true&&right.isNeg==false){
        BigInt result=BigInt::absAdd(left,right);
        result.isNeg=true;
        return result;
    }
    else return BigInt("0");
}
BigInt& BigInt:: operator-=(const BigInt& right){
    *this=*this-right;
    return *this;
}
BigInt operator*(const BigInt& left,const BigInt& right){
    BigInt temp=BigInt::absMul(left,right);
    if(left.isNeg != right.isNeg && !temp.isZero) {
        temp.isNeg = true;
    }
    return temp;
}
BigInt& BigInt::operator*=(const BigInt& right){
    *this=*this*right;
    return *this;
}