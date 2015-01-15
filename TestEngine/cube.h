#ifndef CUBE_H
#define CUBE_H

#include "Engine/gameobject.h"
#include "Engine/transformer.h"
#include "Engine/object3d.h"
#include "Engine/camera.h"
#include "Engine/setting.h"
#include "Engine/managerkeyboard.h"

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

    QMatrix4x4 pos;
    Shader* shader;
    Mesh* mesh;
    float rot_x;

    float cam_x, cam_y, cam_z;
};

#endif // CUBE_H
