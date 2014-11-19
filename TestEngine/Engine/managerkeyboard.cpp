#include "managerkeyboard.h"

ManagerKeyboard* ManagerKeyboard::instance=0;

ManagerKeyboard::ManagerKeyboard()
{
    event = 0;
}

ManagerKeyboard::~ManagerKeyboard()
{
    buffer_key.clear();
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
    buffer_key.insert(event->key(),press);
    /*
     * Тестовый вариант
    */
//    if (event->key()==Qt::Key_Right)
//    {
//        buffer_key[0] = true;
//        if (!press)
//            buffer_key[0] = false;
//    }else
//    {
//        buffer_key[0] = false;
//    }
//    if (event->key()==Qt::Key_Left)
//    {
//        buffer_key[1] = true;
//        if (!press)
//            buffer_key[1] = false;
//    }else
//    {
//        buffer_key[1] = false;
//    }
}

bool ManagerKeyboard::GetKey(Qt::Key key)
{
    /*
     * Тестовый вариант
    */
    if (event!=0)
    {
        return buffer_key.value(key);
    }
    return false;
}
