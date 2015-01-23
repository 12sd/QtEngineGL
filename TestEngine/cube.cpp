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
    ManagerCamera::getInstance()->GetCurrentCamera()->SetPos(QVector3D(0, 0, 1));
    ManagerCamera::getInstance()->GetCurrentCamera()->SetTypeCamera(Direction_Camera);
}

void Cube::Update()
{
    //qDebug()<<"Camera Rect:"<<Camera::getInstance()->GetRect();

    position.RotateRot(QVector3D(1, 1, 0));
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_A))
    {
        //Camera::getInstance()->SetPosX(cam_x);

        ManagerCamera::getInstance()->GetCurrentCamera()->MoveRight(-1);
        //Camera::getInstance()->MovePos(QVector3D(-1, 0, 0));
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_D))
    {
        //Camera::getInstance()->SetPosX(cam_x);

        ManagerCamera::getInstance()->GetCurrentCamera()->MoveRight(1);
        //Camera::getInstance()->MovePos(QVector3D(1, 0, 0));
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_W))
    {
        //Camera::getInstance()->SetPosY(cam_y);

        ManagerCamera::getInstance()->GetCurrentCamera()->MoveForward(1);
        //Camera::getInstance()->MovePos(QVector3D(0, 0, 1));
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_S))
    {
        //Camera::getInstance()->SetPosY(cam_y);

        ManagerCamera::getInstance()->GetCurrentCamera()->MoveForward(-1);
        //Camera::getInstance()->MovePos(QVector3D(0, 0, -1));
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_C))
    {
        //Camera::getInstance()->SetPosZ(cam_z);

        ManagerCamera::getInstance()->GetCurrentCamera()->MoveUp(1);
        //Camera::getInstance()->MovePos(QVector3D(0, 1, 0));
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_V))
    {
        //Camera::getInstance()->SetPosZ(cam_z);

        ManagerCamera::getInstance()->GetCurrentCamera()->MoveUp(-1);
        //Camera::getInstance()->MovePos(QVector3D(0, -1, 0));
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Q))
    {        
        ManagerCamera::getInstance()->GetCurrentCamera()->RotateY(-1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_E))
    {
        ManagerCamera::getInstance()->GetCurrentCamera()->RotateY(1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Z))
    {
        ManagerCamera::getInstance()->GetCurrentCamera()->RotateX(1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_X))
    {
        ManagerCamera::getInstance()->GetCurrentCamera()->RotateX(-1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_R))
    {
        ManagerCamera::getInstance()->GetCurrentCamera()->RotateZ(1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_T))
    {
        ManagerCamera::getInstance()->GetCurrentCamera()->RotateZ(-1);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_1))
    {
        ManagerCamera::getInstance()->SetCurrentCamera("MainCamera");
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_2))
    {
        ManagerCamera::getInstance()->SetCurrentCamera("Camera");
    }
}

void Cube::Draw()
{
    ///*
    cube.Bind();
    cube.GetShader()->setUniformValue(cube.GetShader()->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix()*position.GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, cube.GetMesh()->GetCountVertex());
    //*/

    QMatrix4x4 pos;
    pos.setToIdentity();
    pos.translate(100, 0, -1);
    pos.rotate(45, 1, 0, 1);
    pos.scale(32, 32, 32);
    cube.Bind();
    cube.GetShader()->setUniformValue(cube.GetShader()->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix()*pos);
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
