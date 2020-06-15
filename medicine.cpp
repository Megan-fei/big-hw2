#include "medicine.h"
#include "virus.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>
const QSize Medicine::fixedsize(30,30);//mayberevised

Medicine::Medicine(QPoint start, QPoint desti,int damage,virus* viru,Sceneone *game) :
    QObject(0),startposition(start),destiposition(desti),figure(QPixmap(":/medone.png"))
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
