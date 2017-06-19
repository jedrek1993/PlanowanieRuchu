#ifndef MOBILEROBOT_H
#define MOBILEROBOT_H

#include<QVector>
#include"trajectory.h"
#include<functional>
#include <iostream>

class MobileRobot
{
public:

    QVector<double> q;
    QVector<double> u;
    QVector<QString> qnames;

    virtual QVector<double> dq(QVector<double> deltaQ)=0;

    virtual QVector<double> dqLie(QVector<double> deltaQ)=0;

    virtual Trajectory* executeMotion (double time, int control, double value, int numberOfsteps, std::function<QVector<double> (QVector<double>)> dqType);

};

#endif // MOBILEROBOT_H
