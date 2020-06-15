#include "waypoint.h"
#include <QPainter>
#include <QPoint>


//construct function
WayPoint::WayPoint(QPoint pos)
{
    position=pos;
    nextpoint=NULL;
}
//copy construct function
WayPoint::WayPoint(const WayPoint * point)
{
    this->position=point->pos();
    this->nextpoint=point->nextwaypoint();
}


//set which one is last way point
void WayPoint::setnextpoint(WayPoint *nextone)
{
    nextpoint=nextone;
}
//return last waypoint
WayPoint* WayPoint::nextwaypoint() const//什么用
{
    return nextpoint;
}
//return the present  point
const QPoint WayPoint::pos() const//什么用
{
    return position;
}

//draw the way and way points
void WayPoint::draw(QPainter *painter) const
{
    painter->save();//firstly save its initial "shezhi"
    painter->setPen(Qt::blue);
    painter->drawEllipse(position,5,5);
    painter->drawEllipse(position,10,10);
    if(nextpoint)//make sure there's a nextpoint
        painter->drawLine(position,nextpoint->position);
    painter->restore();//finally make it to the initial stage
}

