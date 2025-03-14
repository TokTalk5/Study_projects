#include "communicator.h"

TCommunicator::TCommunicator(TCommonParam& pars, QObject *parent)
    : QUdpSocket(parent), param(pars), ready(true)
{
    bind(QHostAddress::LocalHost, param.receivePort); // Привязка сокета к порту для приема сообщений.
    connect(this, &QUdpSocket::readyRead, this, &TCommunicator::processPendingDatagrams); // Соединение сигнала readyRead сокета с слотом processPendingDatagrams.
}

TCommunicator::~TCommunicator()
{
    // Удаление указателя на сокет не требуется, так как мы наследуем от QUdpSocket
}

bool TCommunicator::isReady()
{
    return ready;
}

void TCommunicator::send(const QString& message)// Метод для отправки сообщения.
{
   if (ready) writeDatagram(message.toUtf8(), param.address, param.sendPort); // Отправка сообщения на указанный адрес и порт.
}

void TCommunicator::processPendingDatagrams()// Проверка наличия входящих датаграмм.
{
    if (hasPendingDatagrams()) { // Проверка наличия входящих датаграмм.
        QByteArray datagram; // Создание массива байтов для хранения датаграммы.
        datagram.resize(pendingDatagramSize()); // Изменение размера массива байтов на размер входящей датаграммы.
        readDatagram(datagram.data(), datagram.size()); // Чтение датаграммы в массив байтов.
        emit recieved(QString::fromUtf8(datagram)); // Отправка сигнала с прочитанным сообщением.
    }
}
