 #include "Complex.hpp"
 
 
 
 Complex Complex:: operator+(const Complex &other) const
    {
        return Complex(real + other.real, imag + other.imag);
    }

    bool Complex::operator>(const Complex &other) const
    {
        return (real > other.real) && (imag > other.imag);
    }

    bool Complex::operator==(const Complex &other) const
    {
        return (real == other.real) && (imag == other.imag);
    }

   
