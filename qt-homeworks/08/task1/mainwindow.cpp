#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    // Исходное состояние виджетов
    ui->setupUi(this);
    ui->lb_statusConnect->setStyleSheet("color:red");
    ui->pb_request->setEnabled(false);

    /*
   * Выделим память под необходимые объекты. Все они наследники
   * QObject, поэтому воспользуемся иерархией.
   */
    dataDb = new SetDBConnection(this);
    dataBase = new DataBase(this);
    msg = new QMessageBox(this);

    // Установим размер вектора данных для подключения к БД
    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);

    /*
   * Добавим БД используя стандартный драйвер PSQL и зададим имя.
   */
    dataBase->AddDataBase(POSTGRE_DRIVER, DB_NAME);

    /*
   * Устанавливаем данные для подключениея к БД.
   * Поскольку метод небольшой используем лямбда-функцию.
   */
    connect(dataDb, &SetDBConnection::sig_sendData, this,
            [&](QVector<QString> receivData) { dataForConnect = receivData; });

    /*
   * Соединяем сигнал, который передает ответ от БД с методом, который
   * отображает ответ в ПИ
   */
    connect(dataBase, &DataBase::sig_SendDataFromDB, this,
            &MainWindow::ScreenDataFromDB);

    /*
   *  Сигнал для подключения к БД
   */
    connect(dataBase, &DataBase::sig_SendStatusConnection, this,
            &MainWindow::ReceiveStatusConnectionToDB);

    // Интересно, что таблички film, film_category и category сильно похожи на таблички
    // отсюда: https://neon.tech/postgresql/postgresql-getting-started/postgresql-sample-database
    // поэтому проверял и у себя на домашнем компе.
    // Подключение использовал такое:
    // dataForConnect[hostName] = "localhost";
    // dataForConnect[dbName] = "dvdrental";
    // dataForConnect[login] = "postgres";
    // dataForConnect[pass] = "**********";
    // dataForConnect[port] = "5432";

    // захардкодил для проверки
    dataForConnect[hostName] = "981757-ca08998.tmweb.ru";
    dataForConnect[dbName] = "netology_cpp";
    dataForConnect[login] = "netology_usr_cpp";
    dataForConnect[pass] = "CppNeto3";
    dataForConnect[port] = "5432";
}

MainWindow::~MainWindow() { delete ui; }

/*!
 * @brief Слот отображает форму для ввода данных подключения к БД
 */
void MainWindow::on_act_addData_triggered() {
    // Отобразим диалоговое окно. Какой метод нужно использовать?
    dataDb->show();
}

/*!
 * @brief Слот выполняет подключение к БД. И отображает ошибки.
 */

void MainWindow::on_act_connect_triggered() {
    /*
   * Обработчик кнопки у нас должен подключаться и отключаться от БД.
   * Можно привязаться к надписи лейбла статуса. Если он равен
   * "Отключено" мы осуществляем подключение, если "Подключено" то
   * отключаемся
   */

    if (ui->lb_statusConnect->text() == "Отключено") {

        ui->lb_statusConnect->setText("Подключение");
        ui->lb_statusConnect->setStyleSheet("color : black");

        auto conn = [&] { dataBase->ConnectToDataBase(dataForConnect); };
        auto res = QtConcurrent::run(conn);

    } else {
        dataBase->DisconnectFromDataBase(DB_NAME);
        ui->lb_statusConnect->setText("Отключено");
        ui->act_connect->setText("Подключиться");
        ui->lb_statusConnect->setStyleSheet("color:red");
        ui->pb_request->setEnabled(false);
    }
}

/*!
 * \brief Обработчик кнопки "Получить"
 */
void MainWindow::on_pb_request_clicked() {
    dataBase->RequestToDB(ui->cb_category->currentIndex(), requests[ui->cb_category->currentIndex()]);
}

void MainWindow::on_pb_clear_clicked() { ui->tv_result->setModel(nullptr); }


/*!
 * \brief Слот отображает значение в QTableWidget
 * \param widget
 * \param typeRequest
 */
void MainWindow::ScreenDataFromDB(QSqlQueryModel *queryModel,
                                  QSqlTableModel *tableModel,
                                  int type_request) {
    if (type_request == requestType::requestAllFilms) {
        ui->tv_result->setModel(tableModel);
        for (size_t i = 0; i < tableModel->columnCount(); ++i) {
            ui->tv_result->hideColumn(i);
        }
        ui->tv_result->showColumn(1);
        ui->tv_result->showColumn(2);
    } else {
        ui->tv_result->setModel(queryModel);
        ui->tv_result->showColumn(0);
    }

    ui->tv_result->resizeColumnsToContents();
    ui->tv_result->resizeRowsToContents();
    ui->tv_result->show();
}

/*!
 * \brief Метод изменяет стотояние формы в зависимости от статуса подключения к
 * БД
 * \param status
 */
void MainWindow::ReceiveStatusConnectionToDB(bool status) {
    if (status) {
        ui->act_connect->setText("Отключиться");
        ui->lb_statusConnect->setText("Подключено к БД");
        ui->lb_statusConnect->setStyleSheet("color:green");
        ui->pb_request->setEnabled(true);
    } else {
        dataBase->DisconnectFromDataBase(DB_NAME);
        msg->setIcon(QMessageBox::Critical);
        msg->setText(dataBase->GetLastError().text());
        ui->lb_statusConnect->setText("Отключено");
        ui->lb_statusConnect->setStyleSheet("color:red");
        msg->exec();
    }
}
