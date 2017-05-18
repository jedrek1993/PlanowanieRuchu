#ifndef UNICYCLE_H
#define UNICYCLE_H

#include<QVector>
#include"mobilerobot.h"
#include "trajectory.h"

class Unicycle : public MobileRobot
{
public:
    Unicycle(QVector<double> qstart);

    QVector<double> dx();

    Trajectory* executeMotion(double time, int control, double value);


};

#endif // UNICYCLE_H
