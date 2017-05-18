#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "trajectory.h"
#include <iostream>
#include "unicycle.h"
#include <QVector>
#include "qcustomplot.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plot = new QCustomPlot(ui->wykres);
    plot->setGeometry(QRect(QPoint(3, 3),QSize(540, 570)));
    plot->xAxis->setRange(-6, 6);
    plot->xAxis->setLabel("x");
    plot->yAxis->setRange(-4, 4);
    plot->yAxis->setLabel("y");
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->axisRect()->setupFullAxesBox();
    plot->rescaleAxes();
    int t = 1;
    if (t<10)
    {

        QVector<double> uniparams;
        uniparams.resize(3);
        uniparams[0]=0.0;
        uniparams[1]=0.0;
        uniparams[2]=0.0;

        Unicycle* unic = new Unicycle(uniparams);

        Trajectory* t = unic->executeMotion(1, 1, -1);

        cout<<(t->traj[0].size())<<endl;

        plot->addGraph();
        plot->graph(0)->addData(t->traj[0],t->traj[2],true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonOblicz_clicked()
{

}



