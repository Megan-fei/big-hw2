#ifndef UTILITY_H
#define UTILITY_H

#include <QPoint>
#include <QtMath>
#include <QDebug>

//class utility
//{
//public:
//    utility();
//    bool collisionWithTurnpoint(QPoint point1, int r1,const QPoint point2, int r2);
//};

inline bool collisionWithTurnpoint(QPoint point1, int r1,const QPoint point2, int r2)
{
    //qDebug()<<"collision or not";

    double xd=point1.x()-point2.x();
    double yd=point1.y()-point2.y();
    double d=qSqrt(xd*xd+yd*yd);
    if(d<=r1+r2)
    {
        //qDebug("^collided,xd=%f,yd=%f,d=%f",xd,yd,d);
        return true;
    }
    else
    {
       // qDebug("!not collided,xd=%f,yd=%f,d=%f",xd,yd,d);
        return false;
    }
}
#endif // UTILITY_H
