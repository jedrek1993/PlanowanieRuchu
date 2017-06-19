#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QVector>
#include "cbhdprocedure.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QCustomPlot *plot;
    QCPCurve *Spiral1, *Spiral2, *Spiral3;
    QVector<QLabel*> nameVariableLabel,valueVariableLabel,lieVariableLabel, errorLabel;
    QLabel* column0name;
    QLabel* column1name;
    QLabel* column2name;
    QLabel* column3name;

    void showFinalPositionPanel(CBHDProcedure* CBHDArg, Trajectory* t1, Trajectory* t2);
    void clearFinalPositionPanel();


private slots:
    void on_buttonOblicz_clicked();
    void changeStartBoxMaximum();
    void showLengthChoice();
    void initialZoom();
    void targetedZoom();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
