//
// Created by tokar on 18.02.2024.
//
#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <cmath>
using namespace std;

// создает пустую матрицу
SquareMatrix::SquareMatrix() {
    m_rows = 3;
    m_cols = 3;
    m_values.resize(m_rows, vector<number>(m_cols));
}

// выделяем память
SquareMatrix::SquareMatrix(number cols, number rows) {
    m_rows = rows;
    m_cols = cols;
    m_values.resize(m_cols, vector<number>(m_rows));
}

//заполняем единичную матрицу
void SquareMatrix::generate_1() {
    for (number i = 0; i < m_rows; ++i) {
        for (number j = 0; j < m_cols; ++j) {
            //cout << "\nmatrix [" << i << "][" << j << "] = ";
            if (i == j) {
                m_values[i][j] = 1;}
            else {
                m_values[i][j] = 0;}
        }}
}

//выподим матрицу пользователя
void SquareMatrix::CinMatrix() {
    for (size_t i =  0; i < m_rows; ++i) {
        for (size_t j =  0; j < m_cols; ++j) {
            cout << "\nmatrix [" << i << "][" << j << "] = ";
            cin >> m_values[i][j];
        }
    }
}

int SquareMatrix::rows() const { return m_rows;}

int SquareMatrix::cols() const { return m_cols;}

//выводим матрицу
void SquareMatrix::print_screen() {
    for (int i =  0; i < m_rows; ++i) {
        for (int j =  0; j < m_cols; ++j) {
            cout << fixed << setprecision(1) << m_values[i][j] << " ";
        }
        cout << endl;
    }
}

//считаем определитель
double SquareMatrix::determinantGaussJordan() const {
    if (m_rows != m_cols) {
        throw std::invalid_argument("Matrix must be square.");
    }

    int n = m_rows;
    vector<vector<double>> tempMatrix = m_values; // Copy the matrix

    // Transform the matrix to upper triangular form
    for (int i =  0; i < n; ++i) {
        int maxRowIndex = i;
        for (int row = i +  1; row < n; ++row) {
            if (abs(tempMatrix[row][i]) > abs(tempMatrix[maxRowIndex][i])) {
                maxRowIndex = row;
            }
        }
        if (maxRowIndex != i) {
            swap(tempMatrix[i], tempMatrix[maxRowIndex]);
        }
        if (tempMatrix[i][i] ==  0) {
            // If the matrix is singular, return  0 as the determinant is not defined
            return  0;
        }
        double divisor = tempMatrix[i][i];
        for (int col = i; col < n; ++col) {
            tempMatrix[i][col] /= divisor;
        }
        for (int row = i +  1; row < n; ++row) {
            double factor = tempMatrix[row][i];
            for (int col = i; col < n; ++col) {
                tempMatrix[row][col] -= factor * tempMatrix[i][col];
            }
        }
    }

    // Multiply the diagonal elements
    double det =  1;
    for (int i =  0; i < n; ++i) {
        det *= tempMatrix[i][i];
    }
    return det;
}







//транспонируем
SquareMatrix SquareMatrix::transpose() {
    SquareMatrix other(m_cols, m_rows);
    for(size_t i = 0; i < m_rows; i++) {
        for(size_t j = 0; j < m_cols; j++) {
            other.m_values[j][i] = m_values[i][j];
        }
    }
    return other;
}

//считаем ранг

int SquareMatrix:: rank() {
    std::vector<std::vector<double>> tempMatrix = m_values;
    int rank =  0;

    for (int i =  0; i < m_rows; ++i) {
        // Находим строку с максимальным элементом в текущем столбце
        int maxRowIndex = i;
        for (int row = i +  1; row < m_rows; ++row) {
            if (std::abs(tempMatrix[row][i]) > std::abs(tempMatrix[maxRowIndex][i])) {
                maxRowIndex = row;
            }
        }
        // Переставляем строки, если нужно
        if (maxRowIndex != i) {
            std::swap(tempMatrix[i], tempMatrix[maxRowIndex]);
        }
        // Если элемент на главной диагонали равен нулю, то переходим к следующей строке
        if (tempMatrix[i][i] ==  0) {
            continue;
        }

        // Нормализуем строку
        double divisor = tempMatrix[i][i];
        for (int col = i; col < m_cols; ++col) {
            tempMatrix[i][col] /= divisor;
        }
        // Вычитаем из всех строк под главной строкой, умноженные на соответствующий коэффициент
        for (int row = i +  1; row < m_rows; ++row) {
            double factor = tempMatrix[row][i];
            for (int col = i; col < m_cols; ++col) {
                tempMatrix[row][col] -= factor * tempMatrix[i][col];
            }
        }
        rank++;
    }
    return rank;
};