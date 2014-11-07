#include "managersprite.h"

ManagerSprite* ManagerSprite::instance = 0;

ManagerSprite::ManagerSprite()
{
}

ManagerSprite::~ManagerSprite()
{
    Clear();
    qDebug()<<"~ManagerSprite";
}

ManagerSprite* ManagerSprite::getInstance()
{
    if (!instance)
        instance = new ManagerSprite();
    return instance;
}

void ManagerSprite::Add(int key, Sprite* value)
{
    hash_tab.insert(key, value);
}

Sprite* ManagerSprite::GetValue(int key)
{
    return hash_tab.value(key);
}

void ManagerSprite::Clear()
{
    QHash<int, Sprite*>::iterator it = hash_tab.begin();
    while (it != hash_tab.end())
    {
        delete it.value();
        it++;
    }
    hash_tab.clear();
}

void ManagerSprite::Destroy()
{
    if (instance)
    {
        delete instance;
    }
}

