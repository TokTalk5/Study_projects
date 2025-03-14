#include "communicator.h"

TCommunicator::TCommunicator(TCommonParam& pars, QObject *parent)
    : QUdpSocket(parent)
{
    param = pars;
    socket = new QUdpSocket(this); // Создание нового сокета и привязка его к текущему объекту.
        socket->bind(QHostAddress::LocalHost, param.receivePort); // Привязка сокета к порту для приема сообщений.
        if (ready) connect(socket, &QUdpSocket::readyRead, this, &TCommunicator::processPendingDatagrams); // Соединение сигнала readyRead сокета с слотом processPendingDatagrams.
   }

TCommunicator::~TCommunicator()
{
    delete socket;
}
bool TCommunicator::isReady()
{
    return ready;
}

void TCommunicator::send(const QString& message)// Метод для отправки сообщения.
{
   if (ready) socket->writeDatagram(message.toUtf8(), param.address, param.sendPort); // Отправка сообщения на указанный адрес и порт.
}

void TCommunicator::processPendingDatagrams()// Проверка наличия входящих датаграмм.
{

    while (socket->hasPendingDatagrams()) { // Проверка наличия входящих датаграмм.
            QByteArray datagram; // Создание массива байтов для хранения датаграммы.
            datagram.resize(socket->pendingDatagramSize()); // Изменение размера массива байтов на размер входящей датаграммы.
            socket->readDatagram(datagram.data(), datagram.size()); // Чтение датаграммы в массив байтов.
            emit recieved(QString::fromUtf8(datagram)); // Отправка сигнала с прочитанным сообщением.
        }
}
