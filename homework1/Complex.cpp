#include <iostream>
#include "Complex.h"

Complex::Complex() = default;

Complex::Complex(int _real,int _imag) :
real(_real),
imag(_imag){}

int Complex::getR() const
{
return real;
}

int Complex::getI() const
{
return imag;
}

int Complex::Absolute() const
{
return real * real + imag * imag;
}

Complex Complex::operator+(const Complex& i)
{
Complex a(real + i.getR(),imag + i.getI());
return a;
}

Complex Complex::operator*(int i)
{
Complex a(real * i ,imag * i);
return a;
}

Complex Complex::operator*(const Complex& i)
{
Complex a(real * i.getR() - imag * i.getI(),imag * i.getR() + real * i.getI());
return a;
}

bool Complex::operator< (const Complex& i)
{
	return Absolute() < i.Absolute();
}

bool Complex::operator> (const Complex& i)
{
	return Absolute() > i.Absolute(); 
}

bool Complex::operator== (const Complex& i)
{
	return Absolute() == i.Absolute();
}

std::ostream& operator<<(std::ostream& os, const Complex& i)
{
	os << i.real << ((i.imag >= 0) ? " + " : " ") << i.imag << "i";
	return os;
}

std::istream& operator>>(std::istream& is, Complex& i)
{
        is >> i.real >> i.imag;
        return is;
}




void insertionSort(Complex* arr, int n)
{
    int i, j;
    Complex key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

