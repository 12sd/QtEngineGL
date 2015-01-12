#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <QOpenGLVertexArrayObject>
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "managermesh.h"
#include "managershader.h"
#include "managertexture.h"

class Object3D
{
public:
    Object3D();
    ~Object3D();
    void SetMeshKey(int key);
    void SetShaderKey(int key);
    void SetTextureKey(int key);
    Mesh* GetMesh();
    Shader* GetShader();
    Texture* GetTexture();
    void Create();
    void Bind();
    void UnBind();
private:
    Mesh* mesh;
    Shader* shader;
    Texture* texture;
    QOpenGLVertexArrayObject vao;
};

#endif // OBJECT3D_H
