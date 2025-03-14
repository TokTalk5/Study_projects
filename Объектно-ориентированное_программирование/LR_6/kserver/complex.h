#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>

class TComplex {
private:
    double real;
    double imag;

public:
    TComplex();
    TComplex(double real, double imag);
    TComplex(double real);
    double getReal() const; // прием вещественной части
    double getImag() const; // прием мнимой части

    //оператор операций
    TComplex operator+(const TComplex& other) const;
    TComplex operator-(const TComplex& other) const;
    TComplex operator*(const TComplex& other) const;
    TComplex operator/(const TComplex& other) const;
    TComplex& operator*=(const double& scalar);
    TComplex& operator*=(const TComplex& other);
    TComplex& operator-=(const TComplex& other);
    TComplex conjugate() const;
    double magnitude() const;

    void print() const; // вывод

    // Перегрузка операторов
    friend std::ostream& operator<<(std::ostream& os, const TComplex& c);
    friend std::istream& operator>>(std::istream& is, TComplex& c);
};

// модуль
double abs(const TComplex& c);

#endif

