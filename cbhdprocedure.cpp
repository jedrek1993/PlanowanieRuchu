#include "cbhdprocedure.h"
#include "mobilerobot.h"
#include <iostream>
#include <QVector>
#include<functional>

using namespace std;

CBHDProcedure::CBHDProcedure(MobileRobot* mr, double t_arg, int N_arg, int s0_arg) :
    robot(mr),t(t_arg),N(N_arg),s0(s0_arg)
{
   defaultPosition.resize(robot->q.size());

   for (int i=0;i<defaultPosition.size();i++)
       defaultPosition[i]=robot->q[i];
}

Trajectory* CBHDProcedure::CBHDexecute()
{
    double timeOfStep = t/N;
    Trajectory* tr = new Trajectory(robot->q.size(),timeOfStep,4*N+1);

    auto dqNormal = std::bind(&MobileRobot::dq,robot,std::placeholders::_1);


    if (s0<N)
    {
        tr=robot->executeMotion(t/N,1,1,N-s0,dqNormal);
        tr->addTrajectory(robot->executeMotion(t/N,2,1,N,dqNormal));
        tr->addTrajectory(robot->executeMotion(t/N,1,-1,N,dqNormal));
        tr->addTrajectory(robot->executeMotion(t/N,2,-1,N,dqNormal));
        if (s0!=0)
            tr->addTrajectory(robot->executeMotion(t/N,1,1,s0,dqNormal));

    }

    if (s0>=N && s0<2*N)
    {

        tr=robot->executeMotion(t/N,2,1,N-(s0%N),dqNormal);
        tr->addTrajectory(robot->executeMotion(t/N,1,-1,N,dqNormal));
        tr->addTrajectory(robot->executeMotion(t/N,2,-1,N,dqNormal));
        tr->addTrajectory(robot->executeMotion(t/N,1,1,N,dqNormal));
        if (s0%N!=0)
            tr->addTrajectory(robot->executeMotion(t/N,2,1,s0%N,dqNormal));
    }

    if (s0>=2*N && s0<3*N)
    {
        tr=robot->executeMotion(t/N,1,-1,N-(s0%N),dqNormal);
        tr->addTrajectory(robot->executeMotion(t/N,2,-1,N,dqNormal));
        tr->addTrajectory(robot->executeMotion(t/N,1,1,N,dqNormal));
        tr->addTrajectory(robot->executeMotion(t/N,2,1,N,dqNormal));
        if(s0%N!=0)
            tr->addTrajectory(robot->executeMotion(t/N,1,-1,s0%N,dqNormal));
    }

    if (s0>=3*N)
    {
        tr=robot->executeMotion(t/N,2,-1,N-(s0%N),dqNormal);
        tr->addTrajectory(robot->executeMotion(t/N,1,1,N,dqNormal));
        tr->addTrajectory(robot->executeMotion(t/N,2,1,N,dqNormal));
        tr->addTrajectory(robot->executeMotion(t/N,1,-1,N,dqNormal));
        if (s0%N!=0)
            tr->addTrajectory(robot->executeMotion(t/N,2,-1,s0%N,dqNormal));

    }

    returnToDefaultPosition();

    return tr;
}

Trajectory* CBHDProcedure::designateExpectedPosition()
{
    robot->q[0]=0;
    robot->q[1]=0;
    robot->q[2]=0;

    auto dqLie = std::bind(&MobileRobot::dqLie,robot,std::placeholders::_1);


    double timeOfStep = t/N;
    Trajectory* tr = new Trajectory(robot->q.size(),timeOfStep,N);

    tr=robot->executeMotion(t*t/N,1,1,N,dqLie);

    returnToDefaultPosition();

    return tr;

}

void CBHDProcedure::returnToDefaultPosition()
{
    robot->q=defaultPosition;
}


