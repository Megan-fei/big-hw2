#include "buildbtn.h"
#include <QPixmap>
buildbtn::buildbtn(QString pix) : QPushButton(0),temp1(nullptr),temp2(nullptr)
{
    QPixmap pixmap(pix);
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    //call for doctor
    QAction *action1 = new QAction(this);
    action1->setText("call for doctor");
    this->addAction(action1);
    connect(action1,&QAction::triggered,this,[=](){
        choosetowera();
    });
    //call for nurse
    QAction *action2 = new QAction(this);
    action2->setText("call for nurse");
    this->addAction(action2);
    connect(action2,&QAction::triggered,this,[=](){
        choosetowerb();
    });
    //deconstruct the tower
    QAction *action3 = new QAction(this);
    action3->setText("treatments are done");
    this->addAction(action3);
    connect(action3,&QAction::triggered,this,[=](){
        deconstruct();
    });
    //upgrade the tower
    QAction *action4 = new QAction(this);
    action4->setText("need experts");
    this->addAction(action4);
    connect(action4,&QAction::triggered,this,[=](){
        upgrade();
    });
    type=0;
}
