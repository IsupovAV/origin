#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setdbconnection.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow (QWidget *parent = nullptr);
  ~MainWindow ();

private slots:
  void on_pb_setupConnection_clicked();

private:
  Ui::MainWindow *ui;
  SetDBConnection *set_connection;

};
#endif // MAINWINDOW_H
