#include <QStringView>
#include <algorithm>

#include "statistics.h"
#include "ui_statistics.h"

Statistics::Statistics(QWidget *parent)
    : QDialog(parent), ui(new Ui::Statistics) {

    ui->setupUi(this);

    // Гистограмма
    bar_month_set = new QBarSet("Перелеты в течении года");
    year_bar_series_ = new QBarSeries();
    year_bar_series_->append(bar_month_set);

    year_chart_ = new QChart();
    year_chart_->addSeries(year_bar_series_);
    year_chart_->setTitle("Перелеты в течении года по месяцам");
    year_chart_->setAnimationOptions(QChart::SeriesAnimations);
    year_chart_->legend()->setVisible(false);

    baxis_x = new QBarCategoryAxis();
    baxis_y = new QValueAxis();

    year_chart_->addAxis(baxis_x, Qt::AlignBottom);
    year_bar_series_->attachAxis(baxis_x);

    year_chart_view_ = new QChartView(year_chart_, this);
    year_chart_view_->setRenderHint(QPainter::Antialiasing);

    // Линейный график
    series_day = new QLineSeries;
    chart_day = new QChart;
    chart_day->addSeries(series_day);

    axis_x = new QValueAxis();
    axis_y = new QValueAxis;
    chart_day->addAxis(axis_x, Qt::AlignBottom);
    series_day->attachAxis(axis_x);

    chart_day->addAxis(axis_y, Qt::AlignLeft);
    series_day->attachAxis(axis_y);
    chart_day->legend()->hide();

    axis_x->setLabelFormat("%i");
    axis_x->setTitleText("дни месяца");

    axis_y->setLabelFormat("%i");
    axis_y->setTitleText("вылеты/прилёты");
    year_chart_->addAxis(baxis_y, Qt::AlignLeft);
    year_bar_series_->attachAxis(baxis_y);

    month_chart_view_ = new QChartView(chart_day, this);

    QObject::connect(ui->cmb_month, &QComboBox::currentTextChanged, this, [&] {
        clearLineGraphic();
        displayGraphicForDay(x_, y_);
    });
}

Statistics::~Statistics() { delete ui; }

void Statistics::setAirportName(QString airportName) {
    ui->lb_airport->setText(airportName);
}

void Statistics::requestCongestionYearByMonths(QVector<QString> x,
    QVector<double> y) {

    categories.clear();
    bar_month_set->remove(0, x.size());
    for (int i = 0; i < x.size(); ++i) {
        categories << x[i];
        *bar_month_set << y[i];
    }

    auto max_v = std::max_element(y.begin(), y.end());

    baxis_x->clear();
    baxis_x->append(categories);
    // qDebug() << bar_month_set->count();

    baxis_y->setRange(0, *max_v);

    ui->gridLayoutYear->addWidget(year_chart_view_);
}

void Statistics::displayGraphicForDay(QVector<QString> x, QVector<double> y) {
    if (!x.size())
        return;
    QList<int> days;
    QList<double> labels;

    QString current_month_year = ui->cmb_month->currentText();

    auto index = std::find(x.begin(), x.end(), current_month_year) - x.begin();
    int pos_year = current_month_year.indexOf(' ') + 1;
    int year = current_month_year.mid(pos_year).toInt();
    QString month = current_month_year.mid(0, pos_year - 1);
    if (QDate::isLeapYear(year))
        days_month["Февраль"] = 29;

    for (int i = index; i < index + days_month[month]; ++i) {
        days << i - index + 1;
        labels.push_back(y[i]);
    }

    auto [minValue, maxValue] = std::minmax_element(labels.begin(), labels.end());

    series_day->clear();
    series_day->setPointsVisible();
    QHash<QXYSeries::PointConfiguration, QVariant> conf;
    conf[QXYSeries::PointConfiguration::Color] = QColor(Qt::green);
    conf[QXYSeries::PointConfiguration::Size] = 6;
    conf[QXYSeries::PointConfiguration::LabelVisibility] = false;

    for (int i = 0; i < labels.size(); ++i) {
        QPointF p{static_cast<qreal>(days[i]), labels[i]};
        series_day->append(p);
        series_day->setPointConfiguration(i, conf);
    }

    axis_x->setRange(1, days.size());
    axis_x->setTickCount(days.size());

    int diff = *maxValue - *minValue;
    if (diff > 0) {
        axis_y->setTickCount(diff + 1);
        axis_y->setRange(*minValue, *maxValue);
    } else {
        axis_y->setTickCount(3);
        axis_y->setRange(*minValue - 1, *maxValue + 1);
    }

    month_chart_view_->setRenderHint(QPainter::Antialiasing);
    ui->gridLayoutDay->addWidget(month_chart_view_);
}

void Statistics::requestCongestionMonthByDays(QVector<QString> x,
    QVector<double> y) {
    int index_cb_month = 0;
    auto first = QString("Январь");
    if (x.size() > 0) {
        QString month = x[0];
        ui->cmb_month->addItem(x[0]);
        if (x[0].mid(0, 6) == first) {
            index_cb_month = 0;
        }
        for (int i = 1, j = 0; i < x.size(); ++i) {
            QString nextMonth = x[i];
            if (month != nextMonth) {
                month = nextMonth;
                ui->cmb_month->addItem(x[i]);
                j++;
                if (x[i].mid(0, 6) == first) {
                    index_cb_month = j;
                }
            }
        }
    }
    ui->cmb_month->setCurrentIndex(index_cb_month);

    x_ = x;
    y_ = y;
    displayGraphicForDay(x_, y_);
}

void Statistics::clearBarGraphic() {
    if (year_chart_view_) {
        ui->gridLayoutYear->removeWidget(year_chart_view_);
    }
}

void Statistics::clearLineGraphic() {
    if (month_chart_view_) {
        ui->gridLayoutDay->removeWidget(month_chart_view_);
    }
}

void Statistics::on_Statistics_rejected() {
    clearBarGraphic();
    clearLineGraphic();
}
