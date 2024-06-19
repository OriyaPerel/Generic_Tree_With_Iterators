// #include <iostream>

// class Complex {
// public:
//     double real;
//     double imag;

//     Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

//     double get_real() const { return real; }
//     double get_imag() const { return imag; }

//     // Overload the + operator to add two Complex numbers.
//     Complex operator+(const Complex& other) const ;

//     bool operator>(const Complex& other) const ;

//     bool operator==(const Complex& other) const ;


//     //friend std::ostream& operator<<(std::ostream& os, const Complex& c);

//     friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
//         os << "(" << c.real << ", " << c.imag << "!)";
//         return os;
//     }
// };
#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex {
private:
    double real, imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex operator+(const Complex &other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    bool operator>(const Complex &other) const {
        return (real > other.real) && (imag > other.imag);
    }

    bool operator==(const Complex &other) const {
        return (real == other.real) && (imag == other.imag);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << "+" << c.imag << "!)";
        return os;
    }
};

#endif
