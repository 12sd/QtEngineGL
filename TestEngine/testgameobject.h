#ifndef TESTGAMEOBJECT_H
#define TESTGAMEOBJECT_H

#include <QMatrix>

#include "Engine/gameobject.h"
#include "Engine/sprite.h"
#include "Engine/managersprite.h"
#include "Engine/managermouse.h"
#include "Engine/managerkeyboard.h"
#include "Engine/fps.h"
#include "Engine/managertilemap.h"

class TestGameObject:public GameObject
{
public:
    TestGameObject();
    void Init();
    void Update();
    void Draw();
private:
    Sprite* sprite;
    QMatrix4x4 proj;
    QMatrix4x4 model;
    float i,j;
    int ground;
    bool onGround;
};

#endif // TESTGAMEOBJECT_H
