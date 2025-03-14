#include "Matrix.h"
#include <iostream>
#include <iomanip>
using namespace std;

SquareMatrix::SquareMatrix() {
    matrixRows = 0;
    matrixCols = 0;
    matrixValues.clear();
}

void SquareMatrix::Squarematrix(int size) {
    if (size <= 0) {
        throw std::invalid_argument("Matrix size must be a positive integer.");
    }
    matrixRows = size;
    matrixCols = size;
    matrixValues.resize(matrixRows, vector<number>(matrixCols));
}

void SquareMatrix::inputMatrix() {
    for (size_t i = 0; i < matrixRows; ++i) {
        for (size_t j = 0; j < matrixCols; ++j) {
            cout << "\nmatrix [" << i << "][" << j << "] = ";
            cin >> matrixValues[i][j];
        }
    }
}

int SquareMatrix::getRows() const { return matrixRows;}

int SquareMatrix::getCols() const { return matrixCols;}

void SquareMatrix::displayMatrix() {
    for (int i = 0; i < matrixRows; ++i) {
        for (int j = 0; j < matrixCols; ++j) {
            cout << fixed << setprecision(2) << matrixValues[i][j] << " ";
        }
        cout << endl;
    }
}

void SquareMatrix::transposeMatrix() {
   // SquareMatrix transposedMatrix(matrixRows);
    for (size_t i = 0; i < matrixRows; i++) {
        for (size_t j = 0; j < i; j++) {
          this ->matrixValues[j][i] = matrixValues[i][j];
        }
    }
    //return matrix;
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

void SquareMatrix:: setMatrixValue(int Row, int Col, int numerator, int determinator){
    if (Row >= 0 && Row < matrixRows && Col >= 0 && Col < matrixCols) {
                matrixValues[Row][Col] = TRational (numerator, determinator) ;
            }
}
number SquareMatrix::getMatrixValue(int row, int col) const {
    if (row >= 0 && row < matrixRows && col >= 0 && col < matrixCols) {
        return matrixValues[row][col];
    } else {
        throw std::out_of_range("Index out of matrix bounds.");
    }
}

