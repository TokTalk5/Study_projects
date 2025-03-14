#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

#include "number.h"
#include <iostream>
#include <vector>
using namespace std;

class SquareMatrix {
    int m_rows, m_cols;
    vector<vector<number>> m_values;
public:
    SquareMatrix();                         // по умолчанию создается пустая матрица
    SquareMatrix (number rows, number cols);// выделяет память, элементы не инициализирует
    void generate_1();                      // заполняет единичную матрицу
    void print_screen();                    // вывод матрицы
    number determinantGaussJordan() const;
    SquareMatrix transpose();               // транспонирование матрицы
    void CinMatrix ();//ввод пользовательской матрицы
    int rows() const;
    int cols() const;
    int rank();
};


#endif //UNTITLED_MATRIX_H

