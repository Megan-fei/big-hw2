#include "mainwindow.h"
#include "waypoint.h"
#include "virus.h"
#include "medicine.h"
//#include "audioplayer.h"§
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include <QMediaPlayer>
#include "buildbtn.h"
//construct function
static const int towerprice=3200;
Scene::Scene(QWidget *parent):QMainWindow(parent)
{
}
Scene::~Scene()
{}
Sceneone::Sceneone(QWidget *parent) : Scene(parent)
{
    this->setFixedSize(800,600);
    this->loadseats();
    this->loadwaypoints();
    this->loadwave();

   // virus *viru1 = new virus(waypoints[0],this,QPixmap(":/nurseone.jpg"));
   // viruses.push_back(viru1);
    myaudioplayer=new audioplayer(this);
    //myaudioplayer->startbgm();
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updatemap()));//update the viruses every 40ms
    timer->start(40);
}
tower* Scene::build(QPoint position)
{
    auto it = seats.begin();
    while(it !=seats.end())
    {
        if(showgold()>=4000 && it->containpoint(position)&& !it->showhastower())
        {
            QMediaPlayer * player = new QMediaPlayer;
            player->setMedia(QUrl("qrc:/sound/place.wav"));
            player->setVolume(80);
            player->play();
            playergold-=4000;
            it->sethastower(true);
            //QPixmap fig(":/docone.png");
            tower * atower = new tower(it->centerPos(),this,":/docone.png");
            towerslist.push_back(atower);
            update();
            return atower;
            break;
        }
        ++it;
    }
}
void Scene::removetower(tower *towe,QPoint position)
{
    Q_ASSERT(towe);
    towerslist.removeOne(towe);
    towe->~tower();
    towe=nullptr;
    auto it = seats.begin();
    while(it !=seats.end())
    {
        if(it->containpoint(position)&& it->showhastower())
        {
            playergold+=towerprice/3;
            it->sethastower(false);
            break;
        }
        ++it;
    }
}
void Scene::removetowert(towert *towe,QPoint position)
{
    Q_ASSERT(towe);
    towerslist.removeOne(towe);
    towe->~towert();
    towe=nullptr;
    auto it = seats.begin();
    while(it !=seats.end())
    {
        if(it->containpoint(position)&& it->showhastower())
        {
            playergold+=towerprice/3;
            it->sethastower(false);
            break;
        }
        ++it;
    }
} 
towert* Scene::buildt(QPoint position)
{
    auto it = seats.begin();
    while(it !=seats.end())
    {
        if(canbuytower() && it->containpoint(position)&& !it->showhastower())
        {
            QMediaPlayer * player = new QMediaPlayer;
            player->setMedia(QUrl("qrc:/sound/place.wav"));
            player->setVolume(80);
            player->play();
            playergold-=towerprice;
            it->sethastower(true);
            towert * atower = new towert(it->centerPos(),this,":/nurseone.jpg");
            towerslist.push_back(atower);
            update();
            return atower;
            break;
        }
        ++it;
    }
}
//paint the screen
void Sceneone::paintEvent(QPaintEvent *event)
{
    //if the game has ended
    //*canberevised
    //think again
    //qDebug()<<"!!";
    if(whetherwin||whetherlose)
    {
        qDebug("%d",whetherlose);
        qDebug("%d",whetherwin);
        QString text = whetherlose?"lose":"win";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(),Qt::AlignCenter,text);
        return;
    }
    QPixmap cachepic(":/bgpic.jpg");
        QPainter cachepainter(&cachepic);
        //painter.drawPixmap(0,0,this->width(),this->height(),background);
        int len = 10 ;//统计个数
        for(int i=0; i<len ;++i)
        {
            seats[i].draw(&cachepainter);
        }
        foreach(tower *towe, towerslist)
        {
            towe->draw(&cachepainter);
        }
        foreach(WayPoint *wp,waypoints)
        {
            wp->draw(&cachepainter);
        }
        foreach(virus *viru, viruses)
        {
            viru->draw(&cachepainter);
        }
        foreach(Medicine *med,medicines)
        {
            med->draw(&cachepainter);
        }
        drawbgrect(&cachepainter);
        drawgold(&cachepainter);
        drawhp(&cachepainter);
        drawwave(&cachepainter);

        QPainter painter(this);
        painter.drawPixmap(0,0,cachepic);


}

