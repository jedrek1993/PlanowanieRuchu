#include "mobilerobot.h"
#include <QVector>
#include <functional>

#include <iostream>

using namespace std;

Trajectory* MobileRobot::executeMotion(double timeOfStep, int control, double value, int numberOfSteps, std::function<QVector<double> (QVector<double>)> dqType)
{

    Trajectory* t = new Trajectory(q.size(),timeOfStep,numberOfSteps);

    u[control-1]=value;

    for (int i=0;i<q.size();i++)    t->traj[i][0]=q[i];

    QVector <double> zeros;
    QVector <QVector<double> > K;
    zeros.resize(q.size());
    K.resize(4);

    for (int i=0;i<q.size();i++)    zeros[i]=0;


    for (int i=0;i<4;i++)   K[i].resize(q.size());


    for (int count=0;count<numberOfSteps;count++)
    {
        for (int i=0;i<K[0].size();i++) K[0][i]=timeOfStep*dqType(zeros)[i];

        QVector<double> k0,k1;
        k0.resize(q.size());
        k1.resize(q.size());

        for (int i=0;i<k0.size();i++) k0[i]=K[0][i]/2;

        for (int i=0;i<k0.size();i++) K[1][i]=timeOfStep*(dqType(k0))[i];

        for (int i=0;i<k1.size();i++) k1[i]=K[1][i]/2;

        for (int i=0;i<K[1].size();i++) K[2][i]=timeOfStep*dqType(k1)[i];

        for(int i=0;i<K[2].size();i++) K[3][i]=timeOfStep*dqType(K[2])[i];


        for (int i=0;i<q.size();i++)
        {
            t->traj[i+1][count]=q[i]+(K[0][i]+2*K[1][i]+2*K[2][i]+K[3][i])/6;
            q[i] = t->traj[i+1][count];
        }
    }

    u[control-1]=0;

    return t;
}
