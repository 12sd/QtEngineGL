#include "gameobject.h"

GameObject::GameObject()
{

}

void GameObject::SetName(QString name)
{
    this->name = name;
}

QString GameObject::GetName()
{
    return name;
}