//update function
void Scene::updatemap()
{
    //qDebug()<<"updatemap";
    foreach(virus *viru, viruses)
        viru->move();
    foreach(tower *towe, towerslist)
        towe->checkenemy();
    update();//？？？？？？？
}
//load seats
void Sceneone::loadseats()
{
    QPoint position[]=
    {
        QPoint(330,380),//LB 3
        QPoint(255,380),//LB 2
        QPoint(180,380),//LB 1
        QPoint(225,530),//B
        QPoint(280,270),//M 1
        QPoint(355,270),//M 2
        QPoint(430,270),//M 3
        QPoint(545,270),//RT
        QPoint(550,410),//RB
        QPoint(237,158)//TL
    };
    int len = sizeof(position)/sizeof(position[0]);//统计个数？
    for(int i=0; i<len ;++i)
        seats.push_back(position[i]);//push back???
}

//click to buy tower(overload
//detect whether the click point is on a seat and whether there's enough place and money
/*
void Sceneone::mousePressEvent(QMouseEvent *event)
{
    QPoint presspoint = event->pos();
    auto it = seats.begin();
    while(it !=seats.end())
    {
        if(canbuytower() && it->containpoint(presspoint)&& !it->showhastower())
        {
            QMediaPlayer * player = new QMediaPlayer;
            player->setMedia(QUrl("qrc:/sound/place.wav"));
            player->setVolume(80);
            player->play();
            playergold-=towerprice;
            it->sethastower(true);
            QPixmap fig(":/nurseone.jpg");
            tower * atower = new tower(it->centerPos(),this,fig);
            towerslist.push_back(atower);
            update();
            break;
        }
        ++it;
    }
}*/
//whether enough gold
bool Scene::canbuytower() const
{
    if(playergold>=towerprice)
        return true;
    else return false;
}
//loadwaypoints and buttons
void Sceneone::loadwaypoints()
{
    WayPoint *point1 = new WayPoint(QPoint(187,600));
    waypoints.push_back(point1);

    WayPoint *point2 = new WayPoint(QPoint(187,470));
    waypoints.push_back(point2);
    point1->setnextpoint(point2);

    WayPoint *point3 = new WayPoint(QPoint(413,470));
    waypoints.push_back(point3);
    point2->setnextpoint(point3);

    WayPoint *point4 = new WayPoint(QPoint(413,355));
    waypoints.push_back(point4);
    point3->setnextpoint(point4);

    WayPoint *point5 = new WayPoint(QPoint(265,355));
    waypoints.push_back(point5);
    point4->setnextpoint(point5);

    WayPoint *point6 = new WayPoint(QPoint(265,245));
    waypoints.push_back(point6);
    point5->setnextpoint(point6);

    WayPoint *point7 = new WayPoint(QPoint(512,245));
    waypoints.push_back(point7);
    point6->setnextpoint(point7);

    WayPoint *point8 = new WayPoint(QPoint(512,355));
    waypoints.push_back(point8);
    point7->setnextpoint(point8);

    WayPoint *point9 = new WayPoint(QPoint(637,355));
    waypoints.push_back(point9);
    point8->setnextpoint(point9);

    WayPoint *point10 = new WayPoint(QPoint(637,225));
    waypoints.push_back(point10);
    point9->setnextpoint(point10);

    QPoint position[]=
    {
        QPoint(330,380),//LB 3
        QPoint(255,380),//LB 2
        QPoint(180,380),//LB 1
        QPoint(225,530),//B
        QPoint(280,270),//M 1
        QPoint(355,270),//M 2
        QPoint(430,270),//M 3
        QPoint(545,270),//RT
        QPoint(550,410),//RB
        QPoint(237,158)//TL
    };
    for(int i=0;i<10;i++)
    {
        buildbtn *btn = new buildbtn(":/btn.jpg");
        btn->setParent(this);
        btn->move(position[i].x(),position[i].y());
        connect(btn,&buildbtn::choosetowera,this,[=](){btn->temp1=build(position[i]);btn->type=1;});
        connect(btn,&buildbtn::choosetowerb,this,[=](){btn->temp2=buildt(position[i]);btn->type=2;});
        connect(btn,&buildbtn::deconstruct,this,[=](){
            if(btn->type==1)
                removetower(btn->temp1,position[i]);
            else if(btn->type==2)
                removetowert(btn->temp2,position[i]);
        });
        connect(btn,&buildbtn::upgrade,this,[=](){
            if(btn->type==1)
                btn->temp1->upup();
            else if(btn->type==2)
                btn->temp2->upup();
        });
    }
}
//deteriorate the camp
void Scene::getCampHurt(int damage)
{
   //qDebug()<<"sceneone getcamphurt";
   //audio sound
    //needtobefilled
    Hpbase-=damage;
    if(Hpbase<=0)
        gameover();
}
void Scene::gameover()
{
    //qDebug()<<"sceneone gameover";
    if(!whetherlose)
    {
        whetherlose=true;
        //needtobefilled
        //endingscene of lost
    }
}

