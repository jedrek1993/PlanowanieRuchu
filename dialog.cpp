#include "dialog.h"
#include "ui_dialog.h"

#include "qcustomplot.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    plot = new QCustomPlot(ui->widget);
    plot->setGeometry(QRect(QPoint(1, 1),QSize(720, 470)));
    plot->xAxis->setRange(-6, 6);
    plot->yAxis->setRange(-4, 4);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->axisRect()->setupFullAxesBox();
    plot->rescaleAxes();
}

Dialog::~Dialog()
{
    delete ui;
}
