#ifndef TESTGAMEOBJECT_H
#define TESTGAMEOBJECT_H

#include <QMatrix>

#include "Engine/gameobject.h"
#include "Engine/transformer.h"
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
    void Init(QHash<QString,QString> property);
    void Update();
    void Draw();
public:
    Transformer position;
    Sprite* sprite;
    QMatrix4x4 proj;
    bool onGround;
    float gravity;
};

#endif // TESTGAMEOBJECT_H
