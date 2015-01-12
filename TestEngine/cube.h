#ifndef CUBE_H
#define CUBE_H

#include "Engine/gameobject.h"
#include "Engine/transformer.h"
#include "Engine/object3d.h"
#include "Engine/camera.h"
#include "Engine/setting.h"

class Cube: public GameObject
{
public:
    Cube();
    void Init(QHash<QString,QString> property);
    void Update();
    void Draw();
private:
    Transformer position;
    Object3D cube;
};

#endif // CUBE_H
