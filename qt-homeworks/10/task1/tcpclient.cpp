#include "tcpclient.h"

/* ServiceHeader
 * Для работы с потоками наши данные необходимо сериализовать.
 * Поскольку типы данных не стандартные перегрузим оператор <<
 * Для работы с ServiceHeader
 */
QDataStream &operator>>(QDataStream &out, ServiceHeader &data) {
    out >> data.id;
    out >> data.idData;
    out >> data.status;
    out >> data.len;
    return out;
};

QDataStream &operator<<(QDataStream &in, ServiceHeader &data) {
    in << data.id;
    in << data.idData;
    in << data.status;
    in << data.len;
    return in;
};

QDataStream &operator>>(QDataStream &out, StatServer &data) {

    out >> data.incBytes;  // Количество принятых байт
    out >> data.sendBytes; // Количество переданных байт
    out >> data.revPck;    // Количество принятых пакетов
    out >> data.sendPck;   // Количество переданных пакетов
    out >> data.workTime;  // Время работы сервера, сек
    out >> data.clients;   // Количество подключённых клиентов
    return out;
};

QDataStream &operator<<(QDataStream &in, StatServer &data) {
    in << data.incBytes;  // Количество принятых байт
    in << data.sendBytes; // Количество переданных байт
    in << data.revPck;    // Количество принятых пакетов
    in << data.sendPck;   // Количество переданных пакетов
    in << data.workTime;  // Время работы сервера, сек
    in << data.clients;   // Количество подключённых клиентов
    return in;
};

void TCPclient::init_processing_map_()
{
    processing_map_[Messages::GET_SIZE] = [&](ServiceHeader h, QDataStream &stream){
        uint32_t sz;
        stream >> sz;
        emit sig_sendFreeSize(sz);
    };

    processing_map_[Messages::GET_TIME] = [&](ServiceHeader h, QDataStream &stream){
        QDateTime date_time;
        stream >> date_time;
        emit sig_sendTime(date_time);
    };

    processing_map_[Messages::GET_STAT] = [&](ServiceHeader h, QDataStream &stream){
        StatServer statistics;
        stream >> statistics;
        emit sig_sendStat(statistics);
    };

    processing_map_[Messages::SET_DATA] = [&](ServiceHeader h, QDataStream &stream){
        QString str;
        stream >> str;
        emit sig_SendReplyForSetData(str);
    };

    processing_map_[Messages::CLEAR_DATA] = [&](ServiceHeader h, QDataStream &stream){
        emit sig_Success(h.idData);
    };
}

/*
 * Поскольку мы являемся клиентом, инициализацию сокета
 * проведем в конструкторе. Также необходимо соединить
 * сокет со всеми необходимыми нам сигналами.
 */
TCPclient::TCPclient(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &TCPclient::ReadyRead);
    connect(socket, &QTcpSocket::connected, this,
            [this] { emit sig_connectStatus(STATUS_SUCCES); });
    connect(socket, &QTcpSocket::errorOccurred, this,
            [this] { emit sig_connectStatus(ERR_CONNECT_TO_HOST); });
    connect(socket, &QTcpSocket::disconnected, this,
            [this] { emit sig_Disconnected(); });
    init_processing_map_();
}

/* write
 * Метод отправляет запрос на сервер. Сериализировать будем
 * при помощи QDataStream
 */
void TCPclient::SendRequest(ServiceHeader head) {
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << head;
    socket->write(data);
}

/* write
 * Такой же метод только передаем еще данные.
 */
void TCPclient::SendData(ServiceHeader head, QString str) {
    QByteArray head_data, data;
    QDataStream out_head(&head_data, QIODevice::WriteOnly);
    QDataStream out_data(&data, QIODevice::WriteOnly);
    out_data << str;
    head.len = data.size();
    out_head << head;
    socket->write(head_data);
    socket->write(data);
}

/*
 * \brief Метод подключения к серверу
 */
void TCPclient::ConnectToHost(QHostAddress host, uint16_t port) {
    socket->connectToHost(host, port);
}

/*
 * \brief Метод отключения от сервера
 */
void TCPclient::DisconnectFromHost() { socket->disconnectFromHost(); }

void TCPclient::ReadyRead() {

    QDataStream incStream(socket);

    if (incStream.status() != QDataStream::Ok) {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Ошибка открытия входящего потока для чтения данных!");
        msg.exec();
    }

    // Читаем до конца потока
    while (!incStream.atEnd()) {
        // Если мы обработали предыдущий пакет, мы скинули значение idData в 0
        if (servHeader.idData == 0) {

            // Проверяем количество полученных байт. Если доступных байт меньше чем
            // заголовок, то выходим из обработчика и ждем новую посылку. Каждая новая
            // посылка дописывает данные в конец буфера
            if (socket->bytesAvailable() < sizeof(ServiceHeader)) {
                return;
            } else {
                // Читаем заголовок
                incStream >> servHeader;
                // Проверяем на корректность данных. Принимаем решение по заранее
                // известному ID пакета. Если он "битый" отбрасываем все данные в
                // поисках нового ID.
                if (servHeader.id != ID) {
                    uint16_t hdr = 0;
                    while (incStream.atEnd()) {
                        incStream >> hdr;
                        if (hdr == ID) {
                            incStream >> servHeader.idData;
                            incStream >> servHeader.status;
                            incStream >> servHeader.len;
                            break;
                        }
                    }
                }
            }
        }
        // Если получены не все данные, то выходим из обработчика.
        // Ждем новую посылку
        if (socket->bytesAvailable() < servHeader.len) {
            return;
        } else {
            // Обработка данных
            ProcessingData(servHeader, incStream);
            servHeader.idData = 0;
            servHeader.status = 0;
            servHeader.len = 0;
        }
    }
}

/*
 * Остался метод обработки полученных данных. Согласно протоколу
 * мы должны прочитать данные из сообщения и вывести их в ПИ.
 * Поскольку все типы сообщений нам известны реализуем выбор через
 * switch. Реализуем получение времени.
 */
void TCPclient::ProcessingData(ServiceHeader header, QDataStream &stream) {
    if (header.status != STATUS_SUCCES) {
        emit sig_Error(header.status);
        return;
    }

    (processing_map_[header.idData])(header, stream);
}
