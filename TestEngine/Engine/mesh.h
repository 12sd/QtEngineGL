#ifndef MESH_H
#define MESH_H

#include <QOpenGLBuffer>
#include <QDebug>

enum TYPE_MESH {Vertex_Type, Vertex_Texture_Type};

class Mesh
{
public:
    Mesh();
    Mesh(TYPE_MESH type_mesh);
    ~Mesh();
    TYPE_MESH GetTypeMesh();
    void SetTypeMesh(TYPE_MESH type_mesh);
    void Create();
    void Bind(TYPE_MESH type=Vertex_Type);
    void UnBind();
    void SetVertex(float* vertex, int count_vertex);
    float* GetVertex();
    int GetCountVertex();
    void SetVertexTexture(float* vertex, int count_vertex);
    float* GetVertexTexture();
    int GetCountVertexTexture();
private:
    TYPE_MESH type_mesh;
    float* buf_ver;
    int count_ver;
    QOpenGLBuffer vbo_ver;
    float* buf_tex_ver;
    int count_tex_ver;
    QOpenGLBuffer vbo_tex_ver;
};

#endif // MESH_H
