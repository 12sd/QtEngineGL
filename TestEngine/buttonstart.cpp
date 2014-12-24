#include "buttonstart.h"

ButtonStart::ButtonStart()
{
}

void ButtonStart::Init(QHash<QString,QString> property)
{
    sprite = ManagerSprite::getInstance()->GetValue(2);
    proj.setToIdentity();
    proj.ortho(0, 800, 0, 600, -1, 1);
    model.setToIdentity();
    model.translate(400, 600-80-80-10, 0);
    model.scale(400.0, 80.0);
}

void ButtonStart::Update()
{
    Qt::MouseButton button = ManagerMouse::getInstance()->GetButton();
    int x = ManagerMouse::getInstance()->GetX();
    int y = ManagerMouse::getInstance()->GetY();
    if (button==Qt::LeftButton)
    {
        if (x>200 && x<590)
        {
            if (y>137 && y<200)
            {
                qDebug()<<"BackGround";

                CurrentStatusGame = DragPlayer1;
            }
        }
    }
}

void ButtonStart::Draw()
{
    sprite->Bind();
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * model);
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
