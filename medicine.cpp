#include "medicine.h"
#include "virus.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>
const QSize Medicine::fixedsize(30,30);//mayberevised

Medicine::Medicine(QPoint start, QPoint desti,int damage,virus* viru,Scene *game,const QPixmap &fig) :
    QObject(0),startposition(start),destiposition(desti),figure(fig)
{
    this->damage=damage;
    target=viru;
    this->game=game;
}
void Medicine::move()
{
    static const int duration=100;//*mayberevised
    QPropertyAnimation* animation = new QPropertyAnimation(this,"position");
    animation->setDuration(duration);
    animation->setStartValue(startposition);
    animation->setEndValue(destiposition);
    connect(animation,SIGNAL(finished()),this,SLOT(hittarget()));
    animation->start();
}
void Medicine::hittarget()
{
    if(game->viruslist().indexOf(target)!=-1)
        target->gethurt(damage);
    game->removemed(this);
}
Medicine::~Medicine()
{}
void Medicine::setposition(QPoint pos)
{
    position.setX(pos.rx());
    position.setY(pos.ry());
}
QPoint Medicine::pos()
{
    return position;
}
void Medicine::draw(QPainter *painter) const
{
    painter->drawPixmap(position,figure);
}

Medicinet::Medicinet(QPoint start, QPoint desti,int damage,virus* viru,Scene *game,const QPixmap &fig) :Medicine(start,desti,damage,viru,game,fig)
{
    qDebug()<<"medi2";
}
Medicinet::~Medicinet()
{}
void Medicinet::hittarget2()
{
    if(game->viruslist().indexOf(target)!=-1)
    {
        target->gethurt(damage);
        target->slowdown();
    }
    game->removemed(this);
}
void Medicinet::move()
{
    static const int duration=100;//*mayberevised
    QPropertyAnimation* animation = new QPropertyAnimation(this,"position");
    animation->setDuration(duration);
    animation->setStartValue(startposition);
    animation->setEndValue(destiposition);
    connect(animation,SIGNAL(finished()),this,SLOT(hittarget2()));
    animation->start();
}
