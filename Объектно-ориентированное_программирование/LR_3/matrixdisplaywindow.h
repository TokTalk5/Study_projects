#ifndef MATRIXDISPLAYWINDOW_H
#define MATRIXDISPLAYWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QWidget>
#include <QString>
#include <qstring.h>
#include "Matrix.h"

class MatrixDisplayWindow : public QDialog {
    Q_OBJECT

public:
    explicit MatrixDisplayWindow(QWidget *parent = nullptr);

    void displayMatrix(const SquareMatrix& matrix);

private:
    QVBoxLayout *layout;
    QTextEdit *textEdit;
};

#endif // MATRIXDISPLAYWINDOW_H
