#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

struct TCommonParam{
    QHostAddress address; // IP-адрес для отправки сообщений.
    quint16 sendPort; // Порт для отправки сообщений.
    quint16 receivePort; // Порт для приема сообщений.
};

class TCommunicator: public QUdpSocket
{
    Q_OBJECT

public:
    explicit TCommunicator(TCommonParam&, QObject *parent = nullptr);
    ~TCommunicator();
    bool isReady();
public slots:
    void send(const QString& message);// Метод для отправки сообщения.

signals:
    void recieved(const QString& message);// Сигнал, отправляемый при получении сообщения.

private slots:
    void processPendingDatagrams(); // Слот для обработки входящих датаграмм.

private:
    TCommonParam param;
    bool ready;
};

#endif // COMMUNICATOR_H
