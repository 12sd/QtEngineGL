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
    proj.ortho(0, 800, 0, 600, -1, 1);

    onGround = false;
    gravity = 0.1;
    position.SetScalX(48);
    position.SetScalY(65);
}

void TestGameObject::Update()
{
    /*
     * Обновление логики, втом числе движение объекта
    */
    float time = 1.0/Fps::getInstance()->GetFps();
    gravity += 1;
    if (gravity>5)
        gravity = 5;

    QVector2D dir(0, 0);

    Qt::MouseButton button = ManagerMouse::getInstance()->GetButton();
    int x = ManagerMouse::getInstance()->GetX();
    int y = ManagerMouse::getInstance()->GetY();

    if (button == Qt::LeftButton)
    {
        position.SetPosX(x);
        position.SetPosY(600-y);
        onGround = false;

//        QRectF tmp(position.GetPosX(), position.GetPosY(), 18, 26);
//        ManagerTileMap::getInstance()->GetTiles("collision", tmp);
    }

    Transformer future_pos;
    future_pos.SetPos(position.GetPos());
    future_pos.SetRot(position.GetRot());
    future_pos.SetScal(position.GetScal());

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Right))
    {
        future_pos.MoveX(8);
        dir.setX(1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Left))
    {
        future_pos.MoveX(-8);
        dir.setX(-1);
    }

//    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Up))
//    {
//        future_pos.MoveY(1);
//        dir.setY(1);
//    }

//    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Down))
//    {
//        future_pos.MoveY(-1);
//        dir.setY(-1);
//    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Space) && onGround==true)
    {
        future_pos.MoveY(64);
        dir.setY(1);
        onGround = false;
    }


    /* Способ 1 Collision
    QVector3D tmp;
    QRectF bound(future_pos.GetPosX(), future_pos.GetPosY(), 18, 26);
    ManagerTileMap::getInstance()->CheckCollision("collision", position.GetPos(), future_pos.GetPos(), bound, tmp, onGround, gravity);
    position.SetPos(tmp);
    //*/


    ///* Способ 2 Collision
    QRectF bound(future_pos.GetPosX(), future_pos.GetPosY(), 48, 62);
    QVector3D f_p = future_pos.GetPos();
    ManagerTileMap::getInstance()->CollisionX("collision", f_p , bound, dir);
    future_pos.SetPos(f_p);

    if (onGround==false)
    {
        future_pos.MoveY(-gravity);
        dir.setY(-1);
    }

    bound.setLeft(future_pos.GetPosX());
    bound.setTop(future_pos.GetPosY());
    bound.setWidth(48);
    bound.setHeight(62);
    f_p = future_pos.GetPos();
    ManagerTileMap::getInstance()->CollisionY("collision", f_p , bound, dir, gravity, onGround);
    position.SetPos(f_p);
    //*/

    qDebug()<<"onGround:"<<onGround<<" Gravity:"<<gravity;
}

void TestGameObject::Draw()
{
    /*
     * Прорисовка объекта
    */

    sprite->Bind(48, 65, 0, 3);
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * position.GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
