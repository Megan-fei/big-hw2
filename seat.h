#ifndef SEAT_H
#define SEAT_H

#include <QPoint>
#include <QPixmap>
#include <QSize>
#include <QPainter>

class seat
{
public:
    seat(QPoint pos, const QPixmap &fig=QPixmap(":/seat.jpg"));//construct function. 1 position,2 figure of the seat

    void sethastower(bool hasto=true);//set the seat has tower
    bool showhastower() const;//show whether there's a tower
    const QPoint centerPos() const;//show the position of the base?
    bool containpoint(const QPoint &pos) const;//whether the clicked point is in the area?
    void draw(QPainter *painter) const;

private:
    QPoint position;//position
    bool hastower;//whether there's a tower
    QPixmap figure;// picture

    static const QSize fixedsize;//the size of the seat
};

#endif // SEAT_H
