#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->rb_arrival->setChecked(true);

    stopAttempts = new QPushButton("Прервать", this);
    lb_statusText.setMinimumSize(250, 22);
    ui->statusbar->addWidget(&lb_statusText);
    ui->statusbar->addWidget(stopAttempts);

    connectMessage = new QMessageBox(this);

    pAbout = new About(this);

    pTimer = new QTimer(this);
    pTimer->setTimerType(Qt::TimerType::PreciseTimer);
    pTimer->setInterval(1000);

    dataForConnect.resize(SIZE_LIST_FOR_CONNECT);

    database_obj = new Database(this);
    database_obj->AddDatabaseDriver(POSTGRE_DRIVER);

    dataConnection = new SetDBConnection(this);
    pStatisticsWindow = new Statistics(this);

    QObject::connect(dataConnection, &SetDBConnection::sig_sendDataConnection,
                     this, &MainWindow::readySettings);
    QObject::connect(database_obj, &Database::sig_sendStatusConnection, this,
                     &MainWindow::setStatusConnection);
    QObject::connect(connectMessage, &QMessageBox::buttonClicked, this,
                     &MainWindow::on_connectMessage);
    QObject::connect(pTimer, &QTimer::timeout, this,
                     &MainWindow::processingTimeout);
    QObject::connect(stopAttempts, &QPushButton::clicked, this,
                     &MainWindow::on_stopConnection);

    QObject::connect(ui->cmb_aerolist, &QComboBox::currentTextChanged, this, [&] {
        ui->pb_get_schedule->setEnabled(true);
        ui->mnu_get_schedule->setEnabled(true);
    });
    QObject::connect(ui->rb_arrival, &QRadioButton::toggled, this, [&] {
        ui->pb_get_schedule->setEnabled(true);
        ui->mnu_get_schedule->setEnabled(true);
    });
    QObject::connect(ui->rb_departure, &QRadioButton::toggled, this, [&] {
        ui->pb_get_schedule->setEnabled(true);
        ui->mnu_get_schedule->setEnabled(true);
    });
    QObject::connect(ui->dte_date, &QDateEdit::dateChanged, this, [&] {
        ui->pb_get_schedule->setEnabled(true);
        ui->mnu_get_schedule->setEnabled(true);
    });

    QObject::connect(database_obj, &Database::sig_sendDataAirports, this,
                     &MainWindow::processingDataAirports);
    QObject::connect(database_obj, &Database::sig_sendDataFlights, this,
                     &MainWindow::setDataFlights);

    QObject::connect(this, &MainWindow::sig_sendAirportName, pStatisticsWindow,
                     &Statistics::setAirportName);
    QObject::connect(database_obj, &Database::sig_sendCongestionMonthsForYear,
                     pStatisticsWindow,
                     &Statistics::requestCongestionYearByMonths);
    QObject::connect(database_obj, &Database::sig_sendCongestionDaysForMonth,
                     pStatisticsWindow,
                     &Statistics::requestCongestionMonthByDays);
    QObject::connect(database_obj, &Database::sig_sendStatusRequestCongestion,
                     this, &MainWindow::checkStatusCongestion);

    dataConnection->readSettingsConnection(dataForConnect);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setStatusConnection(bool status) {
    if (status) {
        lb_statusText.setText("Подключено");
        lb_statusText.setStyleSheet("color : green");
        ui->mnu_settings->setEnabled(true);
        stopAttempts->setVisible(false);
        on_pb_clear_schedule_clicked();
        ui->mnu_connect->setEnabled(false);
        ui->mnu_disconnect->setEnabled(true);
        ui->pb_get_schedule->setEnabled(true);

        ui->mnu_commands->setEnabled(true);
        secondsCounter = 0;
        attemptsCounter = 0;
        database_obj->RequestListAirports();
    } else {
        lb_statusText.setStyleSheet("color : red");
        stopAttempts->setVisible(false);
        setEnabledWidgets(false);
        ui->mnu_connect->setEnabled(true);
        ui->mnu_disconnect->setEnabled(false);
        ui->mnu_commands->setEnabled(false);
        lb_statusText.setText("Отключено");
        QString lastError = database_obj->GetLastError().text();
        if (lastError != "" && !database_obj->IsOpen()) {
            connectMessage->setIcon(QMessageBox::Critical);
            connectMessage->setText(lastError);
            connectMessage->exec();
        }
    }
}

void MainWindow::on_stopConnection() {
    pTimer->stop();
    secondsCounter = 0;
    attemptsCounter = 0;
    ui->mnu_settings->setEnabled(true);
    stopAttempts->setVisible(false);
    lb_statusText.setText("Отключено");
}

void MainWindow::setEnabledWidgets(bool enabled) {
    ui->grb_schedule->setEnabled(enabled);
    ui->grb_aero_direction->setEnabled(enabled);
    ui->grb_actions->setEnabled(enabled);
}

