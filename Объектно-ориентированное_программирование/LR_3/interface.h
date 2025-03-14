#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include "Matrix.h"
#include "matrixdisplaywindow.h"

class interface : public QWidget
{
    Q_OBJECT
public:
    explicit interface(QWidget *parent = nullptr);

private slots:
    void exitApp();
    void inputMatrix();
    void saveMatrix();
    void calculateDeterminant();
    void transposeMatrix();
    void calculateRank();
    void printMatrix();
    void readMatrixFromInput();

private:
    SquareMatrix matrix;
    QPushButton* exitButton;
    QPushButton* inputMatrixButton;
    QPushButton* saveMatrixButton;
    QPushButton* determinantButton;
    QPushButton* transposeButton;
    QPushButton* rankButton;
    QPushButton* printMatrixButton;
    QLineEdit* matrixSizeInput;
    QLabel* resultLabel;
    QVBoxLayout* layout;
    QGridLayout* matrixInputLayout;
};

#endif // INTERFACE_H











