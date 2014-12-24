#include "buttonexit.h"

ButtonExit::ButtonExit()
{
}

void ButtonExit::Init(QHash<QString,QString> property)
{
    sprite = ManagerSprite::getInstance()->GetValue(1);
    proj.setToIdentity();
    proj.ortho(0, 800, 0, 600, -1, 1);
    model.setToIdentity();
    model.translate(400, 600-80, 0);
    model.scale(400.0, 80.0);
}

void ButtonExit::Update()
{
    Qt::MouseButton button = ManagerMouse::getInstance()->GetButton();
    int x = ManagerMouse::getInstance()->GetX();
    int y = ManagerMouse::getInstance()->GetY();
    if (button==Qt::LeftButton)
    {
        if (x>200 && x<590)
        {
            if (y>46 && y<110)
            {
                qDebug()<<"Exit";
                QApplication::exit();
            }
        }
    }
}

void ButtonExit::Draw()
{
    sprite->Bind();
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * model);
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