void MainWindow::on_connectMessage() {
    pTimer->start();
    ui->mnu_settings->setEnabled(false);
    stopAttempts->setVisible(true);
    auto limitAttempts = dataForConnect[num_attempts].toInt();
    if (limitAttempts == attemptsCounter + 1) {
        ui->mnu_settings->setEnabled(true);
        stopAttempts->setVisible(false);
        lb_statusText.setText("Отключено");
    } else {
        lb_statusText.setText(
            "Отключено\tПереподключение через: " + dataForConnect[timeout] + "\t");
    }
}

void MainWindow::processingTimeout() {
    ++secondsCounter;
    auto limitAttempts = dataForConnect[num_attempts].toInt();
    auto limitSeconds = dataForConnect[timeout].toInt();
    if (limitAttempts != attemptsCounter + 1) {
        lb_statusText.setText("Отключено\tПереподключение через: " +
                              QString::number(limitSeconds - secondsCounter) +
                              "\t");
    }

    if (limitAttempts == 0 && limitSeconds == secondsCounter) {
        secondsCounter = 0;
        attemptsCounter = 0;
        pTimer->stop();
        database_obj->ConnectDatabase();
    } else if (limitAttempts != 0 && limitSeconds == secondsCounter) {
        secondsCounter = 0;
        attemptsCounter += 1;
        pTimer->stop();

        if (limitAttempts == attemptsCounter) {
            secondsCounter = 0;
            attemptsCounter = 0;
        } else {
            database_obj->ConnectDatabase();
        }
    }
}

void MainWindow::processingDataAirports(const QComboBox *airportsCombo) {
    ui->cmb_aerolist->setModel(airportsCombo->model());
    ui->cmb_aerolist->setCurrentIndex(0);
    setEnabledWidgets(true);
}

void MainWindow::setDataFlights(const QTableView *tableView) {
    ui->tbv_shedule->setModel(tableView->model());

    ui->tbv_shedule->resizeColumnToContents(0);
    ui->tbv_shedule->resizeColumnToContents(1);
    ui->tbv_shedule->resizeColumnToContents(2);

    ui->pb_clear_schedule->setEnabled(true);
}

void MainWindow::checkStatusCongestion(QSqlError err) {
    if (err.type() != QSqlError::NoError) {
        database_obj->DisconnectDatabase();
        connectMessage->setIcon(QMessageBox::Critical);
        connectMessage->setText(err.text());
        connectMessage->exec();
    }
}

void MainWindow::on_pb_get_schedule_clicked() { getSchedule(); }

void MainWindow::on_mnu_connect_triggered() {
    pTimer->stop();
    secondsCounter = 0;
    attemptsCounter = 0;
    database_obj->ConnectDatabase();
}

void MainWindow::on_mnu_disconnect_triggered() { setStatusConnection(false); }

void MainWindow::on_pb_clear_schedule_clicked() { clearSchedule(); }

void MainWindow::on_pb_statistics_clicked() { getStatics(); }

void MainWindow::on_mnu_settings_triggered() { dataConnection->exec(); }

void MainWindow::readySettings(QVector<QString> dbSettings) {
    dataForConnect = std::move(dbSettings);
    database_obj->AddConnectionData(dataForConnect);

    if (dataForConnect[auto_connect] == "true") {
        database_obj->ConnectDatabase();
    } else {
        setStatusConnection(false);
    }
}

void MainWindow::on_mnu_about_triggered() { pAbout->exec(); }

void MainWindow::on_mnu_get_schedule_triggered() { getSchedule(); }

void MainWindow::on_mnu_clear_schedule_triggered() { clearSchedule(); }

void MainWindow::on_mnu_statistics_triggered() { getStatics(); }

void MainWindow::getSchedule() {
    QString requestDate = ui->dte_date->text().mid(6) + '-' +
                          ui->dte_date->text().mid(3, 2) + '-' +
                          ui->dte_date->text().mid(0, 2);

    auto code = ui->cmb_aerolist->model()
                    ->data(ui->cmb_aerolist->model()->index(
                        ui->cmb_aerolist->currentIndex(), 1))
                    .toString();

    if (ui->rb_arrival->isChecked()) {
        database_obj->RequestListFlights(code, requestDate, arrival);
    }
    if (ui->rb_departure->isChecked()) {
        database_obj->RequestListFlights(code, requestDate, departure);
    }
    ui->pb_get_schedule->setEnabled(false);
    ui->mnu_get_schedule->setEnabled(false);
    ui->mnu_clear_schedule->setEnabled(true);
}

void MainWindow::clearSchedule() {
    ui->tbv_shedule->setModel(nullptr);

    ui->pb_clear_schedule->setEnabled(false);
    ui->pb_get_schedule->setEnabled(true);

    ui->mnu_clear_schedule->setEnabled(false);
    ui->mnu_get_schedule->setEnabled(true);
}

void MainWindow::getStatics() {
    emit sig_sendAirportName(
        "Аэропорт: " +
        ui->cmb_aerolist->itemText(ui->cmb_aerolist->currentIndex()));
    database_obj->RequestCongestion(ui->cmb_aerolist->model()
                                        ->data(ui->cmb_aerolist->model()->index(
                                            ui->cmb_aerolist->currentIndex(), 1))
                                        .toString());
    pStatisticsWindow->exec();
}
