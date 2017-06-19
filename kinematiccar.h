#ifndef KINEMATICCAR_H
#define KINEMATICCAR_H

#include <QVector>
#include "mobilerobot.h"

class KinematicCar : public MobileRobot
{
public:
    double l;

    KinematicCar(double length);

    KinematicCar(QVector<double> qstart, double length);

    QVector<double> dq(QVector <double> deltaQ);

    QVector<double> dqLie(QVector <double> deltaQ);
};

#endif // KINEMATICCAR_H
