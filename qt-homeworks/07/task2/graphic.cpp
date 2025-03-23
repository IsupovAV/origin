#include "graphic.h"
#include "ui_graphic.h"

Graphic::Graphic(
    QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::Graphic)
{
    ui_->setupUi(this);
    graphic_ = new QCPGraph(ui_->qcp_graphic->xAxis, ui_->qcp_graphic->yAxis);
    ui_->qcp_graphic->addGraph();

    // для зума и перемещения
    ui_->qcp_graphic->setInteraction(QCP::iRangeZoom, true);
    ui_->qcp_graphic->setInteraction(QCP::iRangeDrag, true);
}

Graphic::~Graphic()
{
    delete ui_;
}

void Graphic::AddGraphic(QVector<double> x, QVector<double> y)
{
    graphic_->addData(x, y);
    ui_->qcp_graphic->rescaleAxes();
    // для перерисовки
    ui_->qcp_graphic->replot();
}

void Graphic::ClearGraphic()
{
    graphic_->data()->clear();
    ui_->qcp_graphic->graph(0)->data()->clear();
    ui_->qcp_graphic->replot();
}
