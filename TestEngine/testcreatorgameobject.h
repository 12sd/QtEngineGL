#ifndef TESTCREATORGAMEOBJECT_H
#define TESTCREATORGAMEOBJECT_H

#include "testgameobject.h"
#include "buttonexit.h"
#include "buttonstart.h"
#include "background.h"

enum Type_Obj {Test, Button_Exit, Button_Start, Back_Ground, None};

class TestCreatorGameObject
{
public:
    TestCreatorGameObject();
    static GameObject* CreateGameObject(uint type);
};

#endif // TESTCREATORGAMEOBJECT_H
