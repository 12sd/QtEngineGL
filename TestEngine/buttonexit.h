#ifndef BUTTONEXIT_H
#define BUTTONEXIT_H

#include <QApplication>

#include "Engine/gameobject.h"
#include "Engine/managersprite.h"
#include "Engine/managermouse.h"

class ButtonExit: public GameObject
{
public:
    ButtonExit();
    void Init();
    void Update();
    void Draw();
private:
    Sprite* sprite;
    QMatrix4x4 proj;
    QMatrix4x4 model;
};

#endif // BUTTONEXIT_H
