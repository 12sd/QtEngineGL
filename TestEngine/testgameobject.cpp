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

    onGround = false;
    gravity = 0.5;
    position.SetScalX(48);
    position.SetScalY(65);
    position.SetPivot(QVector3D(-0.5, -0.5, 0));

    Camera::getInstance()->SetPosZ(1);
}

void TestGameObject::Update()
{
    /*
     * Обновление логики, втом числе движение объекта
    */
    float time = 1.0/Fps::getInstance()->GetFps();
    gravity += 0.5;
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
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Right))
    {
        position.MoveX(8);
        dir.setX(1);
        qDebug()<<"MatPos:"<<position.GetMatrix();
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Left))
    {
        position.MoveX(-8);
        dir.setX(-1);
        qDebug()<<"MatPos:"<<position.GetMatrix();
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_A))
    {
        Camera::getInstance()->MoveX(-1);
        qDebug()<<"Scroll -x";
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_D))
    {
        Camera::getInstance()->MoveX(1);
        qDebug()<<"Scroll +x";
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_W))
    {
        Camera::getInstance()->MoveY(1);
        qDebug()<<"Scroll -y";
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_S))
    {
        Camera::getInstance()->MoveY(-1);
        qDebug()<<"Scroll +y";
    }



    ///* Collision
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
        position.MoveY(32);
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

    //qDebug()<<"onGround:"<<onGround<<" Gravity:"<<gravity;
}

void TestGameObject::Draw()
{
    /*
     * Прорисовка объекта
    */

    sprite->Bind(48, 65, 0, 3);
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*Camera::getInstance()->GetMatrix()*position.GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
