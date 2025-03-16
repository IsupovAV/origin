#include "stopwatch.h"

StopWatch::StopWatch(QObject *parent)
    : QObject{parent}, milliseconds_(0), seconds_(0), minutes_(0), hours_(0),
      lap_milliseconds_(0) {
  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this, &StopWatch::slotUpdateTime);
  str_time_ = "00:00:00,0";
}

void StopWatch::startStopWath() { timer_->start(100); }

void StopWatch::stopStopWatch() { timer_->stop(); }

void StopWatch::resetStopWatch() {
  milliseconds_ = 0;
  seconds_ = 0;
  minutes_ = 0;
  hours_ = 0;
  time_prev_lap_ = 0;
  lap_milliseconds_ = 0;
  str_time_ = "00:00:00,0";
}

QString StopWatch::getStrTime()
{
  return str_time_;
}

void StopWatch::slotUpdateLapTime() {
  auto lap_time = lap_milliseconds_ - time_prev_lap_;
  time_prev_lap_ = lap_milliseconds_;

  auto str_lap_time = QString::number(lap_time);
  emit sig_SendCircleTime(str_lap_time);
}

void StopWatch::slotUpdateTime() {
  milliseconds_++;
  lap_milliseconds_++;

  if(milliseconds_ >= 10) {
      milliseconds_ = 0;
      ++seconds_;
    }
  if(seconds_ >= 60) {
      seconds_ = 0;
      ++minutes_;
    }

  if(minutes_ >= 60) {
      minutes_ = 0;
      ++hours_;
    }

  str_time_ =  QString("%1").arg(hours_, 2, 10, QChar('0')) +
      ":" + QString("%1").arg(minutes_, 2, 10, QChar('0')) +
      ":" + QString("%1").arg(seconds_, 2, 10, QChar('0')) +
            "," + QString("%1").arg(milliseconds_, 1, 10, QChar('0'));

}


