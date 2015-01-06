#include "testgameobject.h"

TestGameObject::TestGameObject()
{
}

void TestGameObject::Init(QHash<QString,QString> property)
{
    /*
     * Инициализация объекта
    */
    sprite = ManagerSprite::getInstance()->GetValue(0);
    proj.setToIdentity();
    proj.ortho(0, 1024, 0, 512, -1, 1);

    onGround = false;
    gravity = 32;
    position.SetScalX(32);
    position.SetScalY(32);
}

void TestGameObject::Update()
{
    /*
     * Обновление логики, втом числе движение объекта
    */
    float time = 1.0/Fps::getInstance()->GetFps();

    Qt::MouseButton button = ManagerMouse::getInstance()->GetButton();
    int x = ManagerMouse::getInstance()->GetX();
    int y = ManagerMouse::getInstance()->GetY();

    if (button == Qt::LeftButton)
    {
        position.SetPosX(x);
        position.SetPosY(512-y);
        onGround = false;
        gravity = 32;
    }

    Transformer future_pos;
    future_pos.SetPos(position.GetPos());
    future_pos.SetRot(position.GetRot());
    future_pos.SetScal(position.GetScal());

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Right))
    {
        future_pos.MoveX(32*time);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Left))
    {
        future_pos.MoveX(-32*time);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Up))
    {
        future_pos.MoveY(32*time);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Down))
    {
        future_pos.MoveY(-32*time);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Space) && onGround==true)
    {
        future_pos.MoveY(32);
        onGround = false;
        gravity = 32;
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_A))
    {
        future_pos.RotateZ(-2);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_D))
    {
        future_pos.RotateZ(2);
    }

    if (onGround==false)
        future_pos.MoveY(-gravity*time);

    QVector3D tmp;
    //tmp = this->GetPos();
    QRectF bound(future_pos.GetPosX(), future_pos.GetPosY(), 32, 32);
    //if (ManagerTileMap::getInstance()->CheckCollision("collision", last_pos, this->GetPos(), bound, tmp, onGround))
    {
        ManagerTileMap::getInstance()->CheckCollision("collision", position.GetPos(), future_pos.GetPos(), bound, tmp, onGround, gravity);
        qDebug()<<"Collision";
        position.SetPos(tmp);
    }

    qDebug()<<"onGround:"<<onGround;
}

void TestGameObject::Draw()
{
    /*
     * Прорисовка объекта
    */

    sprite->Bind(32, 32, 4, 0);
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * position.GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
