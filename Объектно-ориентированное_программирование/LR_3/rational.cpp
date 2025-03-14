#include "rational.h"

TRational::TRational() : numerator(0), denominator(1) {}

TRational::TRational(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
    simplify();
}

TRational::TRational(const TRational& other) : numerator(other.numerator), denominator(other.denominator) {}

TRational& TRational::operator=(const TRational& other) {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

TRational& TRational::operator*=(const TRational& other) {
    numerator *= other.numerator;
    denominator *= other.denominator;
    simplify();
    return *this;
}

TRational& TRational::operator-=(const TRational& other) {
    numerator -= other.numerator * denominator / other.denominator;
    simplify();
    return *this;
}

int TRational::getAbsoluteValue() const {
    return std::abs(numerator);
}

int TRational::getNumerator() const {
    return numerator;
}

int TRational::getDenominator() const {
    return denominator;
}

TRational TRational::operator+(const TRational& other) const {
    int newNumerator = numerator * other.denominator + other.numerator * denominator;
    int newDenominator = denominator * other.denominator;
    return TRational(newNumerator, newDenominator);
}

TRational TRational::operator-(const TRational& other) const {
    int newNumerator = numerator * other.denominator - other.numerator * denominator;
    int newDenominator = denominator * other.denominator;
    return TRational(newNumerator, newDenominator);
}

TRational TRational::operator*(const TRational& other) const {
    int newNumerator = numerator * other.numerator;
    int newDenominator = denominator * other.denominator;
    return TRational(newNumerator, newDenominator);
}

TRational TRational::operator/(const TRational& other) const {
    if (other.numerator == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    int newNumerator = numerator * other.denominator;
    int newDenominator = denominator * other.numerator;
    return TRational(newNumerator, newDenominator);
}

bool TRational::operator==(const TRational& other) const {
    return numerator * other.denominator == other.numerator * denominator;
}

bool TRational::operator!=(const TRational& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const TRational& rational) {
    os << rational.numerator << "/" << rational.denominator;
    return os;
}

std::istream& operator>>(std::istream& is, TRational& rational) {
    int numerator, denominator;
    char slash;
    is >> numerator >> slash >> denominator;
    if (denominator == 0) {
        is.setstate(std::ios::failbit);
    } else {
        rational = TRational(numerator, denominator);
    }
    return is;
}

void TRational::simplify() {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero.");
    }
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    int gcdValue = gcd(numerator, denominator);
    numerator /= gcdValue;
    denominator /= gcdValue;
}

int TRational::gcd(int a, int b) const {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

QString TRational::toString() const {
    return QString("%1/%2").arg(getNumerator()).arg(getDenominator());}


