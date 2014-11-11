#ifndef TESTGAMEOBJECT_H
#define TESTGAMEOBJECT_H

#include "Engine/gameobject.h"

class TestGameObject:public GameObject
{
public:
    TestGameObject();
    void Update();
    void Draw();
};

#endif // TESTGAMEOBJECT_H
