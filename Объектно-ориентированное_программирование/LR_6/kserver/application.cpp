#include "application.h"

application::application(int argc, char* argv[]):QCoreApplication(argc, argv){
    TCommonParam params = {
        QHostAddress::LocalHost,
         22222, 11111

    };
    this->comms = new TCommunicator(params);
     connect(this->comms, SIGNAL(recieved(QString)), this, SLOT(takeMessage(QString)));
}

QString application :: answer ( int n){
    QString request;
    request +=QString::number(n)+ "_"; // Номер_размер_матрица
    if ((n == 4) or (n == 2)){
        int sizeMatrix = this -> matrix -> getCols();
        request +=QString::number(sizeMatrix) + "_";
        for (int i = 0; i < sizeMatrix; ++i) {
            for (int j = 0; j < sizeMatrix; ++j) {
                    int numerator, denominator;
                    request +=QString::number(numerator) + "/" + QString::number(denominator) + ";";
            }
        }
    }
    if (n == 1){
        request +=det.toString();

    }
    if (n == 3){
        request +=QString::number(rank);

    }
    if (n == 5){
        request += "saved";
    }

    this->comms->send(request);
}

void application:: takeMessage(QString message){
    QStringList array, matrixArray;
    if (message != "") printf("E");
    array = message.split("_");

    if (array.size() == 1){
        if (array[0].toInt() == 1){
            //determinant
           det = this ->matrix -> calculateDeterminant();
           answer(array[0].toInt());
           printf("determinant done/n");

        }
        if (array[0].toInt() == 3){
            //rank
            rank = this ->matrix -> calculateRank();
            answer(array[0].toInt());
            printf("rank done/n");
        }
        if (array[0].toInt() == 2){
            //transpose
            this ->matrix -> transposeMatrix();
            answer(array[0].toInt());
            printf("transpose done/n");
        }
        if (array[0].toInt() == 4){
            //print
            answer(array[0].toInt());
            printf("print done/n");
        }
    }
    if (array.size() == 3){
        //save
        matrixArray = array[2].split(";");
        int size = array[1].toInt();
        int count = 0;
        //this -> matrix-> Squarematrix(size);
        for (int i = 0; i < size; i++){
            for (int j=0; j < size; j++){
                QStringList value = matrixArray[count].split("/");
                int numerator = value[0].toInt();
                int determinator = value[1].toInt();
                this->matrix->setMatrixValue(i,j,numerator, determinator);
                count ++;
            }
        }
        answer(array[0].toInt());
        printf("save done/n");
    }

    }




