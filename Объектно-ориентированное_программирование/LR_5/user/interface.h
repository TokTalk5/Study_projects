#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>


class interface : public QWidget
{
    Q_OBJECT
public:
   // SquareMatrix matrix;
    explicit interface(QWidget *parent = nullptr);

    // Добавлен метод для обработки полученных сообщений
    void handleReceivedMessage(const QString& message);
    void answerMessage(QString message);
    QString requestForm(int n);

signals:
    void SENDER(QString);

private slots:
    void exitApp();
    void inputMatrix();
    void calculateDeterminant();
    void transposeMatrix();
    void calculateRank();
    void printMatrix();
    void readMatrixFromInput();


private:
    int sizeMatrix;
    QPushButton* exitButton;
    QPushButton* inputMatrixButton;
    QPushButton* saveMatrixButton;
    QPushButton* determinantButton;
    QPushButton* transposeButton;
    QPushButton* rankButton;
    QPushButton* printMatrixButton;
    QLineEdit* matrixSizeInput;
    QLabel* resultLabel;
    QVBoxLayout* layout;
    QGridLayout* matrixInputLayout;
};

#endif // INTERFACE_H
