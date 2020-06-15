#include "seat.h"
#include <QPoint>
#include <QPixmap>
#include <QSize>
#include <QPainter>

//the size
const QSize seat::fixedsize(64,64);//?????!!!revise!!!
//construct function
seat::seat(QPoint pos, const QPixmap &fig)//construct function. 1 position,2 figure of the seat
{
    position=pos;
    this->hastower=false;
    figure=fig;
}
//set the seat has tower
void seat::sethastower(bool hasto)
{
    this->hastower=hasto;
}
//show whether there's a tower
bool seat::showhastower() const
{
    return hastower;
}
//show the center position of the base?
const QPoint seat::centerPos() const
{
    QPoint huansuan(fixedsize.width()/2,fixedsize.height()/2);
    return position+huansuan;
}
//whether the clicked point is in the area?
bool seat::containpoint(const QPoint &pos) const
{
    bool ifxin = position.x()<=pos.x() && pos.x()<=position.x()+fixedsize.width();
    bool ifyin = position.y()<=pos.y() && pos.y()<=position.y()+fixedsize.height();
    return ifxin && ifyin;
}
//draw the seat
void seat::draw(QPainter *painter) const
{
    painter->drawPixmap(position.x(),position.y(),figure);
}

