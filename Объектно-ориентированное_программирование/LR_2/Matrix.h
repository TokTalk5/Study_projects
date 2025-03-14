#ifndef MATRIX_H
#define MATRIX_H
#include "number.h"
#include <iostream>
#include <vector>
using namespace std;


class SquareMatrix {
    int matrixRows, matrixCols;
    vector<vector<number>> matrixValues;
private:
    SquareMatrix luDecomposition() const; // разложение матрицы
public:
    SquareMatrix();
    SquareMatrix(int rows, int cols);
    void displayMatrix();                              // вывод матрицы
    number calculateDeterminant() const;              // опередитель
    SquareMatrix transposeMatrix();                  // транспонирование
    void inputMatrix();                             // ввод значений
    int calculateRank();                           // ранг
    int getRows() const;                          //к-во строк
    int getCols() const;                         //к-во столбцов
};

#endif //MATRIX_H
