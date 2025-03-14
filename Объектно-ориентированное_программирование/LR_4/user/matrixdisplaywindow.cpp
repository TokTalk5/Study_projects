#include "matrixdisplaywindow.h"

MatrixDisplayWindow::MatrixDisplayWindow(QWidget *parent)
    : QDialog(parent), layout(new QVBoxLayout(this)) {
    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);
    setLayout(layout);
}

void MatrixDisplayWindow::displayMatrix(const std::stringstream &matrixText) {
    textEdit->setPlainText(matrixText.str().c_str());
}
