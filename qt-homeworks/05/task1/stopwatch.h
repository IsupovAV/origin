#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class StopWatch : public QObject {
  Q_OBJECT

public:
  explicit StopWatch(QObject *parent = nullptr);

  void startStopWath();
  void stopStopWatch();
  void resetStopWatch();

  QString getStrTime();

private:
  int milliseconds_, seconds_, minutes_, hours_;
  int lap_milliseconds_;
  int seconds_circle_;
  bool reset_timer_ = true;
  int time_prev_lap_ = 0;
  QString str_time_;

  QTimer *timer_;

public slots:
  void slotUpdateTime();

  void slotUpdateLapTime();

signals:
  void sig_SendCircleTime(QString str);
};

#endif // STOPWATCH_H
