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

private:
  Ui::SetDBConnection *ui;
};

#endif // SETDBCONNECTION_H
