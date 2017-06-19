#include "trajectory.h"
#include <iostream>
#include <math.h>

using namespace std;

Trajectory::Trajectory(int stateVectorLength, double timeOfStep, int numberOfSteps)
{
    traj.resize(stateVectorLength+1);

    QVector<double> timeserie;
    timeserie.resize(numberOfSteps);
    timeserie[0]=0;
    for (int i=1;i<timeserie.size();i++)
    {
        timeserie[i]=timeserie[i-1]+timeOfStep;
    }

    for (int i=0;i<traj.size();i++)
    {
        traj[i].resize(timeserie.size());
    }

    traj[0]=timeserie;
}

void Trajectory::addTrajectory(const Trajectory* T)
{
    //int initialSize = traj[0].size();
    //int finalSize = traj[0].size()+T->traj[0].size();

    for (int i=0;i<traj.size();i++)
        traj[i].append(T->traj[i]);

}


