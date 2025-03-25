#ifndef SETDBCONNECTION_H
#define SETDBCONNECTION_H

#include <QDialog>

namespace Ui {
class SetDBConnection;
}

class SetDBConnection : public QDialog {
  Q_OBJECT

public:
  explicit SetDBConnection(QWidget *parent = nullptr);
  ~SetDBConnection();

  signals:
  void sig_sendData(QVector<QString> dbData);

private slots:
  void on_buttonBox_accepted();


private:
  Ui::SetDBConnection *ui;
  QVector<QString> data;
};

#endif // SETDBCONNECTION_H
