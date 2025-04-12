#include "database.h"

Database::Database(QObject *parent) : QObject{parent} {
    database = new QSqlDatabase();
    queryTable = new QSqlQueryModel(this);
    queryAirports = new QSqlQueryModel(this);
    tableView = new QTableView(nullptr);
    airportsCombo = new QComboBox(nullptr);
    sqlQuery = new QSqlQuery;

    connect(&ftrWatcherQueryAirports, &QFutureWatcher<void>::finished, this, [&] {
        airportsCombo->setModel(queryAirports);
        emit sig_sendDataAirports(airportsCombo);
    });

    connect(&ftrWatcherQueryTable, &QFutureWatcher<void>::finished, this, [&] {
        tableView->setModel(queryTable);
        tableView->hideColumn(0);
        emit sig_sendDataFlights(tableView);
    });

    connect(&ftrWatcherQueryYear, &QFutureWatcher<void>::finished, this, [&] {
        QVector<QString> x;
        QVector<double> y;
        while (sqlQuery->next()) {
            QString value_y = sqlQuery->value(0).toString();
            QString value_x = sqlQuery->value(1).toString();
            x.push_back(value_x.mid(5, 2) + '.' + value_x.mid(0, 4));
            y.push_back(value_y.toDouble());
        }

        emit sig_sendCongestionMonthsForYear(x, y);

        ftrQueryDayForMonth = QtConcurrent::run([=, this] {
            *sqlQuery = QSqlQuery(*database);
            QString query_string =
                QString("SELECT count(flight_no), date_trunc(\'day\', "
                                           "scheduled_departure) as Day "
                                           "FROM bookings.flights f "
                                           "WHERE scheduled_departure::date > %1 "
                                           "and scheduled_departure::date <= %2 "
                                           "and (departure_airport = %3 or arrival_airport = %3) "
                                           "GROUP BY Day;")
                                       .arg("'2016-08-31'", "'2017-08-31'", "\'" + airportCode_ + "\'");
            // qDebug() << query_string;
            QSqlError err;
            if (!sqlQuery->exec(query_string)) {
                err = sqlQuery->lastError();
                emit sig_sendStatusRequestCongestion(err);
            }
        });

        ftrWatcherQueryDayForMonth.setFuture(ftrQueryDayForMonth);
    });

    connect(&ftrWatcherQueryDayForMonth, &QFutureWatcher<void>::finished, this,
            [&] {
                QVector<QString> x;
        QVector<double> y;
                while (sqlQuery->next()) {
            auto value = sqlQuery->value(0).toInt();
                    QString key = sqlQuery->value(1).toString();

            QString keyYear = key.mid(0, 4);
                    QString keyMonth = key.mid(5, 2);
            int keyMonthInt = keyMonth.toInt();
                    key = months[keyMonthInt] + ' ' + keyYear;
            x.push_back(key);
                    y.push_back(value);
                }

                emit sig_sendCongestionDaysForMonth(x, y);
    });
}

Database::~Database() {
    delete tableView;
    delete airportsCombo;
    delete sqlQuery;
    delete queryTable;
    delete queryAirports;
    delete database;
}

void Database::AddDatabaseDriver(QString driver) {
    *database = QSqlDatabase::addDatabase(driver);
}

void Database::AddConnectionData(QVector<QString> dataForConnect) {
    database->setHostName(dataForConnect[host_name]);
    database->setDatabaseName(dataForConnect[db_name]);
    database->setPort(dataForConnect[port].toInt());
    database->setUserName(dataForConnect[login]);
    database->setPassword(dataForConnect[pass]);
}

void Database::ConnectDatabase() {
    emit sig_sendStatusConnection(database->open());
}

void Database::DisconnectDatabase() { database->close(); }

void Database::RequestListAirports() {
    ftrQueryAirports = QtConcurrent::run([=, this] {
        queryAirports->setQuery(
            "SELECT airport_name->>\'ru\' as Airport, airport_code "
            "FROM bookings.airports_data "
            "ORDER BY Airport",
            *database);
    });

    ftrWatcherQueryAirports.setFuture(ftrQueryAirports);
}

void Database::RequestListFlights(QString airportCode, QString requestDate,
                                  TypeDirection type) {
    ftrQueryTable = QtConcurrent::run([=, this] {
        // qDebug() << airportCode << ' ' << requestDate << ' ' << type;
        if (type == arrival) {
            QString query_string =
                QString("SELECT flight_no, scheduled_arrival, "
                                           "ad.airport_name->>'ru' as Name "
                                           "FROM bookings.flights f "
                                           "JOIN bookings.airports_data ad on ad.airport_code = "
                                           "f.departure_airport "
                                           "WHERE f.arrival_airport  = %1 AND scheduled_departure::date "
                                           "= %2;")
                                       .arg("\'" + airportCode + "\'", "\'" + requestDate + "\'");

            // qDebug() << "query_sting = " << query_sting;
            queryTable->setQuery(query_string, *database);
            queryTable->setHeaderData(2, Qt::Horizontal, "Аэропорт отправления");
        }
        if (type == departure) {
            QString query_string =
                QString("SELECT flight_no, scheduled_arrival, "
                                           "ad.airport_name->>'ru' as Name "
                                           "FROM bookings.flights f "
                                           "JOIN bookings.airports_data ad on ad.airport_code = "
                                           "f.arrival_airport "
                                           "WHERE f.departure_airport = %1 AND "
                                           "scheduled_departure::date = %2;")
                                       .arg("\'" + airportCode + "\'", "\'" + requestDate + "\'");
            // qDebug() << "query_sting = " << query_sting;
            queryTable->setQuery(query_string, *database);
            queryTable->setHeaderData(2, Qt::Horizontal, "Аэропорт назначения");
        }

        queryTable->setHeaderData(0, Qt::Horizontal, "Номер рейса");
        queryTable->setHeaderData(1, Qt::Horizontal, "Время вылета");
    });

    ftrWatcherQueryTable.setFuture(ftrQueryTable);
}

void Database::RequestCongestion(QString airportCode) {
    airportCode_ = airportCode;
    ftrQueryYear = QtConcurrent::run([=, this] {
        *sqlQuery = QSqlQuery(*database);

        QSqlError err;
        QString query_string =
            QString("SELECT count(flight_no), "
                "date_trunc(\'month\', scheduled_departure) as Month "
                "FROM bookings.flights f WHERE scheduled_departure::date > %1 "
                "and scheduled_departure::date <= %2 "
                "and (departure_airport = %3 "
                "or arrival_airport = %3) "
                "GROUP BY Month;")
                                   .arg("'2016-08-31'", "'2017-08-31'", "\'" + airportCode_ + "\'");
        // qDebug() << query_string;
        if (!sqlQuery->exec(query_string)) {
            err = sqlQuery->lastError();
            emit sig_sendStatusRequestCongestion(err);
        }
    });

    ftrWatcherQueryYear.setFuture(ftrQueryYear);
}

QSqlError Database::GetLastError() { return database->lastError(); }

bool Database::IsChange(QVector<QString> dataForConnect) {
    if (database->hostName() != dataForConnect[host_name] ||
        database->databaseName() != dataForConnect[db_name] ||
        database->port() != dataForConnect[port].toInt() ||
        database->userName() != dataForConnect[login] ||
        database->password() != dataForConnect[pass]) {
        return true;
    }
    return false;
}

bool Database::IsOpen() { return database->isOpen(); }
