#ifndef STATISTICS_H
#define STATISTICS_H

#include <QChartView>
#include <QDialog>
#include <QLineSeries>
#include <QtCharts>
#include <cmath>

namespace Ui {
class Statistics;
}

class Statistics : public QDialog {
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = nullptr);
    ~Statistics();

public slots:
    void setAirportName(QString airportName);
    void requestCongestionYearByMonths(QVector<QString> x, QVector<double> y);
    void requestCongestionMonthByDays(QVector<QString> x, QVector<double> y);

private slots:
    void on_Statistics_rejected();

private:
    void clearBarGraphic();
    void clearLineGraphic();
    void displayGraphicForDay(QVector<QString> x, QVector<double> y);

    Ui::Statistics *ui;

    QBarSet *bar_month_set;
    QChartView *year_chart_view_;
    QBarSeries *year_bar_series_;
    QChart *year_chart_;
    QBarCategoryAxis *baxis_x;
    QValueAxis *baxis_y;
    QStringList categories;

    QChartView *month_chart_view_;
    QVector<QString> x_;
    QVector<double> y_;
    QLineSeries *series_day;
    QChart *chart_day;
    QValueAxis *axis_x;
    QValueAxis *axis_y;

    QMap<QString, int> days_month{
                                  {"Январь", 31},   {"Февраль", 28}, {"Март", 31},   {"Апрель", 30},
        {"Май", 31},      {"Июнь", 30},    {"Июль", 31},   {"Август", 31},
        {"Сентябрь", 30}, {"Октябрь", 31}, {"Ноябрь", 30}, {"Декабрь", 31}};
};

#endif // STATISTICS_H
