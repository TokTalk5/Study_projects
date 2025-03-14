#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H
#include "number.h"
#include <iostream>
#include <vector>
#include "matrix.h"
using namespace std;

class SquareMatrix: public Matrix {
public:
    SquareMatrix(int n);
   number calculateDeterminant() const;
    int calculateRank();
private:
    SquareMatrix luDecomposition() const;

};

#endif //SQUAREMATRIX_H






