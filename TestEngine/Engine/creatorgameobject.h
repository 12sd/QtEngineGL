#ifndef CREATORGAMEOBJECT_H
#define CREATORGAMEOBJECT_H

#include "gameobject.h"

class CreatorGameObject
{
public:
    CreatorGameObject();
    virtual GameObject* CreateGameObject(uint type)=0;
};

#endif // CREATORGAMEOBJECT_H
