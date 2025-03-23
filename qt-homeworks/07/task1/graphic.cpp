#include "graphic.h"
#include "ui_graphic.h"

Graphic::Graphic(
    QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::Graphic)
{
    ui_->setupUi(this);
    chart_ = new QChart();
    chart_->legend()->setVisible(false);
    //Объект QChartView является виджетом отображальщиком графика.
    //В его конструктор передается ссылка на объект QChart.
    chart_view_ = new QChartView(chart_);
    line_series_ = new QLineSeries();
    ui_->gridLayout->addWidget(chart_view_);
    chart_view_->show();
}

Graphic::~Graphic()
{
    delete ui_;
}

void Graphic::UpdateData(QVector<double> x, QVector<double> y){
    ClearData();
    line_series_ = new QLineSeries();
    AddData(x, y);
    chart_->addSeries(line_series_);
    chart_->createDefaultAxes();
    emit sig_graphic();
}

void Graphic::AddData(QVector<double> x, QVector<double> y) {
    uint32_t sz = (x.size() >= y.size()) ? y.size() : x.size();
    for (uint32_t i = 0; i < sz; ++i) {
        line_series_->append(x[i], y[i]);
    }
}

void Graphic::ClearData() {
    line_series_->clear();
    if (!(chart_->series().empty())) {
        chart_->removeSeries(line_series_);
    }
}

