#ifndef SCENEONE_H
#define SCENEONE_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include "seat.h"
#include "tower.h"
#include "waypoint.h"
#include "virus.h"
#include "medicine.h"

class tower;
class virus;
class Medicine;
class Sceneone : public QMainWindow
{
    Q_OBJECT
public:
    explicit Sceneone(QWidget *parent = nullptr);
    ~Sceneone();
    void paintEvent(QPaintEvent *event);
    //related to seats
    void loadseats();
    //related to towers
    bool canbuytower()const;
    void mousePressEvent(QMouseEvent *event);
    //related to virus and waves
    void getCampHurt(int damage);
    void removeVirus(virus *viru);//removeEnemy
    bool loadwave();
    //related to waypoints
    void loadwaypoints();

    //related to enemies

    QList<virus *> viruslist() const;

    //related to medicines
    void removemed(Medicine* med);
    void addmed(Medicine* med);
    //related to base
    void gameover();
    QList<virus *> viruses;
signals:

public slots:
        void updatemap();

private:
    //related to seats
    QList<seat> seats;
    //related to towers
    QList<tower *> towerslist;
    //related to waypoints
    QList<WayPoint *> waypoints;

    //related to enemies and waves

    int wavenow =0;
    //
    bool whetherwin = false;
    bool whetherlose = false;
    QList<Medicine *> medicines;

    //related to base
    double Hpbase=10;

};

#endif // SCENEONE_H
