 #include "Complex.hpp"
 // id:322522806
// email:oriyaperel18@gmail.com
 
 
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

   
