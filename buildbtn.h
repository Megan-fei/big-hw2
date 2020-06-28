#ifndef BUILDBTN_H
#define BUILDBTN_H

#include <QWidget>
#include <QPushButton>
#include <QAction>
class tower;
class towert;
class buildbtn : public QPushButton
{
    Q_OBJECT
public:
    buildbtn(QString pix);
    tower* temp1;
    towert* temp2;
    int type;


signals:
    void choosetowera();
    void choosetowerb();
    void deconstruct();
    void upgrade();

};

#endif // BUILDBTN_H
