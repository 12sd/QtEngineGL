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
    case Button_Exit:
    {
        GameObject* p = new ButtonExit();
        p->SetName("ButtonExit");
        return p;
        break;
    }
    case Button_Start:
    {
        GameObject* p = new ButtonStart();
        p->SetName("ButtonStart");
        return p;
        break;
    }
    case Back_Ground:
    {
        GameObject* p = new BackGround();
        p->SetName("BackGround");
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
