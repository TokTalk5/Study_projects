#include "interface.h"
#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <sstream>
#include "matrixdisplaywindow.h"

interface::interface(QWidget *parent) : QWidget(parent)
{
    // Создаем кнопку
    exitButton = new QPushButton("Выход", this);
    inputMatrixButton = new QPushButton("Входная матрица", this);
    determinantButton = new QPushButton("Определитель", this);
    transposeButton = new QPushButton("Транспонировать", this);
    rankButton = new QPushButton("Ранг", this);
    printMatrixButton = new QPushButton("Распечатать матрицу", this);
    saveMatrixButton = new QPushButton("Сохранить матрицу", this);

    // Создаем виджеты для ввода размерности матрицы и отображения результатов
    resultLabel = new QLabel(this);

    // Создаем макет макета
    layout = new QVBoxLayout(this);
    layout->addWidget(exitButton);
    layout->addWidget(inputMatrixButton);
    layout->addWidget(saveMatrixButton);
    layout->addWidget(determinantButton);
    layout->addWidget(transposeButton);
    layout->addWidget(rankButton);
    layout->addWidget(printMatrixButton);
    layout->addWidget(resultLabel);

    // Создаем макет для полей ввода элементов матрицы
    matrixInputLayout = new QGridLayout();
    layout->addLayout(matrixInputLayout);

    // Подключаем сигналы к слотам
    connect(exitButton, &QPushButton::clicked, this, &interface::exitApp);
    connect(inputMatrixButton, &QPushButton::clicked, this, &interface::inputMatrix);
    connect(determinantButton, &QPushButton::clicked, this, &interface::calculateDeterminant);
    connect(transposeButton, &QPushButton::clicked, this, &interface::transposeMatrix);
    connect(rankButton, &QPushButton::clicked, this, &interface::calculateRank);
    connect(printMatrixButton, &QPushButton::clicked, this, &interface::printMatrix);
    connect(saveMatrixButton, &QPushButton::clicked, this, &interface::readMatrixFromInput);
}

void interface::exitApp() {
    QApplication::quit();
}
QString interface :: requestForm( int n){
    QString request;
    request +=QString::number(n)+ "_"; // Номер_размер_матрица
    if (n == 5){
        request +=QString::number(sizeMatrix) + "_";
        for (int i = 0; i < sizeMatrix; ++i) {
            for (int j = 0; j < sizeMatrix; ++j) {
                QLineEdit* input = qobject_cast<QLineEdit*>(matrixInputLayout->itemAtPosition(i, j)->widget());
                if (input) {
                    int numerator, denominator;
                    if (sscanf(input->text().toStdString().c_str(), "%d/%d", &numerator, &denominator) == 2) {
                        request +=QString::number(numerator) + "/" + QString::number(denominator) + ";";
                    }
                }
            }
        }
    }
    return request;
}

void interface::answerMessage(QString message){
    QStringList array, matrixArray;
    std::stringstream matrixs;
    array = message.split("_");
    if (array.size() == 2){
        if (array[0].toInt() == 5){
            //save
            resultLabel->setText("Матрица сохранена успешно");
        }
        if (array[0].toInt() == 1){
            //determinant
            QString det = array[1];
            resultLabel->setText("Определитель: " + det);
        }
        if (array[0].toInt() == 3){
            //rank
            int rank = array[1].toInt();
            resultLabel->setText("Ранг: " + QString::number(rank));

        }
     }
    if (array.size() == 3){
        matrixArray = array[2].split(";");
        int size = array[1].toInt();
        int count = 0;
        for (int i = 0; i < size; i++){
            for (int j=0; j < size; j++){
                matrixs << matrixArray[count].toStdString() << " ";
                count ++;
            }
            matrixs << "\n";
        }
        MatrixDisplayWindow *matrixDisplayWindow = new MatrixDisplayWindow(this);
        matrixDisplayWindow->displayMatrix(matrixs);
        matrixDisplayWindow->show();

    }
    else{
        resultLabel->setText("Матрица отсутствует");
    }
}

void interface::inputMatrix() {
    bool ok;
    int size = QInputDialog::getInt(this, "Размер входной матрицы", "Введите размер матрицы:", 1, 1, 100, 1, &ok);
    if (ok) {
        // Очищаем окно ввода
        qDeleteAll(matrixInputLayout->children());

        // Создаем поля ввода для элементов матрицы
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                QLineEdit* input = new QLineEdit(this);
                matrixInputLayout->addWidget(input, i, j); // Добавляем виджеты без предварительного просмотра размеров
            }
        }

        //matrix = SquareMatrix(size);
        sizeMatrix = size;
        resultLabel->setText("Поля ввода матрицы созданы.");
    }
}



void interface::calculateDeterminant() {
   QString request = requestForm(1);
   emit SENDER(request);
}

void interface::transposeMatrix() {
    QString request = requestForm(2);
    emit SENDER(request);
}

void interface::calculateRank() {
    QString request = requestForm(3);
    emit SENDER(request);

}

void interface::printMatrix() {
    QString request = requestForm(4);
    emit SENDER(request);
}

void interface::readMatrixFromInput() {
    QString request = requestForm(5);
    emit SENDER(request);

}

void interface::handleReceivedMessage(const QString& message) {
    qDebug() << "Получено сообщение: " << message;
}
