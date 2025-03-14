#include "Application.h"
#include <iostream>
#include "Matrix.h"
#include "number.h"
using namespace std;


ConsoleApplication::ConsoleApplication(){}


int ConsoleApplication::execute() {
    int choice;
    SquareMatrix matrix; 
    int matrixSize;
    while (true){
        choice = menu();
        if (choice == 1) {
            // ввод размеров
            cout << "enter matrix dimensions\n";
            cout << "n= ";
            cin >> matrixSize;
            if (matrixSize <= 0) {
                cout << "Invalid matrix size. Please enter a positive integer." << endl;
                continue;
            }
            // ввод значений
            cout << "enter coefficient matrices\n";
            SquareMatrix inputMatrix(matrixSize, matrixSize);
            inputMatrix.inputMatrix();
            matrix = inputMatrix;
        } else if (choice == 2) {      // определитель
            cout << "Determinant: "<< matrix.calculateDeterminant()<< endl;
        } else if (choice == 3) {     // транспонирование
            SquareMatrix transposedMatrix = matrix.transposeMatrix();
            transposedMatrix.displayMatrix();
            matrix = transposedMatrix;
        } else if (choice == 4) {    // ранг
            cout << "Rank: "<< matrix.calculateRank()<< endl;
        } else if (choice == 5) {    // вывод
            matrix.displayMatrix();
        } else if (choice == 0) {   // выход
            return 0;
        } else {
            cout << "Invalid choice. Please enter a number from the menu." << endl;
        }
    }
}

// вывод меню
int ConsoleApplication::menu() {
    int choice;
    cout << "0. exit\n"
            "1. input of matrix\n"
            "2. determinant\n"
            "3. transpose\n"
            "4. rank\n"
            "5. print matrix"<< endl << "> ";
    cin >> choice;
    return choice;
}

// Основа
int main() {
    ConsoleApplication application;
    return application.execute();
}

