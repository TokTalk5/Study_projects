#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <cmath>
#include <QString>

class TRational {
private:
    int numerator;
    int denominator;

public:
    TRational(); // Объявление конструктора
    TRational(int numerator, int denominator);
    TRational(const TRational& other);
    TRational& operator=(const TRational& other);
    TRational& operator*=(const TRational& other);
    TRational& operator-=(const TRational& other);
    int getAbsoluteValue() const;
    QString toString() const;
    int getNumerator() const;
    int getDenominator() const;

    TRational operator+(const TRational& other) const;
    TRational operator-(const TRational& other) const;
    TRational operator*(const TRational& other) const;
    TRational operator/(const TRational& other) const;

    bool operator==(const TRational& other) const;
    bool operator!=(const TRational& other) const;

    friend std::ostream& operator<<(std::ostream& os, const TRational& rational);
    friend std::istream& operator>>(std::istream& is, TRational& rational);

private:
    void simplify();
    int gcd(int a, int b) const;
};

#endif // RATIONAL_H
