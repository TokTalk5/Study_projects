#ifndef APPLICATION_H
#define APPLICATION_H

#include "../communicator/communicator.h"
#include <QCoreApplication>
#include "Matrix.h"
#include <QStringList>

class application: public QCoreApplication
{
    Q_OBJECT

public:
    application(int , char **);
    QString answer (int n);

public slots:
    void takeMessage(QString);

private:
    TCommunicator *comms;
    SquareMatrix * matrix;
    number det;
    int rank;
signals:
    void recieved(const QString& message);
};

#endif // APPLICATION_H
