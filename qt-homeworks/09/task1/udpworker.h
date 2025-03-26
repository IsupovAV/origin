#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>


class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket(QHostAddress host, int port, int l_port);
    void SendDatagram(const QByteArray& data );


private slots:
    void readPendingDatagrams(void);

private:
    QUdpSocket* serviceUdpSocket_;
    QHostAddress host_;
    int port_;
    int listen_port_;


signals:
    void sig_received(QNetworkDatagram datagram);

};

#endif // UDPWORKER_H
