#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "qcustomplot.h"
#include <QMainWindow>

namespace Ui {
class Graphic;
}

class Graphic : public QMainWindow {
    Q_OBJECT

public:
    explicit Graphic(QWidget *parent = nullptr);
    ~Graphic();

    void AddGraphic(QVector<double> x, QVector<double> y);
    void ClearGraphic();

private:
    Ui::Graphic *ui_;
    QCPGraph *graphic_;
};

#endif // GRAPHIC_H
