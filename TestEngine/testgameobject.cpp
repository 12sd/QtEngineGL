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
    position.SetPivot(QVector3D(-0.5, -0.5, 0));
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

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Right))
    {
        position.MoveX(8);
        dir.setX(1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Left))
    {
        position.MoveX(-8);
        dir.setX(-1);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_A))
    {
        position.RotateZ(1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_D))
    {
        position.RotateZ(-1);
    }


    /* Способ 1 Collision
    QVector3D tmp;
    QRectF bound(future_pos.GetPosX(), future_pos.GetPosY(), 18, 26);
    ManagerTileMap::getInstance()->CheckCollision("collision", position.GetPos(), future_pos.GetPos(), bound, tmp, onGround, gravity);
    position.SetPos(tmp);
    //*/


    ///* Способ 2 Collision
    QRectF bound(position.GetPosX()-48/2, position.GetPosY()-65/2, 48, 62);
    QVector3D f_p = position.GetPos();
    ManagerTileMap::getInstance()->CollisionX("collision", f_p, bound, dir);
    position.SetPos(f_p);

    if (onGround==false)
    {
        position.MoveY(-gravity);
        dir.setY(-1);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Space) && onGround==true)
    {
        position.MoveY(64);
        dir.setY(1);
        onGround = false;
    }

    f_p = position.GetPos();
    bound.setLeft(position.GetPosX()-48/2);
    bound.setTop(position.GetPosY()-65/2);
    bound.setWidth(48);
    bound.setHeight(62);
    ManagerTileMap::getInstance()->CollisionY("collision", f_p, bound, dir, gravity, onGround);
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
