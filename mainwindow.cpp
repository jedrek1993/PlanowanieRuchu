#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trajectory.h"
#include <iostream>
#include "unicycle.h"
#include <QVector>
#include "qcustomplot.h"
#include "cbhdprocedure.h"
#include "kinematiccar.h"
#include "math.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->l_label->setVisible(false);
    ui->l_box->setVisible(false);

    plot = new QCustomPlot(ui->wykres);
    plot->setGeometry(QRect(QPoint(3, 3),QSize(540, 570*0.88)));
    initialZoom();
    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->axisRect()->setupFullAxesBox();
    plot->rescaleAxes();

    Spiral1 = new QCPCurve(this->plot->xAxis, this->plot->yAxis);
    Spiral1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 6));

    Spiral2 = new QCPCurve(this->plot->xAxis, this->plot->yAxis);
    Spiral2->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 6));
    Spiral2->setPen(QPen(Qt::red));

    Spiral3 =  new QCPCurve(this->plot->xAxis, this->plot->yAxis);
    Spiral3->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 6));
    Spiral3->setPen(QPen(Qt::green));

    connect(ui->numberBox,SIGNAL(valueChanged(int)),this,SLOT(changeStartBoxMaximum()));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(showLengthChoice()));
    connect(ui->NormalZoom,SIGNAL(clicked()),this,SLOT(initialZoom()));
    connect(ui->TargetedZoom,SIGNAL(clicked()),this,SLOT(targetedZoom()));

    ui->label_4->setVisible(false);
    ui->positionError->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonOblicz_clicked()
{
    clearFinalPositionPanel();

    int robotClassBox = ui->comboBox->currentIndex();
    double timeBox = ui->timeBox->value();
    int numberBox = ui->numberBox->value();
    int startBox = ui->startBox->value();

    MobileRobot* robot;

    if (robotClassBox==0)
    {
        dynamic_cast<Unicycle*>(robot);
        robot = new Unicycle ();
    }

    else if (robotClassBox==1)
    {
        double lengthOfCar = ui->l_box->value();
        dynamic_cast<KinematicCar*>(robot);
        robot = new KinematicCar(lengthOfCar);
    }

    CBHDProcedure* Cexample = new CBHDProcedure(robot,timeBox,numberBox,startBox);


    Trajectory* t1 = Cexample->CBHDexecute();
    Trajectory* t2 = Cexample->designateExpectedPosition();

    cout << t1->traj[1][t1->traj[1].size()-1] << " " << t1->traj[2][t1->traj[2].size()-1] << endl;
    cout << t2->traj[1][t2->traj[1].size()-1] << " " << t2->traj[2][t2->traj[2].size()-1] << endl;

    QVector<QVector<double> > LiePosition;
    LiePosition.resize(2);
    LiePosition[0].resize(1);
    LiePosition[1].resize(1);

    LiePosition[0][0]=t2->traj[1][t2->traj[1].size()-1];
    LiePosition[1][0]=t2->traj[2][t2->traj[2].size()-1];


    QVector<QVector<double> > RealPosition;
    RealPosition.resize(2);
    RealPosition[0].resize(1);
    RealPosition[1].resize(1);

    RealPosition[0][0]=t1->traj[1][t1->traj[1].size()-1];
    RealPosition[1][0]=t1->traj[2][t1->traj[2].size()-1];


    this->Spiral1->setData(t1->traj[1],t1->traj[2]);
    this->Spiral2->setData(LiePosition[0],LiePosition[1]);
    this->Spiral3->setData(RealPosition[0],RealPosition[1]);

    plot->replot();

    showFinalPositionPanel(Cexample,t1,t2);

}


void MainWindow::changeStartBoxMaximum()
{
    int numberBox = ui->numberBox->value();
    ui->startBox->setMaximum(4*numberBox-1);
}

void MainWindow::showLengthChoice()
{
    if (ui->comboBox->currentIndex()==1)
    {
        ui->l_box->setVisible(true);
        ui->l_label->setVisible(true);
    }
    else
    {
        ui->l_box->setVisible(false);
        ui->l_label->setVisible(false);
    }
}

