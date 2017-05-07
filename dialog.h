#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "qcustomplot.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QCustomPlot *plot;
    QCPCurve *patch;

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
