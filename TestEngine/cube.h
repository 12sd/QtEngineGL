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
    ~Cube();
    void Init(QHash<QString,QString> property);
    void Update();
    void Draw();
private:
    QMatrix4x4 pos;
    Shader* shader;
    Mesh* mesh;
    float rot_x;
};

#endif // CUBE_H
