#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

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
    QCPCurve *patch;

private slots:
    void on_buttonOblicz_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
