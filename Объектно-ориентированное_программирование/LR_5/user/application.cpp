#include "application.h"

application::application(int argc, char* argv[]):QApplication(argc, argv){
    TCommonParam params = {
        QHostAddress::LocalHost,
        11111, 22222
    };
    this->Interface = new interface();
    this->comms = new TCommunicator(params);
     this->Interface->show();
     connect(this->Interface, SIGNAL(SENDER(QString)), this, SLOT(dove(QString)));
     connect(this->comms, SIGNAL(recieved(QString)), this, SLOT(postOffice(QString)));
}

void application::dove(QString msg){
    this->comms->send(msg);
}

void application::postOffice(QString msg){
    this->Interface->answerMessage(msg);
}
