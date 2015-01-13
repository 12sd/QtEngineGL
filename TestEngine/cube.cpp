#include "cube.h"

Cube::Cube()
{
}

void Cube::Init(QHash<QString,QString> property)
{
    position.SetPos(QVector3D(0, 0, -3));
    cube.SetMeshKey(1);
    cube.SetTextureKey(0);
    Shader* sh = new Shader("://Resources/for_cube.vert", "://Resources/for_cube.frag");
//    if (!sh->Load("://Resources/for_cube.vert", "://Resources/for_cube.frag"))
//        qDebug()<<"Error Load Shader";
    sh->SetNameVertex("Vertex");
    sh->SetNameTexture("Texture");
    sh->SetNameMatrixPos("MatrixPos");
    ManagerShader::getInstance()->Add(1, sh);
    cube.SetShaderKey(1);
}

void Cube::Update()
{

}

void Cube::Draw()
{
    cube.Bind();
    cube.GetShader()->setUniformValue(cube.GetShader()->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*position.GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, cube.GetMesh()->GetCountVertex());
}
