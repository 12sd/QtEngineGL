#ifndef FPS_H
#define FPS_H

#include <QObject>
#include <QTimer>
#include <QDebug>

class Fps: public QObject
{
    Q_OBJECT
public:
    Fps();
    ~Fps();
    int GetFps();
    static Fps* getInstance();
    void Destroy();

public slots:
    void UpdateTimer();

private:
    QTimer* timer;
    int fps;
    int count;
    static Fps* instance;
};

#endif // FPS_H
