#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QMainWindow>

#include <QLineSeries>
#include <QtCharts>
#include <QChartView>

namespace Ui {
class Graphic;
}

class Graphic : public QMainWindow
{
    Q_OBJECT

public:
    explicit Graphic(QWidget *parent = nullptr);
    ~Graphic();

    void AddData(QVector<double> x, QVector<double> y);
    void ClearData();
    void UpdateData(QVector<double> x, QVector<double> y);

signals:
    void sig_graphic();

private:
    Ui::Graphic *ui_;
    QLineSeries *line_series_;
    QChart* chart_;
    QChartView* chart_view_;


};

#endif // GRAPHIC_H
