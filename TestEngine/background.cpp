#include "background.h"

BackGround::BackGround()
{
}

void BackGround::Init()
{
    sprite = ManagerSprite::getInstance()->GetValue(3);
    proj.setToIdentity();
    proj.ortho(0, 800, 0, 600, -1, 1);
    model.setToIdentity();
    model.scale(800.0/2, 600.0/2);
    model.translate(1, 1, 0);
}

void BackGround::Update()
{

}

void BackGround::Draw()
{
    sprite->Bind();
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * model);
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
