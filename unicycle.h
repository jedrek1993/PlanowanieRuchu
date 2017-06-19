#ifndef UNICYCLE_H
#define UNICYCLE_H

#include<QVector>
#include"mobilerobot.h"
#include "trajectory.h"

class Unicycle : public MobileRobot
{
public:
    Unicycle();

    Unicycle(QVector<double> qstart);

    QVector<double> dq(QVector <double> deltaQ);

    QVector<double> dqLie(QVector <double> deltaQ);


};

#endif // UNICYCLE_H
