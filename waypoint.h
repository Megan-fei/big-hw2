#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPoint>
#include <QPainter>

class WayPoint
{
public:
    WayPoint(QPoint position);//construct function
    WayPoint(const WayPoint * point);//copy construct function

    void setnextpoint(WayPoint *lastone);//set which one is the next way point
    WayPoint* nextwaypoint() const;//return next way point
    const QPoint pos() const;//return this point

    void draw(QPainter *painter) const;//draw the way points
private:
    QPoint position;
    WayPoint *nextpoint;
};

#endif // WAYPOINT_H
