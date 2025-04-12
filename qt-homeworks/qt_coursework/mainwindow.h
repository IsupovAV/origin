#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QResizeEvent>
#include <QScreen>
#include <QTimer>

#include "about.h"
#include "database.h"
#include "setdbconnection.h"
#include "statistics.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sig_sendAirportName(QString airportName);

private slots:
    void readySettings(QVector<QString> dbSettings);
    void setStatusConnection(bool status);
    void processingTimeout();
    void processingDataAirports(const QComboBox *airportsCombo);
    void setDataFlights(const QTableView *tableView);
    void checkStatusCongestion(QSqlError err);

    void on_connectMessage();
    void on_stopConnection();
    void on_pb_get_schedule_clicked();
    void on_pb_clear_schedule_clicked();
    void on_pb_statistics_clicked();

    void on_mnu_connect_triggered();
    void on_mnu_disconnect_triggered();
    void on_mnu_settings_triggered();
    void on_mnu_get_schedule_triggered();
    void on_mnu_clear_schedule_triggered();
    void on_mnu_statistics_triggered();
    void on_mnu_about_triggered();

private:
    Ui::MainWindow *ui;
    QMessageBox *connectMessage;
    QTimer *pTimer;
    QVector<QString> dataForConnect;
    Database *database_obj;
    SetDBConnection *dataConnection;
    Statistics *pStatisticsWindow;

    QLabel lb_statusText;
    QPushButton *stopAttempts;
    About *pAbout;

    int attemptsCounter = 0;
    int secondsCounter = 0;

    void setEnabledWidgets(bool);
    void getSchedule();
    void clearSchedule();
    void getStatics();
};

#endif // MAINWINDOW_H
