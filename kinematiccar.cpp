#include "kinematiccar.h"
#include <QVector>

KinematicCar::KinematicCar(double length) :
    l(length)
{
    q.resize(4);
    q={0.0, 0.0, 0.0, 0.0};

    qnames.resize(4);
    qnames = {"x","y","theta","phi"};

    u.resize(2);
    u={0.0, 0.0};
}

KinematicCar::KinematicCar(QVector<double> qstart, double length):
    l(length)
{
    l=5;

    this->q.resize(4);
    this->q[0]=qstart[0];
    this->q[1]=qstart[1];
    this->q[2]=qstart[2];
    this->q[3]=qstart[3];

    this->u.resize(2);
    this->u[0]=0;
    this->u[1]=0;
}


QVector<double> KinematicCar::dq(QVector <double> deltaQ={0,0,0,0})
{
    QVector<double> velocity;

    velocity.resize(q.size());
    velocity[0]=u[0]*cos(q[2]+deltaQ[2])*cos(q[3]+deltaQ[3]);
    velocity[1]=u[0]*sin(q[2]+deltaQ[2])*cos(q[3]+deltaQ[3]);
    velocity[2]=u[0]*sin(q[3]+deltaQ[3])/l;
    velocity[3]=u[1];
    return velocity;
}

QVector<double> KinematicCar::dqLie(QVector <double> deltaQ={0,0,0,0})
{
    QVector<double> velocity;

    velocity.resize(q.size());
    velocity[0]=cos(q[2]+deltaQ[2])*sin(q[3]+deltaQ[3]);
    velocity[1]=sin(q[2]+deltaQ[2])*sin(q[3]+deltaQ[3]);
    velocity[2]=-cos(q[3]+deltaQ[3])/l;
    velocity[3]=0;
    return velocity;
}
