#ifndef TESTCREATORGAMEOBJECT_H
#define TESTCREATORGAMEOBJECT_H

#include "testgameobject.h"

enum Type_Obj {Test, None};

class TestCreatorGameObject
{
public:
    TestCreatorGameObject();
    static GameObject* CreateGameObject(uint type);
};

#endif // TESTCREATORGAMEOBJECT_H
