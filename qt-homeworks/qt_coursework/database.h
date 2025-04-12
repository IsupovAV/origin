#ifndef DATABASE_H
#define DATABASE_H

#include <QComboBox>
#include <QDebug>
#include <QMap>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QtConcurrent>

#include "utility.h"

class Database : public QObject {
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    void AddDatabaseDriver(QString driver);
    void AddConnectionData(QVector<QString> dataForConnect);
    void ConnectDatabase();
    void DisconnectDatabase();
    void RequestListAirports();
    void RequestListFlights(QString airportCode, QString requestDate,
                            TypeDirection type);
    void RequestCongestion(QString airportCode);
    QSqlError GetLastError(void);
    bool IsChange(QVector<QString> dataForConnect);
    bool IsOpen();

signals:
    void sig_sendDataAirports(const QComboBox *airportsCombo);
    void sig_sendDataFlights(const QTableView *tableView);
    void sig_sendStatusConnection(bool);
    void sig_sendCongestionMonthsForYear(QVector<QString> x, QVector<double> y);
    void sig_sendCongestionDaysForMonth(QVector<QString> x, QVector<double> y);
    void sig_sendStatusRequestCongestion(QSqlError err);

private:
    QSqlDatabase *database;

    QSqlQueryModel *queryAirports;
    QFuture<void> ftrQueryAirports;
    QFutureWatcher<void> ftrWatcherQueryAirports;

    QSqlQueryModel *queryTable;
    QFuture<void> ftrQueryTable;
    QFutureWatcher<void> ftrWatcherQueryTable;

    QSqlQuery *sqlQuery;
    QFuture<void> ftrQueryYear;
    QFutureWatcher<void> ftrWatcherQueryYear;
    QFuture<void> ftrQueryDayForMonth;
    QFutureWatcher<void> ftrWatcherQueryDayForMonth;

    QTableView *tableView;
    QComboBox *airportsCombo;
    QString airportCode_;

    const QMap<int, QString> months{
                                    {1, "Январь"},   {2, "Февраль"},  {3, "Март"},    {4, "Апрель"},
        {5, "Май"},      {6, "Июнь"},     {7, "Июль"},    {8, "Август"},
        {9, "Сентябрь"}, {10, "Октябрь"}, {11, "Ноябрь"}, {12, "Декабрь"}};
};

#endif // DATABASE_H
