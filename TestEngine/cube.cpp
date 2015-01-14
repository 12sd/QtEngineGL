#include "cube.h"

Cube::Cube()
{
}

Cube::~Cube()
{
    delete mesh;
    delete shader;
}

void Cube::Init(QHash<QString,QString> property)
{
    shader = new Shader("://Resources/for_cube.vert", "://Resources/for_cube.frag");
    shader->SetNameVertex("Vertex");
    shader->SetNameTexture("Texture");
    shader->SetNameMatrixPos("MatrixPos");

    mesh = new Mesh(true);
    mesh->Create();

    mesh->Bind();
    shader->enableAttributeArray(shader->GetNameVertex().toStdString().c_str());
    shader->setAttributeBuffer(shader->GetNameVertex().toStdString().c_str(), GL_FLOAT, 0, 3);
}

void Cube::Update()
{
    rot_x+=1;
    if (rot_x>360)
        rot_x = 0;
    pos.setToIdentity();
    pos.translate(0, 0, -5);
    pos.rotate(rot_x, 1, 1, 0);
}

void Cube::Draw()
{
    /*
    cube.Bind();
    cube.GetShader()->setUniformValue(cube.GetShader()->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*position.GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, cube.GetMesh()->GetCountVertex());
    //*/

    ///*
    shader->bind();
    mesh->Bind();
    shader->setUniformValue(shader->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*Camera::getInstance()->GetMatrix()*pos);
    glDrawArrays(GL_TRIANGLES, 0, mesh->GetCountVertex());
    //*/

    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(Setting::GetProjection().data());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glLoadMatrixf(pos.data());
    glTranslatef(0, 0, -5);
    glRotatef(rot_x, 1, 1, 0);

    float* tmp = mesh->GetVertex();
    glBegin(GL_TRIANGLES);
    for (int i=0; i<mesh->GetCountVertex()*3; i+=3)
    {
        glVertex3f(tmp[i], tmp[i+1], tmp[i+2]);
    }
    glEnd();
    //*/

}
