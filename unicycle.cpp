#include "unicycle.h"
#include "mobilerobot.h"
#include <math.h>
#include <iostream>
#include "trajectory.h"
using namespace std;

Unicycle::Unicycle(QVector<double> qstart)
{

    this->q.resize(3);
    this->q[0]=qstart[0];
    this->q[1]=qstart[1];
    this->q[2]=qstart[2];

    this->u.resize(2);
    this->u[0]=0;
    this->u[1]=0;
}

QVector <double> Unicycle :: dx()
{
    QVector<double> velocity;

    velocity.resize(q.size());
    velocity[0]=u[0]*cos(q[1]);
    velocity[1]=u[0]*sin(q[1]);
    velocity[2]=u[1];
    return velocity;
}

Trajectory* Unicycle::executeMotion(double time, int control, double value)
{


    Trajectory* t = new Trajectory(q.size(),time,0.01);

    u[control-1]=value;

    for (int i=1;i<q.size();i++)
    {
        for (int j=0;j<(t->traj[0].size());j++)
        {
            t->traj[i][j]=i+j;
        }
    }

    u[control-1]=0;
    return t;
}
