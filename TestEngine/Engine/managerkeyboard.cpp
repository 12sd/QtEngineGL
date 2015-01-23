#include "managerkeyboard.h"

ManagerKeyboard* ManagerKeyboard::instance=0;

ManagerKeyboard::ManagerKeyboard()
{
    event = 0;
}

ManagerKeyboard::~ManagerKeyboard()
{
    buffer_key.clear();
    qDebug()<<"~ManagerKeyboard";
}

ManagerKeyboard* ManagerKeyboard::getInstance()
{
    if (!instance)
        instance = new ManagerKeyboard();
    return instance;
}

void ManagerKeyboard::Update(QKeyEvent *event,bool press)
{
    this->event = event;
    buffer_key.insert(event->key(),press);
}

bool ManagerKeyboard::GetKey(Qt::Key key)
{
    if (event!=0)
    {
        return buffer_key.value(key);
    }
    return false;
}

QKeyEvent* ManagerKeyboard::GetEvent()
{
    return event;
}

void ManagerKeyboard::Destroy()
{
    if (instance)
        delete instance;
}
