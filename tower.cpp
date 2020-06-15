#include "tower.h"
#include "virus.h"
#include "medicine.h"
#include "mainwindow.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize tower::fixedsize(49,64);//????????????revise!!!
//construct function
tower::tower(QPoint pos,Sceneone *game, const QPixmap &fig):chosenenemy(NULL),figure(fig),game(game)
{
    position=pos;
    attackrange=100;//@@@@@need to be set
    damage=100;//@@@@@need to be set
    firerate=1000;//@@@@@@need to be set
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(shoot()));
}
//destruct function
tower::~tower()
{
    delete timer;
    timer=NULL;
}
//drawing function
void tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::white);
    //draw attack circle
    painter->drawEllipse(position,attackrange,attackrange);
    //draw the picture of the tower
    static const QPoint huansuan(-fixedsize.width()/2,-fixedsize.height()/2);//huansuan zuobiao
//    painter.drawPixmap(huansuan+position,figure);
    painter->translate(position);
    painter->drawPixmap(huansuan,figure);
    painter->restore();
}
//
void tower::startattack()
{
    qDebug()<<"startattack";
    timer->start(firerate);
}
void tower::chooseenemy(virus *viru)
{
    //qDebug()<<"choose enemy";
    chosenenemy=viru;
    startattack();
    chosenenemy->getattacked(this);
}
void tower::shoot()
{
    qDebug()<<"tower shoot";
    Medicine *med = new Medicine(position,chosenenemy->pos(),damage,chosenenemy,game);
    med->move();
    game->addmed(med);
}
void tower::checkenemy()
{
   // qDebug()<<"tower checkenemy";
    //if have a target now
   if(chosenenemy)
   {
      // qDebug()<<"if";
       //turn the tower to the enemy
       QVector2D normalized(chosenenemy->pos() - this->position);
       normalized.normalize();
       rotation=qRadiansToDegrees(qAtan2(normalized.y(),normalized.x()))-90;
       //check whether out of range
       if(!collisionWithTurnpoint(position,attackrange,chosenenemy->pos(),1))
           losesight();
   }
   //if no target here
   else
   {
      // qDebug()<<"else";
       //QList<virus *> viruses = game->viruslist();
      // qDebug()<<"ready to choose";
       foreach(virus* viru,game->viruslist())
       {
          // qDebug()<<"choosing";
           if(collisionWithTurnpoint(this->position,this->attackrange,viru->pos(),1))
           {

               //if(!chosenenemy)
                chooseenemy(viru);
               break;

           }
       }
   }
}
void tower::targetkilled()
{
    qDebug()<<"targetkilled";
    if(chosenenemy)
        chosenenemy=NULL;
    timer->stop();
    rotation=0.0;
}
void tower::losesight()
{
    qDebug()<<"tower losesight";
    chosenenemy->gotlostsight(this);
    if(chosenenemy)
        chosenenemy=NULL;
    timer->stop();
    rotation=0.0;
}
