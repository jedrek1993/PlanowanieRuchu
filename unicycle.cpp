#include "unicycle.h"
#include "mobilerobot.h"
#include <math.h>
#include <iostream>
#include "trajectory.h"
using namespace std;

Unicycle::Unicycle()
{
    q.resize(3);
    q = {0.0, 0.0, 0.0};

    u.resize(2);
    u = {0.0, 0.0};

    qnames.resize(q.size());
    qnames = {"x","y","theta"};
}

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

QVector <double> Unicycle :: dq(QVector<double> deltaQ)
{
    QVector<double> velocity;

    velocity.resize(q.size());
    velocity[0]=u[0]*cos(q[2]+deltaQ[2]);
    velocity[1]=u[0]*sin(q[2]+deltaQ[2]);
    velocity[2]=u[1];
    return velocity;
}

QVector <double> Unicycle:: dqLie(QVector<double> deltaQ)
{
    QVector<double> velocity;

    velocity.resize(q.size());
    velocity[0]=sin(q[2]+deltaQ[2]);
    velocity[1]=-cos(q[2]+deltaQ[2]);
    velocity[2]=0;
    return velocity;

}
