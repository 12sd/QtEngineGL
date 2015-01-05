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
    this->SetScalX(40);
    this->SetScalY(40);
}

void TestGameObject::Update()
{
    /*
     * Обновление логики, втом числе движение объекта
    */

    Qt::MouseButton button = ManagerMouse::getInstance()->GetButton();
    int x = ManagerMouse::getInstance()->GetX();
    int y = ManagerMouse::getInstance()->GetY();

    if (button == Qt::LeftButton)
    {
        this->SetPosX(x);
        this->SetPosY(512-y);
        ManagerTileMap::getInstance()->GetTiles("collision", this->GetPos());
        qDebug()<<"Pos"<<this->GetPos();
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Right))
    {
        this->MoveX(0.5);
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Left))
    {
        this->MoveX(-0.5);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Up))
    {
        this->MoveY(0.5);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Down))
    {
        this->MoveY(-0.5);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Space) && onGround==true)
    {
        this->MoveY(2);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_A))
    {
        this->RotateZ(-2);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_D))
    {
        this->RotateZ(2);
    }

//    if (onGround==false)
//        this->MoveY(-0.5);

    QVector3D tmp;
    tmp = this->GetPos();
    QRectF bound(this->GetPosX(), this->GetPosY(), 35, 35);
    if (ManagerTileMap::getInstance()->CheckCollision("collision", this->GetPos(), bound, tmp, onGround))
    {
        //ManagerTileMap::getInstance()->CheckCollision("collision", this->GetPos(), bound, tmp);
        qDebug()<<"Collision";
        this->SetPos(tmp);
    }

}

void TestGameObject::Draw()
{
    /*
     * Прорисовка объекта
    */

    sprite->Bind(32, 32, 4, 0);
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
