#include "trajectory.h"
#include <iostream>
#include <math.h>

using namespace std;

Trajectory::Trajectory(int stateVectorLength, double timespan, double step)
{
    traj.resize(stateVectorLength+1);

    QVector<double> timeserie;
    timeserie.resize(timespan/step);
    timeserie[0]=0;
    for (int i=1;i<timeserie.size();i++)
    {
        timeserie[i]=timeserie[i-1]+step;
    }

    for (int i=0;i<traj.size();i++)
    {
        traj[i].resize(timeserie.size());
    }

    traj[0]=timeserie;


}
