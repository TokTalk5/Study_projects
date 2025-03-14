#include "matrix.h"
#include <iostream>
#include <iomanip>
using namespace std;

Matrix::Matrix() {
    matrixRows = 0;
    matrixCols = 0;
    matrixValues.clear();
}

Matrix::Matrix(int size) {
    if (size <= 0) {
        throw std::invalid_argument("Matrix size must be a positive integer.");
    }
    matrixRows = size;
    matrixCols = size;
    matrixValues.resize(matrixRows, vector<number>(matrixCols));
}

void Matrix::inputMatrix() {
    for (size_t i = 0; i < matrixRows; ++i) {
        for (size_t j = 0; j < matrixCols; ++j) {
            cout << "\nmatrix [" << i << "][" << j << "] = ";
            cin >> matrixValues[i][j];
        }
    }
}

int Matrix::getRows() const { return matrixRows;}

int Matrix::getCols() const { return matrixCols;}

void Matrix::displayMatrix() {
    for (int i = 0; i < matrixRows; ++i) {
        for (int j = 0; j < matrixCols; ++j) {
            cout << fixed << setprecision(2) << matrixValues[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::transposeMatrix() {
   // SquareMatrix transposedMatrix(matrixRows);
    for (size_t i = 0; i < matrixRows; i++) {
        for (size_t j = 0; j < i; j++) {
          this ->matrixValues[j][i] = matrixValues[i][j];
        }
    }
    //return matrix;
}

void Matrix:: setMatrixValue(int Row, int Col, int numerator, int determinator){
    if (Row >= 0 && Row < matrixRows && Col >= 0 && Col < matrixCols) {
                matrixValues[Row][Col] = TRational (numerator, determinator) ;
            }
}
number Matrix::getMatrixValue(int row, int col) const {
    if (row >= 0 && row < matrixRows && col >= 0 && col < matrixCols) {
        return matrixValues[row][col];
    } else {
        throw std::out_of_range("Index out of matrix bounds.");
    }
}