void MainWindow::showFinalPositionPanel(CBHDProcedure* CBHDArg, Trajectory* t1, Trajectory* t2)
{
    ui->label_4->setVisible(true);
    ui->positionError->setVisible(true);

    column0name = new QLabel();
    column1name = new QLabel();
    column2name = new QLabel();
    column3name = new QLabel();

    column0name->setText("zmienna");
    column1name->setText("Real");
    column2name->setText("Lie");
    column3name->setText("Error");

    int stateVectorLength = CBHDArg->robot->q.size();

    nameVariableLabel.resize(stateVectorLength);
    valueVariableLabel.resize(stateVectorLength);
    lieVariableLabel.resize(stateVectorLength);
    errorLabel.resize(stateVectorLength);

    ui->finalPositionLayout->setColumnMinimumWidth(0,10);

    ui->finalPositionLayout->addWidget(column0name,0,0);
    ui->finalPositionLayout->addWidget(column1name,0,1);
    ui->finalPositionLayout->addWidget(column2name,0,2);
    ui->finalPositionLayout->addWidget(column3name,0,3);

    for (int i=0;i<stateVectorLength;i++)
    {
        nameVariableLabel[i] = new QLabel();        
        valueVariableLabel[i] = new QLabel();
        lieVariableLabel[i] = new QLabel();
        errorLabel[i] = new QLabel();

        ui->finalPositionLayout->addWidget(nameVariableLabel[i],i+1,0);
        ui->finalPositionLayout->addWidget(valueVariableLabel[i],i+1,1);
        ui->finalPositionLayout->addWidget(lieVariableLabel[i],i+1,2);
        ui->finalPositionLayout->addWidget(errorLabel[i],i+1,3);

        double realPosition = t1->traj[i+1][t1->traj[i+1].size()-1];
        double liePosition = t2->traj[i+1][t2->traj[i+1].size()-1];
        double error = abs(realPosition-liePosition);

        QString stringValue = QString::number(realPosition,'f',5);
        QString stringLie = QString::number(liePosition,'f',5);
        QString eError = QString::number(error,'f',5);

        nameVariableLabel[i]->setText(CBHDArg->robot->qnames[i]);
        valueVariableLabel[i]->setText(stringValue);
        lieVariableLabel[i]->setText(stringLie);
        errorLabel[i]->setText(eError);
    }

    ui->positionError->setText(QString::number(sqrt((pow(errorLabel[0]->text().toDouble(),2)) + (pow(errorLabel[1]->text().toDouble(),2)))));

}

void MainWindow::clearFinalPositionPanel()
{
    if (ui->finalPositionLayout->isEmpty()==false)
    {
        ui->finalPositionLayout->removeWidget(column0name);
        column0name->deleteLater();

        ui->finalPositionLayout->removeWidget(column1name);
        column1name->deleteLater();

        ui->finalPositionLayout->removeWidget(column2name);
        column2name->deleteLater();

        ui->finalPositionLayout->removeWidget(column3name);
        column3name->deleteLater();

        for (int i=0;i<nameVariableLabel.size();i++)
        {
            ui->finalPositionLayout->removeWidget(nameVariableLabel[i]);
            nameVariableLabel[i]->deleteLater();
            ui->finalPositionLayout->removeWidget(valueVariableLabel[i]);
            valueVariableLabel[i]->deleteLater();
            ui->finalPositionLayout->removeWidget(lieVariableLabel[i]);
            lieVariableLabel[i]->deleteLater();
            ui->finalPositionLayout->removeWidget(errorLabel[i]);
            errorLabel[i]->deleteLater();
        }
    }
}

void MainWindow::initialZoom()
{
    cout << plot->xAxis->range().size() << endl;
    plot->xAxis->setRange(-6, 6);
    plot->yAxis->setRange(-5, 5);

    plot->replot();
}

void MainWindow::targetedZoom()
{
    plot->rescaleAxes(false);

    double xSize = plot->xAxis->range().size();
    double ySize = plot->yAxis->range().size();

    if (xSize>ySize)
        plot->yAxis->setRange(plot->yAxis->range().center()-xSize/2,plot->yAxis->range().center()+xSize/2);

    else if (ySize>xSize)
        plot->xAxis->setRange(plot->xAxis->range().center()-ySize/2,plot->xAxis->range().center()+ySize/2);

    plot->xAxis->scaleRange(2);
    plot->yAxis->scaleRange(2);

    plot->replot();
}
