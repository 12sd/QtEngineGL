#include "sound.h"
#include <QDebug>

Sound::Sound(QObject *parent):QObject(parent)
{
    this->repeatEnable=false;
    this->milisecRepeat=0;
    this->connect(&this->sound,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(statusChange(QMediaPlayer::MediaStatus)));
    this->connect(&this->sound,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(stateChange(QMediaPlayer::State)));
    this->connect(this,SIGNAL(finishSound()),this,SLOT(finished()));
}

void Sound::load(QString name)
{
    this->sound.setMedia(QMediaContent(name));
}

void Sound::play()
{
    this->sound.play();
}

void Sound::pause()
{
    this->sound.pause();
}

void Sound::stop()
{
    this->sound.stop();
}

bool Sound::isPlay()
{
    if(this->sound.state()==QMediaPlayer::PlayingState)
        return true;
    return false;
}

bool Sound::isPause()
{
    if(this->sound.state()==QMediaPlayer::PausedState)
        return true;
    return false;
}

bool Sound::isRepeat()
{
    return this->repeatEnable;
}

bool Sound::isStop()
{
    if(this->sound.state()==QMediaPlayer::StoppedState)
        return true;
    return false;
}

void Sound::setVolume(int volume)
{
    this->sound.setVolume(volume);
}

void Sound::setRepeat(bool enable, int milisec)
{
    this->repeatEnable=enable;
    this->milisecRepeat=milisec;
}

void Sound::statusChange(QMediaPlayer::MediaStatus status)
{
    if(status==QMediaPlayer::EndOfMedia)
        emit this->finishSound();
}

void Sound::stateChange(QMediaPlayer::State state)
{
    switch(state)
    {
        case QMediaPlayer::PlayingState:{
            emit this->playSound();
            break;
        }
        case QMediaPlayer::PausedState:{
            emit this->pauseSound();
            break;
        }
        case QMediaPlayer::StoppedState:{
            emit this->stopSound();
            break;
        }
        default: break;
    }

}

void Sound::finished()
{
    if(this->repeatEnable)
        QTimer::singleShot(this->milisecRepeat,this,SLOT(repeated()));
}

void Sound::repeated()
{
    this->play();
}
