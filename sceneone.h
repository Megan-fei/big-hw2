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
#include "audioplayer.h"

class tower;
class virus;
class Medicine;
class towert;
class Scene:public QMainWindow
{
    Q_OBJECT
public:
    Scene(QWidget *parent = nullptr);
    ~Scene();
    virtual void paintevent(QPaintEvent *event){};
    virtual void loadseats(){};

    virtual bool loadwave(){};
    virtual void loadwaypoints(){};

    //public
    bool canbuytower()const;
    void getCampHurt(int damage);
    void removeVirus(virus *viru);
    void removemed(Medicine* med);
    void removetower(tower* towe,QPoint position);
    void removetowert(towert *towe,QPoint position);
    void addmed(Medicine* med);
    void gameover();
    int showgold();
    void spendmoney(int price);
    //related to the game
    void award(int money);

    //related to the screen
    void drawwave(QPainter *painter);
    void drawhp(QPainter *painter);
    void drawgold(QPainter *painter);
    void drawbgrect(QPainter *painter);

    QList<virus *> viruslist() const;
public slots:
    void updatemap();
    tower* build(QPoint position);
    towert* buildt(QPoint position);
protected:
    QList<virus *> viruses;
    QList<seat> seats;
    //related to towers
    QList<tower *> towerslist;
    //related to waypoints
    QList<WayPoint *> waypoints;

    //related to enemies and waves

    //related to the game
    int wavenow =0;
    bool whetherwin = false;
    bool whetherlose = false;
    int playergold=4000;
    audioplayer* myaudioplayer;

    QList<Medicine *> medicines;

    //related to base
    double Hpbase=10;
};

class Sceneone : public Scene
{
    Q_OBJECT
public:
    explicit Sceneone(QWidget *parent = nullptr);
    ~Sceneone();
    void paintEvent(QPaintEvent *event);
    //related to seats
    void loadseats();
//    //related to towers
//    bool canbuytower()const;
    //void mousePressEvent(QMouseEvent *event);
    //related to virus and waves
//    void getCampHurt(int damage);
//    void removeVirus(virus *viru);//removeEnemy
    bool loadwave();
    //related to waypoints
    void loadwaypoints();

    //related to enemies

//    QList<virus *> viruslist() const;

    //related to medicines
//    void removemed(Medicine* med);
//    void addmed(Medicine* med);
    //related to base
//    void gameover();
//    QList<virus *> viruses;

//    //related to the game
//    void award(int money);

//    //related to the screen
//    void drawwave(QPainter *painter);
//    void drawhp(QPainter *painter);
//    void drawgold(QPainter *painter);
//    void drawbgrect(QPainter *painter);

//    void removetower(tower* towe,QPoint position);
//    void removetowert(towert *towe,QPoint position);

//    int showgold();
//    void spendmoney(int price);

public slots:
//        void updatemap();
    //???????????????
//        tower* build(QPoint position);
//        towert* buildt(QPoint position);
        //void pulldown(QPoint position);

protected:
    //related to seats
//    QList<seat> seats;
//    //related to towers
//    QList<tower *> towerslist;
//    //related to waypoints
//    QList<WayPoint *> waypoints;

//    //related to enemies and waves

//    //related to the game
//    int wavenow =0;
//    bool whetherwin = false;
//    bool whetherlose = false;
//    int playergold=4000;
//    audioplayer* myaudioplayer;

//    QList<Medicine *> medicines;

//    //related to base
//    double Hpbase=10;
};
class Scenetwo:public Scene
{
    Q_OBJECT
public:
    Scenetwo(QWidget *parent = nullptr);
    ~Scenetwo();
    void paintEvent(QPaintEvent *event);
    void loadseats();
    void loadwaypoints();
    bool loadwave();
};



#endif // SCENEONE_H
