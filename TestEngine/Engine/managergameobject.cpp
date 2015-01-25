#include "managergameobject.h"

ManagerGameObject* ManagerGameObject::instance = 0;

ManagerGameObject::ManagerGameObject()
{
}

ManagerGameObject::~ManagerGameObject()
{
    Clear();
    qDebug()<<"~ManagerGameObject";
}

ManagerGameObject* ManagerGameObject::getInstance()
{
    if (!instance)
        instance = new ManagerGameObject();
    return instance;
}

void ManagerGameObject::Add(QString key, GameObject* value)
{
    hash_tab.insertMulti(key, value);
}

GameObject* ManagerGameObject::GetValue(QString key)
{
    return hash_tab.value(key);
}

QList<GameObject*> ManagerGameObject::GetValues(QString key)
{
    return hash_tab.values(key);
}

QHash<QString, GameObject*> ManagerGameObject::GetHashTab()
{
    return hash_tab;
}

void ManagerGameObject::Clear()
{
    QHash<QString, GameObject*>::iterator it = hash_tab.begin();
    while (it != hash_tab.end())
    {
        delete it.value();
        it++;
    }
    hash_tab.clear();
}

void ManagerGameObject::Destroy()
{
    if (instance)
    {
        delete instance;
    }
}

