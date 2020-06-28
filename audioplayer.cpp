#include "audioplayer.h"
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>

//static const QString curdir=QDir::currentPath()+"/";
audioplayer::audioplayer(QObject *parent) : QObject(parent),bgmplayer(NULL)
{
    //set bgm

    //QUrl bgmUrl=QUrl::fromLocalFile(curdir+"music/bgm.mp3");
    //qDebug()<<"const";
    /*if(QFile::exists(bgmUrl.toLocalFile()))
    {
        qDebug()<<"sound";
        bgmplayer= new QMediaPlayer(this);
        QMediaPlaylist *bgmlist=new QMediaPlaylist();
        QMediaContent media(bgmUrl);
        bgmlist->addMedia(media);
        bgmlist->setCurrentIndex(0);
        //循环播放
        bgmlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        bgmplayer->setPlaylist(bgmlist);
    }*/
    QMediaPlayer *player = new QMediaPlayer();
    bgmplayer=player;
    player->setMedia(QUrl("qrc:/sound/bgm.mp3"));
    player->setVolume(100);
    player->play();
}
/*void audioplayer::startbgm()
{
    qDebug()<<"startbgm";
    if(bgmplayer)
    {
        qDebug()<<"play";
        bgmplayer->play();
    }
}*/
/*void audioplayer::playsound(Soundtype type)
{
    static const QUrl mediasUrls[] =
        {
            QUrl::fromLocalFile(curdir + "place.wav"),
            QUrl::fromLocalFile(curdir + "hurt.mp3"),
            QUrl::fromLocalFile(curdir + "shoot.mp3"),
            QUrl::fromLocalFile(curdir + "killed.wav")
        };
        static QMediaPlayer player;
        if (QFile::exists(mediasUrls[type].toLocalFile()))
        {
            player.setMedia(mediasUrls[type]);
            player.play();
        }
}*/
