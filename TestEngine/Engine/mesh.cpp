#include "mesh.h"

Mesh::Mesh()
{
    count_ver = 6;
    buf_ver = new float[count_ver * 3];

    ///*XYZ - 1 вершины
    buf_ver[0] = buf_ver[1] = -0.5f;
    buf_ver[2] = 0.0f;
    //*/

    ///*XYZ - 2 вершины
    buf_ver[3] = 0.5f;
    buf_ver[4] = -0.5f;
    buf_ver[5] = 0.0f;
    //*/

    ///*XYZ - 3 вершины
    buf_ver[6] = -0.5f;
    buf_ver[7] = 0.5f;
    buf_ver[8] = 0.0f;
    //*/

    ///*XYZ - 4 вершины
    buf_ver[9] = 0.5f;
    buf_ver[10] = -0.5f;
    buf_ver[11] = 0.0f;
    //*/

    ///*XYZ - 5 вершины
    buf_ver[12] = buf_ver[13] = 0.5f;
    buf_ver[14] = 0.0f;
    //*/

    ///*XYZ - 6 вершины
    buf_ver[15] = -0.5f;
    buf_ver[16] = 0.5f;
    buf_ver[17] = 0.0f;
    //*/
}

Mesh::~Mesh()
{
    vbo_ver.destroy();
    delete [] buf_ver;
    qDebug()<<"~Mesh";
}

void Mesh::Create()
{
    vbo_ver.create();
    vbo_ver.bind();
    vbo_ver.allocate(buf_ver, count_ver * 3 * sizeof(float));
    vbo_ver.release();
}

void Mesh::Bind()
{
    vbo_ver.bind();
}

void Mesh::UnBind()
{
    vbo_ver.release();
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
