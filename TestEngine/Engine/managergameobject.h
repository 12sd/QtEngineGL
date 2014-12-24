#ifndef MANAGERGAMEOBJECT_H
#define MANAGERGAMEOBJECT_H

#include <QHash>
#include <QDebug>
#include "gameobject.h"

class ManagerGameObject
{
public:
    ManagerGameObject();
    ~ManagerGameObject();
    static ManagerGameObject* getInstance();
    void Add(QString key, GameObject* value);
    GameObject* GetValue(QString key);
    QList<GameObject*> GetValues(QString key);
    void Clear();
    void Destroy();

private:
    static ManagerGameObject* instance;
    QHash<QString, GameObject*> hash_tab;
};

#endif // MANAGERGAMEOBJECT_H
