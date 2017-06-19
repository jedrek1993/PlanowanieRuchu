#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include<QVector>

class Trajectory
{
public:
    QVector <QVector<double> > traj;

    Trajectory(int stateVectorLength, double timeOfStep, int numberOfStep);

    void addTrajectory(const Trajectory* Traj);

};

#endif // TRAJECTORY_H
