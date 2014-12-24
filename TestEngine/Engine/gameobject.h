#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>
#include <QHash>

class GameObject
{
public:
    GameObject();
    virtual void Init(QHash<QString,QString> property)=0;
    virtual void Update()=0;
    virtual void Draw()=0;
    void SetName(QString name);
    QString GetName();

private:
    QString name;
};

#endif // GAMEOBJECT_H
