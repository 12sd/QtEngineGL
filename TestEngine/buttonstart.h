#ifndef BUTTONSTART_H
#define BUTTONSTART_H

#include <QApplication>

#include "Engine/gameobject.h"
#include "Engine/managersprite.h"
#include "Engine/managermouse.h"

#include "statusgame.h"

class ButtonStart: public GameObject
{
public:
    ButtonStart();
    void Init();
    void Update();
    void Draw();
private:
    Sprite* sprite;
    QMatrix4x4 proj;
    QMatrix4x4 model;
};

#endif // BUTTONSTART_H
