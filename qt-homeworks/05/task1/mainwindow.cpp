#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("Секундомер");

  stopwatch_ = new StopWatch(this);

  ui->pb_start_stop->setText("Старт");
  ui->pb_circle->setEnabled(false);

  stopwatch_->startTimer(1);

  connect(stopwatch_->getTimer(), &QTimer::timeout, this, &MainWindow::UpdateTime);

  connect(stopwatch_, &StopWatch::sig_SendCircleTime, this,
           &MainWindow::rcvCircleTime);

  int id = QFontDatabase::addApplicationFont(":/7fonts.ru_DS-DIGII.TTF");
  QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  QFont digit(family, 48);
  ui->lb_time->setFont(digit);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::UpdateTime() {
  QString str = stopwatch_->getStrTime();
  ui->lb_time->setText(str);
}

void MainWindow::rcvCircleTime(QString str) {
  uint time_passed = str.toUInt();
  QString lap = QString::number(number_lap_);
  QString sec = QString::number(time_passed / 10);
  QString dec_sec = QString::number(time_passed % 10);

  ui->te_browser->append("Круг " + lap +
                          " время: " + sec + "," + dec_sec + " сек.");
}

void MainWindow::on_pb_start_stop_clicked() {
  if (is_start_) {

      is_start_ = false;
      ui->pb_start_stop->setText("Стоп");
      stopwatch_->startStopWath();
      ui->pb_circle->setEnabled(true);
    } else {
      is_start_ = true;
      ui->pb_start_stop->setText("Старт");
      stopwatch_->stopStopWatch();
      ui->pb_circle->setEnabled(false);
    }
}

void MainWindow::on_pb_reset_clicked() {
  ui->te_browser->clear();

  stopwatch_->resetStopWatch();

  number_lap_ = 0;

  ui->lb_time->setText(stopwatch_->getStrTime());
}

void MainWindow::on_pb_circle_clicked() {
  ++number_lap_;
  stopwatch_->slotUpdateLapTime();
}
