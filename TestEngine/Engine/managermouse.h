#ifndef MANAGERMOUSE_H
#define MANAGERMOUSE_H

#include <QMouseEvent>
#include <QDebug>

class ManagerMouse
{
public:
    ManagerMouse();
    ~ManagerMouse();
    static ManagerMouse* getInstance();
    void Update(QMouseEvent* event);
    QMouseEvent* GetEvent();
    int GetX();
    int GetY();
    Qt::MouseButton GetButton();
    void Destroy();

private:
    static ManagerMouse* instance;
    QMouseEvent* event;
    Qt::MouseButton button;
    int x;
    int y;
};

#endif // MANAGERMOUSE_H
