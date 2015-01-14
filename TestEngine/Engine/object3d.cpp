#include "object3d.h"

Object3D::Object3D()
{
    mesh = 0;
    shader = 0;
    texture = 0;
}

Object3D::~Object3D()
{
    vao.destroy();
    qDebug()<<"~Object3D";
}

void Object3D::SetMeshKey(int key)
{
    mesh = ManagerMesh::getInstance()->GetValue(key);
}

void Object3D::SetShaderKey(int key)
{
    shader = ManagerShader::getInstance()->GetValue(key);
}

void Object3D::SetTextureKey(int key)
{
    texture = ManagerTexture::getInstance()->GetValue(key);
}

Mesh* Object3D::GetMesh()
{
    return mesh;
}

Shader* Object3D::GetShader()
{
    return shader;
}

Texture* Object3D::GetTexture()
{
    return texture;
}

void Object3D::Create()
{
    vao.create();
    vao.bind();

    mesh->Bind();
    shader->enableAttributeArray(shader->GetNameVertex().toStdString().c_str());
    shader->setAttributeBuffer(shader->GetNameVertex().toStdString().c_str(), GL_FLOAT, 0, 3);
}

void Object3D::Bind()
{
    shader->bind();
    texture->Bind();
    vao.bind();
}

void Object3D::UnBind()
{
    vao.release();
    texture->UnBind();
    shader->release();
}
