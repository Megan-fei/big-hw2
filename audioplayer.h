#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
class QMediaPlayer;
enum Soundtype
{
    placetowersound,
    loselifesound,
    shootsound,
    killvirussound

};

class audioplayer : public QObject
{
public:
    explicit audioplayer(QObject *parent = nullptr);

    //void startbgm();
    //void playsound(Soundtype type);
signals:

public slots:
private:
    QMediaPlayer *bgmplayer;//only used for bgm
};

#endif // AUDIOPLAYER_H
