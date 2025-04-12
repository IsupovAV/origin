#include "setdbconnection.h"
#include "ui_setdbconnection.h"

#include "utility.h"

SetDBConnection::SetDBConnection(QWidget *parent)
    : QDialog(parent), ui(new Ui::SetDBConnection) {
    ui->setupUi(this);

    data.resize(SIZE_LIST_FOR_CONNECT);
    data[host_name] = HOSTNAME;
    data[db_name] = DBNAME;
    data[port] = PORT;
    data[login] = LOGIN;
    data[pass] = PASS;
    data[auto_connect] = AUTOCONNECT;
    data[num_attempts] = NUM_OF_CONN_ATTEMPTS;
    data[timeout] = TIMEOUT;

    ui->line_host->setText(data[host_name]);
    ui->line_base->setText(data[db_name]);
    ui->line_login->setText(data[login]);
    ui->line_passw->setText(data[pass]);
    ui->spin_port->setValue(QString(data[port]).toInt());
}

SetDBConnection::~SetDBConnection() { delete ui; }

void SetDBConnection::on_buttonBox_accepted() {
    data[host_name] = ui->line_host->text();
    data[db_name] = ui->line_base->text();
    data[login] = ui->line_login->text();
    data[pass] = ui->line_passw->text();
    data[port] = ui->spin_port->text();

    emit sig_sendDataConnection(data);
}

void SetDBConnection::readSettingsConnection(QVector<QString> dbSetting) {
    dbSetting[host_name] = data[host_name];
    dbSetting[db_name] = data[db_name];
    dbSetting[port] = data[port];
    dbSetting[login] = data[login];
    dbSetting[pass] = data[pass];
    dbSetting[auto_connect] = data[auto_connect];
    dbSetting[num_attempts] = data[num_attempts];
    dbSetting[timeout] = data[timeout];

    emit sig_sendDataConnection(data);
}
