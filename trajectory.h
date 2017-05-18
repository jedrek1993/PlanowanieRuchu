#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include<QVector>

class Trajectory
{
public:
    QVector <QVector<double> > traj;

    Trajectory(int stateVectorLength, double timespan, double step);

};

#endif // TRAJECTORY_H
