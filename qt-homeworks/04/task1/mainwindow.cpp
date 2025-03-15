#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->groupBox->setTitle("Установить шаг прогресс-бар");
  ui->rd_one->setText("шаг 10%");
  ui->rd_two->setText("шаг 20%");
  ui->rd_one->setChecked(true);

  ui->pbar_process->setMaximum(10);
  ui->pbar_process->setMinimum(0);
  ui->pbar_process->setValue(0);
  ui->pbar_process->setFormat("%p%");

  ui->pb_com->setCheckable(true);
  ui->pb_com->setText("Запуск прогрес-бар");

  ui->cb_list->addItem("Python");
  ui->cb_list->addItem("C++");
  ui->cb_list->addItem("Java");
  ui->cb_list->addItem("C#");
  ui->cb_list->addItem("JavaScript");
  ui->cb_list->addItem("Go");
  ui->cb_list->addItem("Rust");
  ui->cb_list->addItem("Ruby");
  ui->cb_list->addItem("Swift");
  ui->cb_list->addItem("Kotlin");
  ui->cb_list->addItem("SQL");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pb_com_toggled(bool checked) {
  if (checked) {

      ui->pb_com->setStyleSheet("background-color : green");

      uint current_val = ui->pbar_process->value();
      if (ui->rd_one->isChecked()) {
          ++current_val;
        } else
        current_val += 2;

      if (current_val > 10) {
          current_val = 0;
          ui->pbar_process->setValue(0);
        }
      ui->pbar_process->setValue(current_val);
      ui->cb_list->setCurrentIndex(current_val % 11);
    } else {
      ui->pb_com->setStyleSheet("background-color : light grey");
    }
}
