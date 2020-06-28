#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class virus;
class Scene;
class QTimer;
class tower:public QObject
{
    Q_OBJECT
public:
    tower(QPoint pos,Scene *scene, const QString pix=":/nurseone.jpg");
    void draw(QPainter *painter) const;
    ~tower();
    void startattack();//attackenemy
    void chooseenemy(virus* viru);//chooseenemyforattack
    void checkenemy();//checkenemyinrange

    void targetkilled();//targetkilled
    void losesight();//lostsightofenemy

    //??
    void upup();


public slots:
    void shoot();//shootweapon
protected:
    QPoint position;//center position
    int attackrange;
    int damage;
    int firerate;
    //const QPixmap figure;

    qreal rotation;
    virus* chosenenemy;
    QTimer* timer;
    Scene* game;

    bool whetherattacking;

    QString pix;

    static const QSize fixedsize;//the size of the tower
};

class towert:public tower
{
    Q_OBJECT
public:
    towert(QPoint pos,Scene *scene, const QString pix);
    ~towert();
    //QTimer* timer2;
    void upup();
public slots:
    void shoot2();

};


#endif // TOWER_H
