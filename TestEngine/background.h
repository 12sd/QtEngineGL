#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QApplication>

#include "Engine/gameobject.h"
#include "Engine/managersprite.h"
#include "Engine/managermouse.h"

class BackGround: public GameObject
{
public:
    BackGround();
    void Init();
    void Update();
    void Draw();
private:
    Sprite* sprite;
    QMatrix4x4 proj;
    QMatrix4x4 model;
};

#endif // BACKGROUND_H
