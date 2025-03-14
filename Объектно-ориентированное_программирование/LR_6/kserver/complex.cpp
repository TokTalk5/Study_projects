#include "complex.h"
#include <iostream>
#include <cmath>
#include <iomanip>


TComplex::TComplex() : real(0), imag(0) {}

TComplex::TComplex(double real, double imag) : real(real), imag(imag) {}

TComplex::TComplex(double real) : real(real), imag(0) {}

double TComplex::getReal() const {
    return real;
}

double TComplex::getImag() const {
    return imag;
}

TComplex TComplex::operator+(const TComplex& other) const {
    return TComplex(real + other.real, imag + other.imag);
}

TComplex TComplex::operator-(const TComplex& other) const {
    return TComplex(real - other.real, imag - other.imag);
}

TComplex TComplex::operator*(const TComplex& other) const {
    return TComplex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
}

TComplex TComplex::operator/(const TComplex& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;
    return TComplex((real * other.real + imag * other.imag) / denominator, (imag * other.real - real * other.imag) / denominator);
}

TComplex& TComplex::operator*=(const double& scalar) {
    real *= scalar;
    imag *= scalar;
    return *this;
}

TComplex& TComplex::operator*=(const TComplex& other) {
    double tempReal = real * other.real - imag * other.imag;
    double tempImag = real * other.imag + imag * other.real;
    real = tempReal;
    imag = tempImag;
    return *this;
}

TComplex& TComplex::operator-=(const TComplex& other) {
    real -= other.real;
    imag -= other.imag;
    return *this;
}

TComplex TComplex::conjugate() const {
    return TComplex(real, -imag);
}

double TComplex::magnitude() const {
    return sqrt(real * real + imag * imag);
}

void TComplex::print() const {
    std::cout << std::fixed << std::setprecision(2) << real << " + " << imag << "i" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const TComplex& c) {
    os << std::fixed << std::setprecision(2) << c.getReal() << " + " << c.getImag() << "i";
    return os;
}

std::istream& operator>>(std::istream& is, TComplex& c) {
    double real, imag;
    char plusOrMinus;
    is >> real >> plusOrMinus >> imag;
    if (plusOrMinus == '-') {
        imag = -imag;
    }
    c = TComplex(real, imag);
    return is;
}

double abs(const TComplex& c) {
    return c.magnitude();
}



