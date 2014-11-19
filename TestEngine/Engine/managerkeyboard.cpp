#include "managerkeyboard.h"

ManagerKeyboard* ManagerKeyboard::instance=0;

ManagerKeyboard::ManagerKeyboard()
{
    event = 0;
}

ManagerKeyboard::~ManagerKeyboard()
{
    qDebug()<<"~ManagerMouse";
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
    /*
     * Тестовый вариант
    */
    if (event->key()==Qt::Key_Right)
        buffer_key[0] = true;
    else
        buffer_key[0] = false;
    if (!press)
        buffer_key[0] = false;
}

bool ManagerKeyboard::GetKey(Qt::Key key)
{
    /*
     * Тестовый вариант
    */
    if (event!=0)
    {
        if (buffer_key[0])
            return true;
        else
            return false;
    }
}
