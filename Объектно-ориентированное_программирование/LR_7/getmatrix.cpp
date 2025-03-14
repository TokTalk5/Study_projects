#include "getmatrix.h"


GetMatrix::GetMatrix(QString t)
{
    pathFile = t;
}


int GetMatrix::checkMatrix()
{
    matrix.clear();
    QFile file(pathFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("File wasn't open");
        return 1;
    }
    else
    {
        QTextStream in(&file);
        int columnCount = 0;
        int rowCount = 0;
        QString columnLine = in.readLine();
        for (auto t:columnLine)
        {
            if (t == ' ')
                columnCount++;
        }
        columnCount--;
        while (!in.atEnd()) {
            QString temp = in.readLine();
            QVector<int> rows;
            for (int i = 1; i < temp.size(); i++)
            {
                if (temp.at(i)!= '|')
                {
                    rows.push_back(temp[i].digitValue());
                    if ((temp[i].digitValue() > 1) || (temp[i].digitValue() < 0))
                    {
                        qWarning("Not 0 or 1");
                        matrix.clear();
                        return 2;
                    }
                }
            }
            matrix.push_back(rows);
            rowCount++;
        }
        if(rowCount!=columnCount)
        {
            qWarning("Matrix not square");
            matrix.clear();
            return 3;
        }
    }
    return 0;
}

QVector <QVector<int>> GetMatrix::getFullMatrix()
{
    return matrix;
}
