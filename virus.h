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
class Scene;
class tower;
class virus : public QObject
{
    Q_OBJECT
public:
    virus(WayPoint *startPoint,Scene *game,const QPixmap &fig);//construct function
    void draw(QPainter *painter);//paint the virus
    void move();//the virus go step by step
    ~virus();
    void getattacked(tower* towe);
    void gotlostsight(tower* towe);
    void gethurt(int damage);
    void getremoved();
    QPoint pos() const;

    void slowdown();

signals:

public slots:
     void activate();//set it as active
     void recoverspeed();

protected:
    int killedaward;
    int basicaward;
    int bonusaward;
    double Hplife;//HP total
    double Hpnow;//HP now
    double speed;//speed
    WayPoint * goalpoint;//next  waypoint
    QPoint position;//position now
    QPixmap figure;//figure of the virus
    Scene *game;//???????what type???????sceneone or mainwindow or what?
    double rotation;//the angle needs to turn at next way point
    bool active = false;//whether this virus can move??what usage

    QList<tower *>attackers;

    static const QSize fixedsize;
};
class virust:public virus
{
public:
    virust(WayPoint *startPoint,Scene *game,const QPixmap &fig);
    ~virust();
};
class virusth:public virus
{
public:
    virusth(WayPoint *startPoint,Scene *game,const QPixmap &fig);
    ~virusth();
};
class virusf:public virus
{
public:
    virusf(WayPoint *startPoint,Scene *game,const QPixmap &fig);
    ~virusf();
};

#endif // VIRUS_H

