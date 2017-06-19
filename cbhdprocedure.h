#ifndef CBHDPROCEDURE_H
#define CBHDPROCEDURE_H

#include "mobilerobot.h"
#include "trajectory.h"

class CBHDProcedure
{
public:
    MobileRobot* robot;
    QVector <double> defaultPosition;
    double t;
    int N;
    int s0;

    CBHDProcedure(MobileRobot* mr, double t,int N, int s0);

    Trajectory* CBHDexecute();

    Trajectory* designateExpectedPosition();

    void returnToDefaultPosition();

};

#endif // CBHDPROCEDURE_H
