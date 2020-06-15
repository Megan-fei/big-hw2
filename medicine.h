#ifndef MEDICINE_H
#define MEDICINE_H

#include <QObject>
#include <QPainter>
#include "sceneone.h"
#include "virus.h"
class virus;
class Sceneone;
class Medicine : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QPoint position READ pos WRITE setposition);
    Medicine(QPoint start, QPoint desti,int damage,virus* viru,Sceneone *game);
    ~Medicine();
    void draw(QPainter* painter) const;
    void move();
    void setposition(QPoint pos);
    QPoint pos();

private:
    const QPoint startposition;
    const QPoint destiposition;
    QPoint position;
    const QPixmap figure;
    Sceneone* game;
    int damage;
    virus* target;

    static const QSize fixedsize;
signals:

public slots:
    void hittarget();
};

#endif // MEDICINE_H