void Scene::removeVirus(virus *viru)
{
    Q_ASSERT(viru);//?
    viruses.removeOne(viru);
    viru->~virus();
    viru=nullptr;
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sound/killed.wav"));
    player->setVolume(80);
    player->play();
    //delete viru;
    if(viruses.empty())
    {
        wavenow=wavenow+1;//波数+1
        //load next wave
        if(!loadwave())
        {
            //qDebug()<<"here";
            //if there's no more wave then you win
            whetherwin=true;
            //needtobecompleted
        }
    }
}
bool Sceneone::loadwave()
{
    //qDebug()<<"loadwave()";
   // qDebug("%d",wavenow);
    if(wavenow>=6)//canberevised
    {
        //qDebug()<<"false";
        return false;
    }
//    WayPoint *startpoint = waypoints.back();//??shima
    QPixmap fig1(":/virusone.png");//needtoberevised
    int virusinterval[6][12][2]={
        {{0,1},{5,1},{8,1},{10,1},{11,1},{12,2},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},//[0][][]
        {{0,1},{5,1},{8,1},{9,2},{10,1},{11,1},{12,1},{13,3},{0,0}},//[1][][]
        {{0,1},{5,1},{8,1},{9,2},{10,2},{11,1},{12,3},{13,3},{0,0}},//[2][][]
        {{0,1},{2,1},{5,2},{6,2},{8,3},{9,2},{10,2},{11,3},{12,3},{13,3},{14,4},{0,0}},//[3][][]
        {{0,2},{2,2},{4,2},{10,2},{11,3},{12,3},{13,3},{17,1},{18,2},{19,1},{0,0},{0,0}},//[4][][]
        {{0,1},{1,1},{2,3},{4,3},{5,2},{6,2},{7,3},{9,3},{11,2},{12,3},{13,4},{0,0}}//[5][][]
    };
    int j=0;
    for(int i=0;i<12;i++)
    {
        switch(virusinterval[wavenow][i][1])
        {
        case 0:
        {
            j++;
            break;
        }
        case 1:
        {
            virus *viru=new virus(waypoints[0],this,fig1);
            viruses.push_back(viru);
            QTimer::singleShot(1000*virusinterval[wavenow][i][0],viru,SLOT(activate()));
            break;
        }
        case 2:
        {
            virust *viru=new virust(waypoints[0],this,fig1);
            viruses.push_back(viru);
            QTimer::singleShot(1000*virusinterval[wavenow][i][0],viru,SLOT(activate()));
            break;
        }
        case 3:
        {
            virusth *viru=new virusth(waypoints[0],this,fig1);
            viruses.push_back(viru);
            QTimer::singleShot(1000*virusinterval[wavenow][i][0],viru,SLOT(activate()));
            break;
        }
        case 4:
        {
            virusf *viru=new virusf(waypoints[0],this,fig1);
            viruses.push_back(viru);
            QTimer::singleShot(1000*virusinterval[wavenow][i][0],viru,SLOT(activate()));
            break;
        }
        }
        if(j>0) break;
    }
    return true;
}

