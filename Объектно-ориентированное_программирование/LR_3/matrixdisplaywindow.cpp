#include "matrixdisplaywindow.h"

MatrixDisplayWindow::MatrixDisplayWindow(QWidget *parent)
    : QDialog(parent), layout(new QVBoxLayout(this)) {
    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);
    setLayout(layout);
}

void MatrixDisplayWindow::displayMatrix(const SquareMatrix& matrix) {
    QString matrixText;
    for (int i = 0; i < matrix.getRows(); ++i) {
        for (int j = 0; j < matrix.getCols(); ++j) {
            QString value = matrix.getMatrixValue(i, j).toString();
            matrixText += value + " ";
        }
        matrixText += "\n";
    }
    textEdit->setPlainText(matrixText);
}
