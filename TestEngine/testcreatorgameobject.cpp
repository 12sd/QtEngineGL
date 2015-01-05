#include "testcreatorgameobject.h"

TestCreatorGameObject::TestCreatorGameObject()
{
}

GameObject* TestCreatorGameObject::CreateGameObject(uint type)
{
    switch (type) {
    case Test:
    {
        GameObject* p = new TestGameObject();
        p->SetName("TestGameObject");
        return p;
        break;
    }
    default:
    {
        return 0;
        break;
    }
    }
}
