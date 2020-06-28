#include "virus.h"
#include "utility.h"
#include "sceneone.h"
#include <QDebug>
#include <ctime>
#include <QMediaPlayer>
#include <QTimer>
//construct function
const QSize virus::fixedsize(30,41);//mayberevised

virus::virus(WayPoint *startPoint,Scene *game,const QPixmap &fig) : QObject(0),position(startPoint->pos()),
    figure(fig),game(game),goalpoint(startPoint->nextwaypoint())//??QObject(0)?
{
    Hplife=300.0;//*canberevised
    Hpnow=300.0;//*canberevised
    speed=2;//*canberevised
    rotation=0.0;
    killedaward=400;
    basicaward=200;
    bonusaward=200;

    //active?
}
//draw the viurs and healthbar
void virus::draw(QPainter *painter)
{
    //qDebug()<<"draw";
    if(!active)
        return;
    //healthbar
    static const int  healthbarWidth=40;
    painter->save();
    QPoint huansuan1(-healthbarWidth/2,-fixedsize.height()/2-3);//tiaozheng!!
    QPoint healthbarPos=position+huansuan1;
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthbarBackrect(healthbarPos,QSize(healthbarWidth,2));
    painter->drawRect(healthbarBackrect);
    painter->setBrush(Qt::green);
    QRect healthbarRect(healthbarPos,QSize(double(Hpnow/Hplife)*healthbarWidth,2));
    painter->drawRect(healthbarRect);
    //virus
    static const QPoint huansuan2(-fixedsize.width()/2,-fixedsize.height()/2);
    painter->translate(position);
    painter->rotate(rotation);
    painter->drawPixmap(huansuan2,figure);
    painter->restore();

}
//move
void virus::move()
{
   //qDebug()<<"move";
    if(!active)
    {
        return;
        qDebug()<<"not actice";
    }
    //at a waypoint
    if(collisionWithTurnpoint(position,1,goalpoint->pos(),1))
    {
        //qDebug()<<"^collided";
        //not reached final base
        if(goalpoint->nextwaypoint())
        {
            position=goalpoint->pos();
            this->goalpoint=goalpoint->nextwaypoint();
        }
        //reached final base
        else
        {
            game->getCampHurt(2);//deteriorate the camp
            game->removeVirus(this);//??????
        }
    }
    //on the way to waypoint
    QPoint targetpoint=goalpoint->pos();
    //未来修改这个可以添加移动状态，加减速等等
    double movespeed=speed;
    QVector2D normalized(targetpoint-position);
    normalized.normalize();
    position=position+normalized.toPoint() * movespeed;
    rotation=qRadiansToDegrees(qAtan2(normalized.y(),normalized.x()))+90;
    //后面几行？？？？？
}
//destruct function
virus::~virus()
{
    attackers.clear();
    //goalpoint=NULL;
    //game=NULL;
}

//activate the virus
void virus::activate()
{
    active = true;
}
//*?
void virus::getattacked(tower* towe)
{
    //qDebug()<<"virus getattacked";
    attackers.push_back(towe);
}
void virus::gotlostsight(tower *towe)
{
    //qDebug()<<"virus gotlostsight";
    attackers.removeOne(towe);
}
void virus::gethurt(int damage)
{
    //qDebug()<<"virus gethurt";
    Hpnow-=damage;
    qsrand(time(NULL));
    int bonus=basicaward+qrand()%bonusaward;
   // qDebug("%d ",bonus);
    game->award(bonus);
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sound/hurt.mp3"));
    player->setVolume(50);
    player->play();
    if(Hpnow<=0)
    {
        this->getremoved();
        game->award(killedaward);
    }
}
void virus::getremoved()
{
    //qDebug()<<"virus getremoved";
    if(attackers.empty())
        return;
    foreach(tower* attacker,attackers)
        attacker->targetkilled();
    game->removeVirus(this);
}
void virus::slowdown()
{
    this->speed=0.85*speed;
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(recoverspeed()));//update the viruses every 40ms
    timer->start(13000);
}
void virus::recoverspeed()
{
    this->speed=speed/0.85;
}
QPoint virus::pos() const
{
    //qDebug()<<"virus pos";
    return position;
}



virust::virust(WayPoint *startPoint,Scene *game,const QPixmap &fig):virus(startPoint,game,QPixmap(":/virusflu.png"))
{
    Hplife=375.0;//*canberevised
    Hpnow=375.0;//*canberevised
    speed=3;
    killedaward=450;
    bonusaward=200;
    basicaward=100;
}
virust::~virust()
{}

virusth::virusth(WayPoint *startPoint,Scene *game,const QPixmap &fig):virus(startPoint,game,QPixmap(":/viruspoi.png"))
{
    Hplife=900.0;//*canberevised
    Hpnow=900.0;//*canberevised
    speed=2.5;
    killedaward=600;
    bonusaward=75;
    basicaward=150;
}
virusth::~virusth()
{}

virusf::virusf(WayPoint *startPoint,Scene *game,const QPixmap &fig):virus(startPoint,game,QPixmap(":/virusboss.png"))
{
    Hplife=4500.0;//*canberevised
    Hpnow=4500.0;//*canberevised
    speed=1.5;
    killedaward=5000;
    bonusaward=100;
    basicaward=20;
}
virusf::~virusf()
{}
