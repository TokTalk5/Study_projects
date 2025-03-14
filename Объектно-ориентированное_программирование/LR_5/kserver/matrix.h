#ifndef MATRIX_H
#define MATRIX_H
#include "number.h"
#include <iostream>
#include <vector>
using namespace std;

class Matrix {
protected:
    int matrixRows, matrixCols;
    vector<vector<number>> matrixValues;
public:
    Matrix();
    Matrix(int size);
    void displayMatrix();
    void transposeMatrix();
    void inputMatrix();
    int getRows() const;
    int getCols() const;
    void setMatrixValue(int Row, int Col, int numerator, int determinator);
    number getMatrixValue(int row, int col) const;
};

#endif //MATRIX_H
