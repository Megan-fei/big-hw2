#ifndef VIRUS_H
#define VIRUS_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include "waypoint.h"
#include "mainwindow.h"
#include <QSize>
#include "sceneone.h"

//继承QObject？
class Sceneone;
class tower;
class virus : public QObject
{
    Q_OBJECT
public:
    virus(WayPoint *startPoint,Sceneone *game,const QPixmap &fig);//construct function
    void draw(QPainter *painter);//paint the virus
    void move();//the virus go step by step
    ~virus();
    void getattacked(tower* towe);
    void gotlostsight(tower* towe);
    void gethurt(int damage);
    void getremoved();
    QPoint pos() const;
signals:

public slots:
     void activate();//set it as active

private:
    double Hplife;//HP total
    double Hpnow;//HP now
    double speed;//speed
    WayPoint * goalpoint;//next  waypoint
    QPoint position;//position now
    QPixmap figure;//figure of the virus
    Sceneone *game;//???????what type???????sceneone or mainwindow or what?
    double rotation;//the angle needs to turn at next way point
    bool active = false;//whether this virus can move??what usage

    QList<tower *>attackers;

    static const QSize fixedsize;
};

#endif // VIRUS_H

