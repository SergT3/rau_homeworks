#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>

class Complex
{
public:
int getR() const;
int getI() const;
Complex();
Complex(int _real,int _imag);
Complex operator+ (const Complex& i);
Complex operator* (const Complex& i);
Complex operator* (int i);
bool operator< (const Complex& i);
bool operator> (const Complex& i);
bool operator== (const Complex& i);
friend std::ostream& operator<<(std::ostream& os, const Complex& i);
friend std::istream& operator>>(std::istream& is, Complex& i);
int Absolute() const;
private:
int real;
int imag;
};

void insertionSort(Complex* arr, int n);

#endif
