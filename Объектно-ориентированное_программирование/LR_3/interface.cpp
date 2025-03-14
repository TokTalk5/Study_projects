#include "interface.h"
#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>

interface::interface(QWidget *parent) : QWidget(parent)
{
    // Создаем кнопки
    exitButton = new QPushButton("Exit", this);
    inputMatrixButton = new QPushButton("Input Matrix", this);
    determinantButton = new QPushButton("Determinant", this);
    transposeButton = new QPushButton("Transpose", this);
    rankButton = new QPushButton("Rank", this);
    printMatrixButton = new QPushButton("Print Matrix", this);
    saveMatrixButton = new QPushButton("Save Matrix", this);



    // Создаем виджеты для ввода размерности матрицы и отображения результатов
    resultLabel = new QLabel(this);

    // Создаем layout
    layout = new QVBoxLayout(this);
    layout->addWidget(exitButton);
    layout->addWidget(inputMatrixButton);
    layout->addWidget(saveMatrixButton);
    layout->addWidget(determinantButton);
    layout->addWidget(transposeButton);
    layout->addWidget(rankButton);
    layout->addWidget(printMatrixButton);
    layout->addWidget(resultLabel);

    // Создаем layout для полей ввода элементов матрицы
    matrixInputLayout = new QGridLayout();
    layout->addLayout(matrixInputLayout);

    // Подключаем сигналы к слотам
    connect(exitButton, &QPushButton::clicked, this, &interface::exitApp);
    connect(inputMatrixButton, &QPushButton::clicked, this, &interface::inputMatrix);
    connect(determinantButton, &QPushButton::clicked, this, &interface::calculateDeterminant);
    connect(transposeButton, &QPushButton::clicked, this, &interface::transposeMatrix);
    connect(rankButton, &QPushButton::clicked, this, &interface::calculateRank);
    connect(printMatrixButton, &QPushButton::clicked, this, &interface::printMatrix);
    connect(saveMatrixButton, &QPushButton::clicked, this, &interface::readMatrixFromInput);
}

void interface::exitApp() {
    QApplication::quit();
}

void interface::inputMatrix() {
    bool ok;
    int size = QInputDialog::getInt(this, "Input Matrix Size", "Enter matrix size:", 1, 1, 100, 1, &ok);
    if (ok) {
        // Очищаем предыдущие поля ввода
        qDeleteAll(matrixInputLayout->children());

        // Создаем поля ввода для элементов матрицы
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                QLineEdit* input = new QLineEdit(this);
                matrixInputLayout->addWidget(input, i, j); // Добавляем виджеты без предварительного установления размеров
            }
        }

        matrix = SquareMatrix(size);
        resultLabel->setText("Matrix input fields have been created.");
    }
}

void interface::saveMatrix(){



}

void interface::calculateDeterminant() {
    if (matrix.getRows() > 0) {
        number det = matrix.calculateDeterminant();
        resultLabel->setText("Determinant: " + det.toString());
    } else {
        resultLabel->setText("Matrix is not created.");
    }
}

void interface::transposeMatrix() {
    if (matrix.getRows() > 0) {
        SquareMatrix transposedMatrix = matrix.transposeMatrix();
        MatrixDisplayWindow *matrixDisplayWindow = new MatrixDisplayWindow(this);
        matrixDisplayWindow->displayMatrix(transposedMatrix);
        matrixDisplayWindow->exec();
        resultLabel->setText("transposed Matrix has been printed in a new window.");
    } else {
        resultLabel->setText("Matrix is not created.");
    }

}

void interface::calculateRank() {
    if (matrix.getRows() > 0) {
        int rank = matrix.calculateRank();
        resultLabel->setText("Rank: " + QString::number(rank));
    } else {
        resultLabel->setText("Matrix is not created.");
    }
}

void interface::printMatrix() {
        if (matrix.getRows() > 0) {
            MatrixDisplayWindow *matrixDisplayWindow = new MatrixDisplayWindow(this);
            matrixDisplayWindow->displayMatrix(matrix);
            matrixDisplayWindow->exec();
            resultLabel->setText("Matrix has been printed in a new window.");
        } else {
            resultLabel->setText("Matrix is not created.");
        }
}

void interface::readMatrixFromInput() {
    for (int i = 0; i < matrix.getRows(); ++i) {
        for (int j = 0; j < matrix.getCols(); ++j) {
            QLineEdit* input = qobject_cast<QLineEdit*>(matrixInputLayout->itemAtPosition(i, j)->widget());
            if (input) {
                int numerator, denominator;
                if (sscanf(input->text().toStdString().c_str(), "%d/%d", &numerator, &denominator) == 2) {
                    matrix.setMatrixValue(i, j,numerator, denominator);
                }
            }
        }
    }
     resultLabel->setText("Martix save succesful");
}