void Scene::removemed(Medicine *med)
{
    //qDebug()<<"removemed";
    Q_ASSERT(med);//important
    medicines.removeOne(med);
    med->~Medicine();
    med=nullptr;
}
void Scene::addmed(Medicine *med)
{
    //qDebug()<<"sceneone addmed";
    Q_ASSERT(med);//important
    medicines.push_back(med);
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sound/shoot.mp3"));
    player->setVolume(50);
    player->play();
}
QList<virus *> Scene::viruslist() const
{
    //qDebug()<<"sceneone viruslist";

    return viruses;
}
Sceneone::~Sceneone()
{

}
//related to game
//award money when virus is hurt or killed
void Scene::award(int money)
{
    playergold+=money;
    update();
}
//related to screen
void Scene::drawwave(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue));
    painter->drawText(QRect(380,5,100,25),QString("Wave:%1").arg(wavenow+1));
}
void Scene::drawhp(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue));
    painter->drawText(QRect(30,5,100,25),QString("Hp:%1").arg(Hpbase));
}
void Scene::drawgold(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue));
    painter->drawText(QRect(190,5,200,25),QString("My Gold:%1").arg(playergold));
}
void Scene::drawbgrect(QPainter *painter)
{
    //static const int width=25;
    QPoint bgrectpos(20,5);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    QRect bgrect(bgrectpos,QSize(425,20));
    painter->drawRect(bgrect);
}
int Scene::showgold()
{
    return playergold;
}
void Scene::spendmoney(int price)
{
    playergold-=price;
}


