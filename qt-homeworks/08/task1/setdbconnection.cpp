#include "setdbconnection.h"
#include "ui_setdbconnection.h"

#include "database.h"

SetDBConnection::SetDBConnection (QWidget *parent)
    : QDialog (parent), ui (new Ui::SetDBConnection)
{
    ui->setupUi(this);

    //Ресайзим вектор значений, по количеству полей необходимых для
    //подключения к БД
    data.resize(NUM_DATA_FOR_CONNECT_TO_DB);

    ui->line_host->setText("981757-ca08998.tmweb.ru");
    ui->line_base->setText("netology_cpp");
    ui->line_login->setText("netology_usr_cpp");
    ui->line_passw->setText("CppNeto3");
    ui->spin_port->setValue(5432);

}
SetDBConnection::~SetDBConnection () { delete ui; }

void SetDBConnection::on_buttonBox_accepted()
{

    //Добавляем данные в контейнер и передаем в главное окно
    data[hostName] = ui->line_host->text();
    data[dbName] = ui->line_base->text();
    data[login] = ui->line_login->text();
    data[pass] = ui->line_passw->text();
    data[port] = ui->spin_port->text();

    emit sig_sendData(data);

}


