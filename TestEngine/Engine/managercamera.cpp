#include "managercamera.h"

ManagerCamera* ManagerCamera::instance = 0;

ManagerCamera::ManagerCamera()
{
    current = 0;
}

ManagerCamera::~ManagerCamera()
{
    Clear();
    qDebug()<<"~ManagerCamera";
}

ManagerCamera* ManagerCamera::getInstance()
{
    if (!instance)
        instance = new ManagerCamera();
    return instance;
}

void ManagerCamera::Add(QString key, Camera* value)
{
    hash_tab.insert(key, value);
}

Camera* ManagerCamera::GetValue(QString key)
{
    return hash_tab.value(key);
}

Camera* ManagerCamera::GetCurrentCamera()
{
    return current;
}

void ManagerCamera::SetCurrentCamera(QString key)
{
    current = GetValue(key);
}

void ManagerCamera::Clear()
{
    QHash<QString, Camera*>::iterator it = hash_tab.begin();
    while (it != hash_tab.end())
    {
        delete it.value();
        it++;
    }
    hash_tab.clear();
}

void ManagerCamera::Destroy()
{
    if (instance)
    {
        delete instance;
    }
}