Scenetwo::Scenetwo(QWidget *parent) : Scene(parent)
{
    //qDebug()<<"two";
    this->setFixedSize(800,600);
    this->loadseats();
    this->loadwaypoints();
    this->loadwave();
    myaudioplayer=new audioplayer(this);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updatemap()));//update the viruses every 40ms
    timer->start(40);
    playergold=20000;
}
void Scenetwo::paintEvent(QPaintEvent *event)
{
    //if the game has ended
    //*canberevised
    //think again
    //qDebug()<<"!!";
    if(whetherwin||whetherlose)
    {
        qDebug("%d",whetherlose);
        qDebug("%d",whetherwin);
        QString text = whetherlose?"lose":"win";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(),Qt::AlignCenter,text);
        return;
    }
    QPixmap cachepic(":/scene2.jpg");
        QPainter cachepainter(&cachepic);
        //painter.drawPixmap(0,0,this->width(),this->height(),background);
        int len = 11 ;//统计个数
        for(int i=0; i<len ;++i)
        {
            seats[i].draw(&cachepainter);
        }
        foreach(tower *towe, towerslist)
        {
            towe->draw(&cachepainter);
        }
        foreach(WayPoint *wp,waypoints)
        {
            wp->draw(&cachepainter);
        }
        foreach(virus *viru, viruses)
        {
            viru->draw(&cachepainter);
        }
        foreach(Medicine *med,medicines)
        {
            med->draw(&cachepainter);
        }
        drawbgrect(&cachepainter);
        drawgold(&cachepainter);
        drawhp(&cachepainter);
        drawwave(&cachepainter);

        QPainter painter(this);
        painter.drawPixmap(0,0,cachepic);
}
Scenetwo::~Scenetwo()
{

}
void Scenetwo::loadseats()
{
    QPoint position[]=
    {
        QPoint(440,490),//LB 3
        QPoint(120,355),//LB 2
        QPoint(195,355),//LB 1
        QPoint(270,355),//B
        QPoint(175,265),//M 1
        QPoint(250,265),//M 2
        QPoint(390,265),//M 3
        QPoint(710,115),//RT
        QPoint(620,115),//RB
        QPoint(190,115),//TL
        QPoint(340,115)
    };
    int len = sizeof(position)/sizeof(position[0]);//统计个数？
    for(int i=0; i<len ;++i)
        seats.push_back(position[i]);//push back???
}
void Scenetwo::loadwaypoints()
{
    WayPoint *point1 = new WayPoint(QPoint(799,90));
    waypoints.push_back(point1);

    WayPoint *point2 = new WayPoint(QPoint(90,90));
    waypoints.push_back(point2);
    point1->setnextpoint(point2);

    WayPoint *point3 = new WayPoint(QPoint(90,240));
    waypoints.push_back(point3);
    point2->setnextpoint(point3);

    WayPoint *point4 = new WayPoint(QPoint(799,465));
    waypoints.push_back(point4);


    WayPoint *point5 = new WayPoint(QPoint(490,465));
    waypoints.push_back(point5);
    point4->setnextpoint(point5);

    WayPoint *point6 = new WayPoint(QPoint(490,240));
    waypoints.push_back(point6);
    point5->setnextpoint(point6);
    point6->setnextpoint(point3);

    WayPoint *point7 = new WayPoint(QPoint(415,600));
    waypoints.push_back(point7);


    WayPoint *point8 = new WayPoint(QPoint(415,430));
    waypoints.push_back(point8);
    point7->setnextpoint(point8);

    WayPoint *point9 = new WayPoint(QPoint(90,430));
    waypoints.push_back(point9);
    point8->setnextpoint(point9);
    point9->setnextpoint(point3);

    QPoint position[]=
    {
        QPoint(440,490),//LB 3
        QPoint(120,355),//LB 2
        QPoint(195,355),//LB 1
        QPoint(270,355),//B
        QPoint(175,265),//M 1
        QPoint(250,265),//M 2
        QPoint(390,265),//M 3
        QPoint(710,115),//RT
        QPoint(620,115),//RB
        QPoint(190,115),//TL
        QPoint(340,115)
    };
    for(int i=0;i<11;i++)
    {
        buildbtn *btn = new buildbtn(":/btn.jpg");
        btn->setParent(this);
        btn->move(position[i].x(),position[i].y());
        connect(btn,&buildbtn::choosetowera,this,[=](){btn->temp1=build(position[i]);btn->type=1;});
        connect(btn,&buildbtn::choosetowerb,this,[=](){btn->temp2=buildt(position[i]);btn->type=2;});
        connect(btn,&buildbtn::deconstruct,this,[=](){
            if(btn->type==1)
                removetower(btn->temp1,position[i]);
            else if(btn->type==2)
                removetowert(btn->temp2,position[i]);
        });
        connect(btn,&buildbtn::upgrade,this,[=](){
            if(btn->type==1)
                btn->temp1->upup();
            else if(btn->type==2)
                btn->temp2->upup();
        });
    }
}
bool Scenetwo::loadwave()
{
    if(wavenow>=6)//canberevised
    {
        return false;
    }
    QPixmap fig1(":/virusone.png");//needtoberevised
    int virusinterval[6][12][2]={
        {{0,1},{5,1},{8,1},{10,1},{11,1},{12,2},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},//[0][][]
        {{0,1},{5,1},{8,1},{9,2},{10,1},{11,1},{12,1},{13,3},{0,0}},//[1][][]
        {{0,1},{5,1},{8,1},{9,2},{10,2},{11,1},{12,3},{13,3},{0,0}},//[2][][]
        {{0,1},{2,1},{5,2},{6,2},{8,3},{9,2},{10,2},{11,3},{12,3},{13,3},{14,4},{0,0}},//[3][][]
        {{0,2},{2,2},{4,2},{10,2},{11,3},{12,3},{13,3},{17,1},{18,2},{19,1},{0,0},{0,0}},//[4][][]
        {{0,1},{1,1},{2,3},{4,3},{5,2},{6,2},{7,3},{9,3},{11,2},{12,3},{13,4},{0,0}}//[5][][]
    };
    int j=0;
    int place[6][12]={
        {1,1,1,1,4,1,0},{4,4,4,1,7,7,7,1},{7,7,1,4,4,4,4,4},{7,7,7,4,7,1,7,7,1,7,7},
        {4,4,4,4,4,1,4,1,4,1},{1,4,7,1,4,7,1,4,7,1,4,7}
    };
    for(int i=0;i<12;i++)
    {
        switch(virusinterval[wavenow][i][1])
        {
        case 0:
        {
            j++;
            break;
        }
        case 1:
        {
            virus *viru=new virus(waypoints[place[wavenow][i]-1],this,fig1);
            viruses.push_back(viru);
            QTimer::singleShot(1000*virusinterval[wavenow][i][0],viru,SLOT(activate()));
            break;
        }
        case 2:
        {
            virust *viru=new virust(waypoints[place[wavenow][i]-1],this,fig1);
            viruses.push_back(viru);
            QTimer::singleShot(1000*virusinterval[wavenow][i][0],viru,SLOT(activate()));
            break;
        }
        case 3:
        {
            virusth *viru=new virusth(waypoints[place[wavenow][i]-1],this,fig1);
            viruses.push_back(viru);
            QTimer::singleShot(1000*virusinterval[wavenow][i][0],viru,SLOT(activate()));
            break;
        }
        case 4:
        {
            virusf *viru=new virusf(waypoints[place[wavenow][i]-1],this,fig1);
            viruses.push_back(viru);
            QTimer::singleShot(1000*virusinterval[wavenow][i][0],viru,SLOT(activate()));
            break;
        }
        }
        if(j>0) break;
    }
    return true;
}
