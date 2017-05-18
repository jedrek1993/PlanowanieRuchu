#ifndef MOBILEROBOT_H
#define MOBILEROBOT_H

#include<QVector>
#include"trajectory.h"

class MobileRobot
{
public:

    QVector<double> q;
    QVector<double> u;

    virtual QVector<double> dx()=0;

    virtual Trajectory* executeMotion (double time, int control, double value)=0;

};

#endif // MOBILEROBOT_H
