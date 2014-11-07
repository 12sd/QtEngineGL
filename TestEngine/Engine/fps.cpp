#include "fps.h"

Fps* Fps::instance = 0;

Fps::Fps()
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateTimer()));
    timer->start(1000);
}

Fps::~Fps()
{
    delete timer;
    qDebug()<<"~Fps";
}

int Fps::GetFps()
{
    count++;
    return fps;
}

void Fps::UpdateTimer()
{
    fps = count;
    count = 0;
}

Fps* Fps::getInstance()
{
    if (!instance)
        instance = new Fps();
    return instance;
}

void Fps::Destroy()
{
    if (instance)
    {
        delete instance;
    }
}
