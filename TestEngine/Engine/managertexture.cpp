#include "managertexture.h"

ManagerTexture* ManagerTexture::instance = 0;

ManagerTexture::ManagerTexture()
{
}

ManagerTexture::~ManagerTexture()
{
    Clear();
    qDebug()<<"~ManagerTexture";
}

ManagerTexture* ManagerTexture::getInstance()
{
    if (!instance)
        instance = new ManagerTexture();
    return instance;
}

void ManagerTexture::Add(int key, Texture* value)
{
    hash_tab.insert(key, value);
}

Texture* ManagerTexture::GetValue(int key)
{
    return hash_tab.value(key);
}

void ManagerTexture::Clear()
{
    QHash<int, Texture*>::iterator it = hash_tab.begin();
    while (it != hash_tab.end())
    {
        delete it.value();
        it++;
    }
    hash_tab.clear();
}

void ManagerTexture::Destroy()
{
    if (instance)
    {
        delete instance;
    }
}

