#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "UdpWorker.h"

#define TIMER_DELAY 1000

const uint32_t port_timer = 33333;
const uint32_t listen_port_timer = 33333;
const uint32_t port_message = 44444;
const uint32_t listen_port_message = 44444;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void DisplayTime(QNetworkDatagram datagram);
    void DisplayMessage(QNetworkDatagram datagram);
    void SendMessage();
    void on_pb_start_clicked();
    void on_pb_stop_clicked();

private:
    void clear_if_fill();
    Ui::MainWindow *ui_;
    QTimer* timer_;
    UDPworker* worker_timer_;
    UDPworker* worker_message_;
    uint32_t counterPck = 0;
};
#endif // MAINWINDOW_H
