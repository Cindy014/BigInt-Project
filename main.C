#include<iostream>
#include"BigIntpro.h"
using namespace std;

int main() {
    BigInt a("12345678901234567890");
    BigInt b("-98765432109876543210");
    BigInt c("5555555555");
    BigInt d("-1");
    BigInt zero(0);
    BigInt x;
    
    x = a;
    
    cout << x << " == " << a << "? " << (x == a) << endl;
    cout << x << " != " << b << "? " << (x != b) << endl;
    cout << a << " > " << b << "? " << (a > b) << endl;
    cout << a << " <= " << c << "? " << (a <= c) << endl;
    cout << b << " < " << zero << "? " << (b < zero) << endl;
    cout << zero << " >= " << d << "? " << (zero >= d) << endl << endl;
    
    cout << a << " + " << c << " = " << (a + c) << endl;
    cout << a << " + " << b << " = " << (a + b) << endl;
    cout << b << " + " << zero << " = " << (b + zero) << endl;
    cout << b << " + " << b << " = " << (b + b) << endl << endl;
    
    std::cout << a << " - " << c << " = " << (a - c) << std::endl;
    std::cout << c << " - " << a << " = " << (c - a) << std::endl;
    std::cout << zero << " - " << a << " = " << (zero - a) << std::endl;
    std::cout << a << " - " << b << " = " << (a - b) << std::endl << std::endl;
    
    std::cout << a << " * " << c << " = " << (a * c) << std::endl;
    std::cout << b << " * " << b << " = " << (b * b) << std::endl;
    std::cout << a << " * " << zero << " = " << (a * zero) << std::endl << std::endl;
    
    std::cout << "(" << a << "+" << b << "-" << c << ") * " << d << " = " << (a + b - c) * d << std::endl;
    
    return 0;
}