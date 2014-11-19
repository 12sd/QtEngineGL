#include "managermouse.h"

ManagerMouse* ManagerMouse::instance=0;

ManagerMouse::ManagerMouse()
{
}

ManagerMouse::~ManagerMouse()
{
    qDebug()<<"~ManagerMouse";
}

ManagerMouse* ManagerMouse::getInstance()
{
    if (!instance)
        instance = new ManagerMouse();
    return instance;
}

void ManagerMouse::Update(QMouseEvent* event,bool press)
{
    this->event = event;
    x = event->x();
    y = event->y();
    if (press)
        button = event->button();
    else
        button = Qt::NoButton;
}

QMouseEvent* ManagerMouse::GetEvent()
{
    return event;
}

int ManagerMouse::GetX()
{
    return x;
}

int ManagerMouse::GetY()
{
    return y;
}

Qt::MouseButton ManagerMouse::GetButton()
{
    return button;
}

void ManagerMouse::Destroy()
{
    if (instance)
        delete instance;
}
