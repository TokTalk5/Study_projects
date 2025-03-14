#include "SquareMatrix.h"
#include <iostream>
#include <iomanip>
using namespace std;


SquareMatrix::SquareMatrix(int n){
    new Matrix (n);
}
number SquareMatrix::calculateDeterminant() const {
    if (matrixRows != matrixCols) {
        throw std::invalid_argument("Matrix must be square to calculate its determinant.");
    }
    SquareMatrix LU = luDecomposition();
    number det = TRational(1, 1);
    for (int i = 0; i < matrixRows; ++i) {
        det *= LU.matrixValues[i][i];
    }
    return det;
}

SquareMatrix SquareMatrix::luDecomposition() const {
    if (matrixRows != matrixCols) {
        throw std::invalid_argument("Matrix must be square for LU decomposition.");
    }
    SquareMatrix LU = *this;
    for (int i = 0; i < matrixRows - 1; ++i) {
        for (int j = i + 1; j < matrixRows; ++j) {
            number factor = LU.matrixValues[j][i] / LU.matrixValues[i][i];
            for (int k = i; k < matrixRows; ++k) {
                LU.matrixValues[j][k] -= factor * LU.matrixValues[i][k];
            }
        }
    }
    return LU;
}

int SquareMatrix::calculateRank() {
    SquareMatrix LU = luDecomposition();
    int rank = 0;
    for (int i = 0; i < matrixRows; ++i) {
        if (LU.matrixValues[i][i].getAbsoluteValue() > 1e-10) {
            rank++;
        }
    }
    return rank;
}



