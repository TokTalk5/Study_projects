#ifndef MATRIX_H
#define MATRIX_H
#include "number.h"
#include <iostream>
#include <vector>
using namespace std;

class SquareMatrix {
    int matrixRows, matrixCols;
    vector<vector<number>> matrixValues;
public:
    SquareMatrix();
    SquareMatrix(int size);
    void displayMatrix();
    number calculateDeterminant() const;
    SquareMatrix transposeMatrix();
    void inputMatrix();
    int calculateRank();
    int getRows() const;
    int getCols() const;
    void setMatrixValue(int Row, int Col, int numerator, int determinator);
    number getMatrixValue(int row, int col) const;
private:
    SquareMatrix luDecomposition() const;
};

#endif //MATRIX_H






