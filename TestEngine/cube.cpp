#include "cube.h"

Cube::Cube()
{
}

Cube::~Cube()
{
//    delete mesh;
//    delete shader;
}

void Cube::Init(QHash<QString,QString> property)
{
    shader = new Shader("://Resources/for_cube.vert", "://Resources/for_cube.frag");
    shader->SetNameVertex("Vertex");
    shader->SetNameTexture("Texture");
    shader->SetNameMatrixPos("MatrixPos");

    mesh = new Mesh(true);
    mesh->Create();

//    mesh->Bind();
//    shader->enableAttributeArray(shader->GetNameVertex().toStdString().c_str());
//    shader->setAttributeBuffer(shader->GetNameVertex().toStdString().c_str(), GL_FLOAT, 0, 3);

    ManagerMesh::getInstance()->Add(1, mesh);
    cube.SetMeshKey(1);
    ManagerShader::getInstance()->Add(1, shader);
    cube.SetShaderKey(1);
    cube.SetTextureKey(0);
    cube.Create();
    position.SetPos(QVector3D(0, 0, -2));
    position.SetScal(QVector3D(32, 32, 32));

    cam_x = cam_y = cam_z = 0;
}

void Cube::Update()
{
    rot_x+=1;
    if (rot_x>360)
        rot_x = 0;
    pos.setToIdentity();
    pos.translate(0, 0, -2);
    pos.rotate(rot_x, 1, 1, 0);

    position.SetRotX(rot_x);
    position.SetRotY(rot_x);

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_A))
    {
        cam_x-=1;
        Camera::getInstance()->SetPosX(cam_x);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_D))
    {
        cam_x+=1;
        Camera::getInstance()->SetPosX(cam_x);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_W))
    {
        cam_y+=1;
        Camera::getInstance()->SetPosY(cam_y);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_S))
    {
        cam_y-=1;
        Camera::getInstance()->SetPosY(cam_y);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Q))
    {        
        Camera::getInstance()->RotateY(-1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_E))
    {
        Camera::getInstance()->RotateY(1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Z))
    {
        Camera::getInstance()->RotateX(1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_X))
    {
        Camera::getInstance()->RotateX(-1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_C))
    {
        cam_z+=1;
        Camera::getInstance()->SetPosZ(cam_z);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_V))
    {
        cam_z-=1;
        Camera::getInstance()->SetPosZ(cam_z);
    }
}

void Cube::Draw()
{
    ///*
    cube.Bind();
    cube.GetShader()->setUniformValue(cube.GetShader()->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*Camera::getInstance()->GetMatrix()*position.GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, cube.GetMesh()->GetCountVertex());
    //*/

    QMatrix4x4 pos;
    pos.setToIdentity();
    pos.translate(100, 0, -1);
    pos.rotate(45, 1, 0, 1);
    pos.scale(32, 32, 32);
    cube.Bind();
    cube.GetShader()->setUniformValue(cube.GetShader()->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*Camera::getInstance()->GetMatrix()*pos);
    glDrawArrays(GL_TRIANGLES, 0, cube.GetMesh()->GetCountVertex());

    /*
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
