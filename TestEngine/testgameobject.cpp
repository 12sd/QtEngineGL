#include "testgameobject.h"

TestGameObject::TestGameObject()
{
}

void TestGameObject::Init(QHash<QString,QString> property)
{
    /*
     * Инициализация объекта
    */
    sprite = ManagerSprite::getInstance()->GetValue(1);
    proj.setToIdentity();
    proj.ortho(0, 480, 0, 320, -1, 1);

    onGround = false;
    gravity = 0.1;
    position.SetScalX(18);
    position.SetScalY(26);
}

void TestGameObject::Update()
{
    /*
     * Обновление логики, втом числе движение объекта
    */
    float time = 1.0/Fps::getInstance()->GetFps();
    gravity = 0.3;
//    if (gravity>3)
//        gravity = 3;

    Qt::MouseButton button = ManagerMouse::getInstance()->GetButton();
    int x = ManagerMouse::getInstance()->GetX();
    int y = ManagerMouse::getInstance()->GetY();

    if (button == Qt::LeftButton)
    {
        position.SetPosX(x);
        position.SetPosY(320-y);
        onGround = false;
    }

    Transformer future_pos;
    future_pos.SetPos(position.GetPos());
    future_pos.SetRot(position.GetRot());
    future_pos.SetScal(position.GetScal());

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Right))
    {
        future_pos.MoveX(0.3);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Left))
    {
        future_pos.MoveX(-0.3);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Up))
    {
        future_pos.MoveY(1);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Down))
    {
        future_pos.MoveY(-1);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Space) && onGround==true)
    {
        future_pos.MoveY(32);
        onGround = false;
    }


    if (onGround==false)
        future_pos.MoveY(-gravity);

    QVector3D tmp;
    //tmp = this->GetPos();
    QRectF bound(future_pos.GetPosX(), future_pos.GetPosY(), 18, 26);
    //if (ManagerTileMap::getInstance()->CheckCollision("collision", last_pos, this->GetPos(), bound, tmp, onGround))
    {
        ManagerTileMap::getInstance()->CheckCollision("collision", position.GetPos(), future_pos.GetPos(), bound, tmp, onGround, gravity);
        qDebug()<<"Collision";
        position.SetPos(tmp);
    }

    qDebug()<<"onGround:"<<onGround<<" Gravity:"<<gravity;
}

void TestGameObject::Draw()
{
    /*
     * Прорисовка объекта
    */

    sprite->Bind(18, 26);
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * position.GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
