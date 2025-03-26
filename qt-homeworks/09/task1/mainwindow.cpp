#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);

    worker_timer_ = new UDPworker(this);
    worker_timer_->InitSocket(QHostAddress::LocalHost, port_timer,
                              listen_port_timer);

    worker_message_ = new UDPworker(this);
    worker_message_->InitSocket(QHostAddress::LocalHost, port_message,
                                listen_port_message);

    connect(worker_timer_, &UDPworker::sig_received, this,
            &MainWindow::DisplayTime);
    connect(worker_message_, &UDPworker::sig_received, this,
            &MainWindow::DisplayMessage);
    connect(ui_->pb_sendDatagram, &QPushButton::clicked, this,
            &MainWindow::SendMessage);

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, [&] {
        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << dateTime;

        worker_timer_->SendDatagram(dataToSend);
        timer_->start(TIMER_DELAY);
    });
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::DisplayTime(QNetworkDatagram datagram) {
    clear_if_fill();
    QByteArray data;
    data = datagram.data();
    QDataStream inStr(&data, QIODevice::ReadOnly);
    QDateTime date_time;
    inStr >> date_time;
    ui_->te_result->append(QString("Текущее время: %1. Принято пакетов %2")
                               .arg(date_time.toString(),QString::number(counterPck)));
}

void MainWindow::DisplayMessage(QNetworkDatagram datagram) {
    clear_if_fill();
    auto str = QString("Принято сообщение от %1:%2, размер сообщения(байт) %3")
                   .arg(datagram.senderAddress().toString())
                   .arg(datagram.senderPort())
                   .arg(datagram.data().size());

    ui_->te_result->append(str);
}

void MainWindow::SendMessage() {
    QByteArray dataToSend;
    QDataStream outStr(&dataToSend, QIODevice::WriteOnly);
    outStr << ui_->te_sendText->toPlainText();
    worker_message_->SendDatagram(dataToSend);
}

void MainWindow::clear_if_fill() {
    if (++counterPck % 20 == 0) {
        ui_->te_result->clear();
    }
}

void MainWindow::on_pb_start_clicked() { timer_->start(TIMER_DELAY); }

void MainWindow::on_pb_stop_clicked() { timer_->stop(); }
