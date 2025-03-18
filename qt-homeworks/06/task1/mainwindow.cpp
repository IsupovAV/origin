#include "mainwindow.h"
#include "./ui_mainwindow.h"

const uint InitNumber = 250'000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->sb_initNum->setValue(InitNumber);
    ui->rb_synchOff->setChecked(true);

    race1 = new Controller(&m);
    race2 = new Controller(&m);

    concurRace1 = new ExampleRace(&m);
    concurRace2 = new ExampleRace(&m);

    // Сигналы по завершению работы потоков
    connect(race1, &Controller::sig_WorkFinish, [&]() {
        // отображаем только когда второй поток закончит работу
        if (countFinish == 0) {
            countFinish++;
        } else {
            ui->te_debug->append("Искомое число равно: " + QString::number(number_) +
                                 ", а должно быть " +
                                 QString::number(ui->sb_initNum->value() * 2));
            ui->pb_start->setEnabled(true);
        }
    });

    connect(race2, &Controller::sig_WorkFinish, [&]() {
        if (countFinish == 0) {
            countFinish++;
        } else {
            ui->te_debug->append("Искомое число равно: " + QString::number(number_) +
                                 ", а должно быть " +
                                 QString::number(ui->sb_initNum->value() * 2));
            ui->pb_start->setEnabled(true);
        }
    });

    connect(concurRace1, &ExampleRace::sig_Finish, [&]() {
        if (countFinish == 0) {
            countFinish++;
        } else {
            ui->te_debug->append("Искомое число равно: " + QString::number(number_) +
                                 ", а должно быть " +
                                 QString::number(ui->sb_initNum->value() * 2));
            ui->pb_start->setEnabled(true);
        }
    });

    connect(concurRace2, &ExampleRace::sig_Finish, [&]() {
        if (countFinish == 0) {
            countFinish++;
        } else {
            ui->te_debug->append("Искомое число равно: " + QString::number(number_) +
                                 ", а должно быть " +
                                 QString::number(ui->sb_initNum->value() * 2));
            ui->pb_start->setEnabled(true);
        }
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

// Метод запускает два потока
void MainWindow::StartRace(void) {

    if (ui->rb_qtConcur->isChecked()) {

        // ui->te_debug->append("Выполни ДЗ!");
        // Тут должен быть код ДЗ
        futConcurRace1 = QtConcurrent::run(&ExampleRace::DoWork, concurRace1,
                                           &number_, ui->rb_qtConcur->isChecked(),
                                           ui->sb_initNum->value());

        futConcurRace2 = QtConcurrent::run(&ExampleRace::DoWork, concurRace2,
                                           &number_, ui->rb_qtConcur->isChecked(),
                                           ui->sb_initNum->value());

    } else {
        race1->operate(&number_, ui->rb_mutexOn->isChecked(),
                       ui->sb_initNum->value());
        race2->operate(&number_, ui->rb_mutexOn->isChecked(),
                       ui->sb_initNum->value());
    }
}

// Обработка кнопки "Старт"
void MainWindow::on_pb_start_clicked() {
    ui->pb_start->setEnabled(false);
    countFinish = 0;
    number_ = 0;
    StartRace();
}
