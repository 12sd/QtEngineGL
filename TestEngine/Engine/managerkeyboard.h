#ifndef MANAGERKEYBOARD_H
#define MANAGERKEYBOARD_H

#include <QKeyEvent>
#include <QHash>
#include <QDebug>

class ManagerKeyboard
{
public:
    ManagerKeyboard();
    ~ManagerKeyboard();
    static ManagerKeyboard* getInstance();
    void Update(QKeyEvent* event,bool press=true);
    bool GetKey(Qt::Key key);
    QKeyEvent* GetEvent();
    void Destroy();
private:
    static ManagerKeyboard* instance;
    QKeyEvent* event;
    QHash<int, bool> buffer_key;
};

#endif // MANAGERKEYBOARD_H
