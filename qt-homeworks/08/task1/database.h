#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDataBase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>
#include <QTableWidget>

#define POSTGRE_DRIVER "QPSQL"
#define DB_NAME "MyDB"

// Количество полей данных необходимых для подключения к БД
#define NUM_DATA_FOR_CONNECT_TO_DB 5

// Перечисление полей данных
enum fieldsForConnect {
    hostName = 0,
    dbName = 1,
    login = 2,
    pass = 3,
    port = 4
};

// Типы запросов
enum requestType {

    requestAllFilms = 0,
    requestComedy = 1,
    requestHorrors = 2

};

class DataBase : public QObject {
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void AddDataBase(QString driver, QString nameDB = "");
    void DisconnectFromDataBase(QString nameDb = "");
    void RequestToDB(int type_request, QString request);
    QSqlError GetLastError(void);
    void ConnectToDataBase(QVector<QString> dataForConnect);

signals:
    void sig_SendDataFromDB(QSqlQueryModel *queryModel,QSqlTableModel *tableModel, int type_request);
    void sig_SendStatusConnection(bool);

private:
    QSqlDatabase *dataBase;
    QSqlQueryModel* queryModel;
    QSqlTableModel* tableModel;
};

#endif // DATABASE_H
