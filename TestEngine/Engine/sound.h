#ifndef SOUND_H
#define SOUND_H

#include <QMediaPlayer>
#include <QTimer>
#include <QObject>

class Sound:public QObject
{
    Q_OBJECT
public:
    Sound(QObject *parent=0);
    // Путь к звуковому файлу
    void load(QString name);
    // начать проигрование звукового файла
    void play();
    // приостоновить проигрование звукового файла
    void pause();
    // остановить проигрование звукового файла
    void stop();
    // задать уровень громкости звукового файла
    void setVolume(int volume);
    // задать повторение проигрования звукового файла через заданое количество милисекунд
    void setRepeat(bool enable=false,int milisec=0);
    // возвращает уровень громкости звукового файла
    int volume();
    // проиграл ли файл полностью
    bool isFinished();
    // проигровается ли файл в данное время
    bool isPlay();
    // остоновлено ли воспроизведение звукового файла
    bool isStop();
    // приостановленно ли воспроизведение звукового файла
    bool isPause();
    // задано ли повторение звуковому файлу
    bool isRepeat();
signals:
    void playSound(); // возникает когда проигровается звуковой файл
    void pauseSound(); // возникает когда приостоновлено воспроизведение звукового файла
    void stopSound(); // возникает когда остоновлено воспроизведение звукового файла
    void finishSound(); // возникает когда файл проигран до конца
private:
    QMediaPlayer sound;
    bool repeatEnable;
    int milisecRepeat;
private slots:
   void statusChange(QMediaPlayer::MediaStatus status);
   void stateChange(QMediaPlayer::State state);
   void repeated();
   void finished();
};

#endif // SOUND_H
