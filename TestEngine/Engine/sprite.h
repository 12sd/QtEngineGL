#ifndef SPRITE_H
#define SPRITE_H

#include <QOpenGLVertexArrayObject>
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "managermesh.h"
#include "managershader.h"
#include "managertexture.h"

class Sprite
{
public:
    Sprite();
    ~Sprite();
    void SetMeshKey(int key);
    void SetShaderKey(int key);
    void SetTextureKey(int key);
    Mesh* GetMesh();
    Shader* GetShader();
    Texture* GetTexture();
    void Create();
    void Bind(int width = 0, int height = 0, int frameX = 0, int frameY = 0);
    void UnBind();
private:
    Mesh* mesh;
    Shader* shader;
    Texture* texture;
    float* buf_tex;
    QOpenGLBuffer vbo_tex;
    QOpenGLVertexArrayObject vao;
};

#endif // SPRITE_H
