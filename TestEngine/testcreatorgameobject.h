#ifndef TESTCREATORGAMEOBJECT_H
#define TESTCREATORGAMEOBJECT_H

#include "testgameobject.h"
#include "buttonexit.h"
#include "buttonstart.h"
#include "background.h"
#include "Engine/creatorgameobject.h"

enum Type_Obj {Test, Button_Exit, Button_Start, Back_Ground, None};

class TestCreatorGameObject: public CreatorGameObject
{
public:
    TestCreatorGameObject();
    GameObject* CreateGameObject(uint type);
};

#endif // TESTCREATORGAMEOBJECT_H
