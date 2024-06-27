#ifndef COMPLEX_HPP
#define COMPLEX_HPP
// id:322522806
// email:oriyaperel18@gmail.com

#include <iostream>

class Complex
{
private:
    double real, imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    double get_real() const { return real; }

    double get_imag() const { return imag; }

    Complex operator+(const Complex &other) const;

    bool operator>(const Complex &other) const;

    bool operator==(const Complex &other) const;
    friend std::ostream &operator<<(std::ostream &os, const Complex &c)
    {
        os << "(" << c.real << "+" << c.imag << "!)";
        return os;
    }
};

#endif
