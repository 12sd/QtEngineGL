#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>

class GameObject
{
public:
    GameObject();
    virtual void Init()=0;
    virtual void Update()=0;
    virtual void Draw()=0;
    void SetName(QString name);
    QString GetName();

private:
    QString name;
};

#endif // GAMEOBJECT_H
