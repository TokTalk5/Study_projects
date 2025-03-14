#include "Matrix.h"
#include <iostream>
#include <iomanip>
using namespace std;

SquareMatrix::SquareMatrix() {
    matrixRows = 0;
    matrixCols = 0;
    matrixValues.clear();
}

SquareMatrix::SquareMatrix(int rows, int cols) {
    matrixRows = rows;
    matrixCols = cols;
    matrixValues.resize(matrixRows, vector<number>(matrixCols));
}

// ввод
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

// вывод
void SquareMatrix::displayMatrix() {
    for (int i = 0; i < matrixRows; ++i) {
        for (int j = 0; j < matrixCols; ++j) {
            cout << fixed << setprecision(2) << matrixValues[i][j] << " ";
        }
        cout << endl;
    }
}

// транспонирование
SquareMatrix SquareMatrix::transposeMatrix() {
    SquareMatrix transposedMatrix(matrixCols, matrixRows);
    for (size_t i = 0; i < matrixRows; i++) {
        for (size_t j = 0; j < matrixCols; j++) {
            transposedMatrix.matrixValues[j][i] = matrixValues[i][j];
        }
    }
    return transposedMatrix;
}

// определитель
number SquareMatrix::calculateDeterminant() const {
    SquareMatrix LU = luDecomposition();
    number det = 1.0;
    for (int i = 0; i < matrixRows; ++i) {
        det *= LU.matrixValues[i][i];
    }
    return det;
}

// разложение матрцы
SquareMatrix SquareMatrix::luDecomposition() const {
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
// ранг
int SquareMatrix::calculateRank() {
    SquareMatrix LU = luDecomposition();
    int rank = 0;
    for (int i = 0; i < matrixRows; ++i) {
        if (abs(LU.matrixValues[i][i]) > 1e-10) {
            rank++;
        }
    }
    return rank;
}

