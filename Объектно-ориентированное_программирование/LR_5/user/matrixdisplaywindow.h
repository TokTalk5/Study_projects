#ifndef MATRIXDISPLAYWINDOW_H
#define MATRIXDISPLAYWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QWidget>
#include <QString>
#include <qstring.h>
#include "interface.h"
#include <sstream>


class MatrixDisplayWindow : public QDialog {
    Q_OBJECT

public:
    explicit MatrixDisplayWindow(QWidget *parent = nullptr);

    //void displayMatrix(SquareMatrix& matrix);
    void displayMatrix(const std::stringstream &matrixText);

private:
    QVBoxLayout *layout;
    QTextEdit *textEdit;
};

#endif // MATRIXDISPLAYWINDOW_H
