#ifndef APPlICATION_H
#define APPlICATION_H

#include "interface.h"
#include "../communicator/communicator.h"
#include <QApplication>

class application: public QApplication
{
    Q_OBJECT

public:
    application(int , char **);

public slots:
    void dove(QString);
    void postOffice(QString);

private:
    interface *Interface;
    TCommunicator *comms;
};

#endif // APPlICATION_H
