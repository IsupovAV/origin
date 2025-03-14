#include "setdbconnection.h"
#include "ui_setdbconnection.h"

SetDBConnection::SetDBConnection (QWidget *parent)
    : QDialog (parent), ui (new Ui::SetDBConnection)
{
  ui->setupUi (this);
}

SetDBConnection::~SetDBConnection () { delete ui; }


