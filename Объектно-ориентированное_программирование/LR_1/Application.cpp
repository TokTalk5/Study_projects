//
// Created by tokar on 18.02.2024.
//

#include "Application.h"
#include <iostream>
#include "Matrix.h"
#include "number.h"
using namespace std;

Application::Application(){

}

int Application::exec() {
    int ch;
    SquareMatrix matrix = SquareMatrix();
    matrix.generate_1();
    number n;
    while (true){
        ch = menu();
        switch (ch){
            case 1:
            {
                cout << "enter matrix dimensions\n";
                cout << "n= ";
                cin >> n;
                cout << "enter coefficient matrices\n";
                SquareMatrix Matrix (n,n);
                Matrix.CinMatrix();
                matrix = Matrix;}
                break;
            case 2: //- определителя матрицы и вывод результатов расчета;
                cout << "Determinant: "<< matrix.determinantGaussJordan()<< endl;
                break;
            case 3:{
                SquareMatrix Tmatrix = SquareMatrix();
                Tmatrix = matrix.transpose();
                Tmatrix.print_screen();
                matrix = Tmatrix;
            }
                break;
            case 4://- ранга матрицы и вывод результатов расчета;
                cout << "Rank: "<< matrix.rank()<< endl;
                break;
            case 5:
                matrix.print_screen();
                break;
            case 0:
                return 0;
            default:
                break;
        }
    }
}

int Application::menu() {
    int ch;
    cout << "0 -- exit\n"                           //- выход из приложения
            "1 -- input of matrix coefficients\n"   //- ввод с консоли значений, задающих объект матрицы (до ввода задана матрица по умолчанию);
            "2 -- calculate determinant\n"          //- определителя матрицы и вывод результатов расчета;
            "3 -- transpose matrix\n"               //- транспонированной матрицы и ее вывода в консоль;
            "4 -- calculate rank\n"                 //- ранга матрицы и вывод результатов расчета;
            "5 -- print matrix"<< endl << "> ";     //- представление в консоль текущего объекта матрицы;
    cin >> ch;
    return ch;
}