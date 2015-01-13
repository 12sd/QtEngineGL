#include "mesh.h"

Mesh::Mesh()
{
    count_ver = 6;
    buf_ver = new float[count_ver * 3];

////Center - XY_center
//    ///*XYZ - 1 вершины
//    buf_ver[0] = buf_ver[1] = -0.5f;
//    buf_ver[2] = 0.0f;
//    //*/

//    ///*XYZ - 2 вершины
//    buf_ver[3] = 0.5f;
//    buf_ver[4] = -0.5f;
//    buf_ver[5] = 0.0f;
//    //*/

//    ///*XYZ - 3 вершины
//    buf_ver[6] = -0.5f;
//    buf_ver[7] = 0.5f;
//    buf_ver[8] = 0.0f;
//    //*/

//    ///*XYZ - 4 вершины
//    buf_ver[9] = 0.5f;
//    buf_ver[10] = -0.5f;
//    buf_ver[11] = 0.0f;
//    //*/

//    ///*XYZ - 5 вершины
//    buf_ver[12] = buf_ver[13] = 0.5f;
//    buf_ver[14] = 0.0f;
//    //*/

//    ///*XYZ - 6 вершины
//    buf_ver[15] = -0.5f;
//    buf_ver[16] = 0.5f;
//    buf_ver[17] = 0.0f;
//    //*/

//Center - XY_left_down
    ///*XYZ - 1 вершины
    buf_ver[0] = buf_ver[1] = 0.0f;
    buf_ver[2] = 0.0f;
    //*/

    ///*XYZ - 2 вершины
    buf_ver[3] = 1.0f;
    buf_ver[4] = 0.0f;
    buf_ver[5] = 0.0f;
    //*/

    ///*XYZ - 3 вершины
    buf_ver[6] = 0.0f;
    buf_ver[7] = 1.0f;
    buf_ver[8] = 0.0f;
    //*/

    ///*XYZ - 4 вершины
    buf_ver[9] = 1.0f;
    buf_ver[10] = 0.0f;
    buf_ver[11] = 0.0f;
    //*/

    ///*XYZ - 5 вершины
    buf_ver[12] = buf_ver[13] = 1.0f;
    buf_ver[14] = 0.0f;
    //*/

    ///*XYZ - 6 вершины
    buf_ver[15] = 0.0f;
    buf_ver[16] = 1.0f;
    buf_ver[17] = 0.0f;
    //*/

    type_mesh = Vertex_Type;
}

Mesh::Mesh(TYPE_MESH type_mesh)
{
    if (type_mesh==Vertex_Texture_Type)
    {
        count_ver = 36;
        buf_ver = new float[count_ver * 3];

        count_tex_ver = 36;
        buf_tex_ver = new float[count_tex_ver * 2];

        float tmp[] = {
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f, //1 - грань
            -1.0f, 1.0f, 1.0f,

            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, //1 - грань
            -1.0f, 1.0f, 1.0f,

            1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f, //2 - грань
            1.0f, 1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f, //2 - грань
            1.0f, 1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f, //3 - грань
            1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f, //3 - грань
            1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f, //4 - грань
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, //4 - грань
            -1.0f, 1.0f, -1.0f,

            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, //5 - грань
            -1.0f, 1.0f, -1.0f,

            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f, //5 - грань
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f, //6 - грань
            1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f, //6 - грань
            1.0f, -1.0f, -1.0f
        };

        qDebug()<<"Vertex buffer";
        for (int i=0; i<36*3; i++)
        {
            buf_ver[i] = tmp[i];
            qDebug()<<buf_ver[i];
        }

        float tmp_tex[] = {
            0.0f, 0.0f,
            1.0f, 0.0f, //1 - грань
            0.0f, 1.0f,

            1.0f, 0.0f,
            0.0f, 1.0f, //1 - грань
            1.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 0.0f, //2 - грань
            0.0f, 1.0f,

            1.0f, 0.0f,
            0.0f, 1.0f, //2 - грань
            1.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 0.0f, //3 - грань
            0.0f, 1.0f,

            1.0f, 0.0f,
            0.0f, 1.0f, //3 - грань
            1.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 0.0f, //4 - грань
            0.0f, 1.0f,

            1.0f, 0.0f,
            0.0f, 1.0f, //4 - грань
            1.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 0.0f, //5 - грань
            0.0f, 1.0f,

            1.0f, 0.0f,
            0.0f, 1.0f, //5 - грань
            1.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 0.0f, //6 - грань
            0.0f, 1.0f,

            1.0f, 0.0f,
            0.0f, 1.0f, //6 - грань
            1.0f, 1.0f,
        };

        qDebug()<<"Texture buffer";
        for (int i=0; i<36*2; i++)
        {
            buf_tex_ver[i] = tmp_tex[i];
            qDebug()<<buf_tex_ver[i];
        }

        this->type_mesh = Vertex_Texture_Type;
    }
}

Mesh::~Mesh()
{
    vbo_ver.destroy();
    delete [] buf_ver;
    if (type_mesh==Vertex_Texture_Type)
    {
        vbo_tex_ver.destroy();
        delete [] buf_tex_ver;
    }
    qDebug()<<"~Mesh";
}

TYPE_MESH Mesh::GetTypeMesh()
{
    return type_mesh;
}

void Mesh::SetTypeMesh(TYPE_MESH type_mesh)
{
    this->type_mesh = type_mesh;
}

void Mesh::Create()
{
    vbo_ver.create();
    vbo_ver.bind();
    vbo_ver.allocate(buf_ver, count_ver * 3 * sizeof(float));
    vbo_ver.release();

    if (type_mesh==Vertex_Texture_Type)
    {
        vbo_tex_ver.create();
        vbo_tex_ver.bind();
        vbo_tex_ver.allocate(buf_tex_ver, count_tex_ver * 2 * sizeof(float));
        vbo_tex_ver.release();
    }
}

void Mesh::Bind(TYPE_MESH type)
{
    if (type==Vertex_Type)
        vbo_ver.bind();
    if (type==Vertex_Texture_Type)
        vbo_tex_ver.bind();
}

void Mesh::UnBind()
{
    if (type_mesh==Vertex_Type)
        vbo_ver.release();
    if (type_mesh==Vertex_Texture_Type)
        vbo_tex_ver.release();
}

void Mesh::SetVertex(float* vertex, int count_vertex)
{
    delete [] buf_ver;
    count_ver = count_vertex;
    buf_ver = new float[count_ver * 3];
    for (int i = 0; i < count_ver * 3; i++)
        buf_ver[i] = vertex[i];
}

float* Mesh::GetVertex()
{
    return buf_ver;
}

int Mesh::GetCountVertex()
{
    return count_ver;
}

void Mesh::SetVertexTexture(float* vertex, int count_vertex)
{
    delete [] buf_tex_ver;
    count_tex_ver = count_vertex;
    buf_tex_ver = new float[count_ver * 2];
    for (int i = 0; i < count_ver * 2; i++)
        buf_tex_ver[i] = vertex[i];
}

float* Mesh::GetVertexTexture()
{
    return buf_tex_ver;
}

int Mesh::GetCountVertexTexture()
{
    return count_tex_ver;
}
