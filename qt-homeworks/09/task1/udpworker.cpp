#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent) {}

/*!
 * @brief Метод инициализирует UDP сервер
 */
void UDPworker::InitSocket(QHostAddress host, int port, int l_port) {
    host_ = host;
    port_ = port;

    serviceUdpSocket_ = new QUdpSocket(this);
    /*
   * Соединяем присваиваем адрес и порт серверу и соединяем функцию
   * обраотчик принятых пакетов с сокетом
   */
    serviceUdpSocket_->bind(QHostAddress::LocalHost, l_port);

    connect(serviceUdpSocket_, &QUdpSocket::readyRead, this,
            &UDPworker::readPendingDatagrams);
}

/*!
 * @brief Метод осуществляет опередачу датаграммы
 */
void UDPworker::SendDatagram(const QByteArray &data) {
    /*
   *  Отправляем данные на host_:port_
   */
    serviceUdpSocket_->writeDatagram(data, host_, port_);
}

/*!
 * @brief Метод осуществляет чтение датаграм из сокета
 */
void UDPworker::readPendingDatagrams(void) {
    /*
   *  Производим чтение принятых датаграмм
   */
    while (serviceUdpSocket_->hasPendingDatagrams()) {
        QNetworkDatagram datagram = serviceUdpSocket_->receiveDatagram();
        emit sig_received(datagram);
    }
}
