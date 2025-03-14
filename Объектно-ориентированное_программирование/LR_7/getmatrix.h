#ifndef GETMATRIX_H
#define GETMATRIX_H
#include <QVector>
#include <QTextStream>
#include <QFile>

class GetMatrix
{
private:
    QVector <QVector<int>> matrix;
    QString pathFile;
public:
    GetMatrix(QString);
    QVector <QVector<int>> getFullMatrix();
    int checkMatrix();
};

#endif // GETMATRIX_H
