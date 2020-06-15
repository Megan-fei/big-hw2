#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class virus;
class Sceneone;
class QTimer;
class tower:QObject
{
    Q_OBJECT
public:
    tower(QPoint pos,Sceneone *scene, const QPixmap &fig=QPixmap(":/nurseone.jpg"));
    void draw(QPainter *painter) const;
    ~tower();
    void startattack();//attackenemy
    void chooseenemy(virus* viru);//chooseenemyforattack
    void checkenemy();//checkenemyinrange

    void targetkilled();//targetkilled
    void losesight();//lostsightofenemy

    //??


public slots:
    void shoot();//shootweapon
private:
    QPoint position;//center position
    int attackrange;
    int damage;
    int firerate;
    const QPixmap figure;

    qreal rotation;
    virus* chosenenemy;
    QTimer* timer;
    Sceneone* game;

    bool whetherattacking;

    static const QSize fixedsize;//the size of the tower
};

#endif // TOWER_H
