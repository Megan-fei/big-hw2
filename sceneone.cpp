#include "mainwindow.h"
#include "waypoint.h"
#include "virus.h"
#include "medicine.h"
//#include "audioplayer.h"§
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
//construct function
Sceneone::Sceneone(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800,600);
    this->loadseats();
    this->loadwaypoints();
    this->loadwave();
   // virus *viru1 = new virus(waypoints[0],this,QPixmap(":/nurseone.jpg"));
   // viruses.push_back(viru1);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updatemap()));//update the viruses every 40ms
    timer->start(50);
}
//paint the screen
void Sceneone::paintEvent(QPaintEvent *event)
{
    //if the game has ended
    //*canberevised
    //think again
    //qDebug()<<"!!";
    if(whetherwin||whetherlose)
    {
        qDebug("%d",whetherlose);
        qDebug("%d",whetherwin);
        QString text = whetherlose?"lose":"win";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(),Qt::AlignCenter,text);
        return;
    }
    QPixmap cachepic(":/bgpic.jpg");
        QPainter cachepainter(&cachepic);
        //painter.drawPixmap(0,0,this->width(),this->height(),background);
        int len = 10 ;//统计个数
        for(int i=0; i<len ;++i)
        {
            seats[i].draw(&cachepainter);
        }
        foreach(tower *towe, towerslist)
        {
            towe->draw(&cachepainter);
        }
        foreach(WayPoint *wp,waypoints)
        {
            wp->draw(&cachepainter);
        }
        foreach(virus *viru, viruses)
        {
            viru->draw(&cachepainter);
        }
        foreach(Medicine *med,medicines)
        {
            med->draw(&cachepainter);
        }

        QPainter painter(this);
        painter.drawPixmap(0,0,cachepic);


}
//update function
void Sceneone::updatemap()
{
    //qDebug()<<"updatemap";
    foreach(virus *viru, viruses)
        viru->move();
    foreach(tower *towe, towerslist)
        towe->checkenemy();
    update();//？？？？？？？
}
//load seats
void Sceneone::loadseats()
{
    QPoint position[]=
    {
        QPoint(330,380),//LB 3
        QPoint(255,380),//LB 2
        QPoint(180,380),//LB 1
        QPoint(225,530),//B
        QPoint(280,270),//M 1
        QPoint(355,270),//M 2
        QPoint(430,270),//M 3
        QPoint(545,270),//RT
        QPoint(550,410),//RB
        QPoint(237,158)//TL
    };
    int len = sizeof(position)/sizeof(position[0]);//统计个数？
    for(int i=0; i<len ;++i)
        seats.push_back(position[i]);//push back???
}
//click to buy tower(overload
//detect whether the click point is on a seat and whether there's enough place and money
void Sceneone::mousePressEvent(QMouseEvent *event)
{
    QPoint presspoint = event->pos();
    auto it = seats.begin();
    while(it !=seats.end())
    {
        if(canbuytower() && it->containpoint(presspoint)&& !it->showhastower())
        {
            it->sethastower(true);
            QPixmap fig(":/nurseone.jpg");
            tower * atower = new tower(it->centerPos(),this,fig);
            towerslist.push_back(atower);
            update();
            break;
        }
        ++it;
    }
}
//whether enough money(先设置程都可以，之后再算money
bool Sceneone::canbuytower() const
{
    return true;
}
//loadwaypoints
void Sceneone::loadwaypoints()
{
    WayPoint *point1 = new WayPoint(QPoint(187,600));
    waypoints.push_back(point1);

    WayPoint *point2 = new WayPoint(QPoint(187,470));
    waypoints.push_back(point2);
    point1->setnextpoint(point2);

    WayPoint *point3 = new WayPoint(QPoint(413,470));
    waypoints.push_back(point3);
    point2->setnextpoint(point3);

    WayPoint *point4 = new WayPoint(QPoint(413,355));
    waypoints.push_back(point4);
    point3->setnextpoint(point4);

    WayPoint *point5 = new WayPoint(QPoint(265,355));
    waypoints.push_back(point5);
    point4->setnextpoint(point5);

    WayPoint *point6 = new WayPoint(QPoint(265,245));
    waypoints.push_back(point6);
    point5->setnextpoint(point6);

    WayPoint *point7 = new WayPoint(QPoint(512,245));
    waypoints.push_back(point7);
    point6->setnextpoint(point7);

    WayPoint *point8 = new WayPoint(QPoint(512,355));
    waypoints.push_back(point8);
    point7->setnextpoint(point8);

    WayPoint *point9 = new WayPoint(QPoint(637,355));
    waypoints.push_back(point9);
    point8->setnextpoint(point9);

    WayPoint *point10 = new WayPoint(QPoint(637,225));
    waypoints.push_back(point10);
    point9->setnextpoint(point10);
}
//deteriorate the camp
void Sceneone::getCampHurt(int damage)
{
   qDebug()<<"sceneone getcamphurt";
   //audio sound
    //needtobefilled
    Hpbase-=damage;
    if(Hpbase<=0)
        gameover();
}
void Sceneone::gameover()
{
    qDebug()<<"sceneone gameover";
    if(!whetherlose)
    {
        whetherlose=true;
        //needtobefilled
        //endingscene of lost
    }
}

void Sceneone::removeVirus(virus *viru)
{
    Q_ASSERT(viru);//?
    viruses.removeOne(viru);
    viru->~virus();
    viru=nullptr;
    //delete viru;
    if(viruses.empty())
    {
        wavenow=wavenow+1;//波数+1
        //load next wave
        if(!loadwave())
        {
            //qDebug()<<"here";
            //if there's no more wave then you win
            whetherwin=true;
            //needtobecompleted
        }
    }
}
bool Sceneone::loadwave()
{
    //qDebug()<<"loadwave()";
   // qDebug("%d",wavenow);
    if(wavenow>=3)//canberevised
    {
        //qDebug()<<"false";
        return false;
    }
//    WayPoint *startpoint = waypoints.back();//??shima
    int virusInterval[]={0,5000,8000,10000,11000,12000};//canberevised
    QPixmap fig(":/virusone.png");//needtoberevised
    for(int i=0;i<6;i++)//6 viruses per wave canberevised
    {
        virus *viru = new virus(waypoints[0],this,fig);
        viruses.push_back(viru);
       QTimer::singleShot(virusInterval[i],viru,SLOT(activate()));//virus类必须继承于qobject，才能使用信号和槽
    }
    return true;

}

void Sceneone::removemed(Medicine *med)
{
    qDebug()<<"removemed";
    Q_ASSERT(med);//important
    medicines.removeOne(med);
    med->~Medicine();
    med=nullptr;
}
void Sceneone::addmed(Medicine *med)
{
    qDebug()<<"sceneone addmed";
    Q_ASSERT(med);//important
    medicines.push_back(med);
}
QList<virus *> Sceneone::viruslist() const
{
    //qDebug()<<"sceneone viruslist";

    return viruses;
}
Sceneone::~Sceneone()
{

}
