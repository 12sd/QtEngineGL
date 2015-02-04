#include "testgameobject.h"

TestGameObject::TestGameObject()
{
}

void TestGameObject::Init(QHash<QString,QString> property)
{
    /*
     * Инициализация объекта
    */

    qDebug()<<"Property GameObject 'TestGameObject':";
    QHash<QString, QString>::iterator it = property.begin();
    while (it != property.end())
    {
        qDebug()<<"Key:"<<it.key()<<"Value:"<<it.value();
        it++;
    }


    sprite = ManagerSprite::getInstance()->GetValue(1);

    onGround = false;
    gravity = 0.5;
    SetScalX(48);
    SetScalY(65);
    SetPivot(QVector3D(0.5, 0.5, 0));
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
        SetPosX(x);
        SetPosY(600-y);
        onGround = false;
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Right))
    {
        MoveX(8);
        dir.setX(1);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Left))
    {
        MoveX(-8);
        dir.setX(-1);
    }



    ///* Collision
    QRectF bound(GetPosX()-48/2, GetPosY()-65/2, 48, 62);
    //QRectF bound(GetPosX(), GetPosY(), 48, 62);
    QVector3D f_p = GetPos();
    ManagerTileMap::getInstance()->CollisionX("collision", f_p, bound, dir);
    SetPos(f_p);

    if (onGround==false)
    {
        MoveY(-gravity);
        dir.setY(-1);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Space) && onGround==true)
    {
        MoveY(32);
        dir.setY(1);
        onGround = false;
    }

    f_p = GetPos();
    bound.setLeft(GetPosX()-48/2);
    bound.setTop(GetPosY()-65/2);
    //bound.setLeft(GetPosX());
    //bound.setTop(GetPosY());
    bound.setWidth(48);
    bound.setHeight(62);
    ManagerTileMap::getInstance()->CollisionY("collision", f_p, bound, dir, gravity, onGround);
    SetPos(f_p);
    //*/

    //qDebug()<<"onGround:"<<onGround<<" Gravity:"<<gravity;
}

void TestGameObject::Draw()
{
    /*
     * Прорисовка объекта
    */

    sprite->Bind(48, 65, 0, 3);
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), Setting::GetProjection()*ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix()*GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
    sprite->UnBind();
    sprite->GetShader()->release();
}
