#ifndef MESH_H
#define MESH_H

#include <QOpenGLBuffer>
#include <QDebug>

class Mesh
{
public:
    Mesh();
    ~Mesh();
    void Create();
    void Bind();
    void UnBind();
    void SetVertex(float* vertex, int count_vertex);
    float* GetVertex();
    int GetCountVertex();

private:
    float* buf_ver;
    int count_ver;
    QOpenGLBuffer vbo_ver;
};

#endif // MESH_H
