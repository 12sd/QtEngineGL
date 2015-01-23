#ifndef CUBE_H
#define CUBE_H

#include "Engine/gameobject.h"
#include "Engine/transformer.h"
#include "Engine/object3d.h"
#include "Engine/camera.h"
#include "Engine/setting.h"
#include "Engine/managerkeyboard.h"
#include "Engine/managercamera.h"

class Cube: public GameObject
{
public:
    Cube();
    ~Cube();
    void Init(QHash<QString,QString> property);
    void Update();
    void Draw();
private:
    Object3D cube;
    Transformer position;

    Shader* shader;
    Mesh* mesh;
};

#endif // CUBE_H
