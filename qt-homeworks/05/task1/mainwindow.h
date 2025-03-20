#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>

#include"stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  StopWatch* stopwatch_;
  bool is_start_ = true;

  int number_lap_ = 0;

public slots:
  void UpdateTime();


private slots:
  void rcvCircleTime(QString str);

  void on_pb_circle_clicked();
  void on_pb_start_stop_clicked();
  void on_pb_reset_clicked();
};
#endif // MAINWINDOW_H
