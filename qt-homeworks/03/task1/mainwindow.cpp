#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "setdbconnection.h"

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent), ui (new Ui::MainWindow)
{
  ui->setupUi (this);

  set_connection = new SetDBConnection(this);
}

MainWindow::~MainWindow () { delete ui; }

void MainWindow::on_pb_setupConnection_clicked()
{
  set_connection->show();
}

