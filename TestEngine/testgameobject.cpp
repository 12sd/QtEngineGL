#include "testgameobject.h"

TestGameObject::TestGameObject()
{
}

void TestGameObject::Init(QHash<QString,QString> property)
{
    /*
     * Инициализация объекта
    */
    i = j = 0;
    sprite = ManagerSprite::getInstance()->GetValue(0);
    proj.setToIdentity();
    proj.ortho(0, 800, 0, 600, -1, 1);

    this->SetScalX(48);
    this->SetScalY(65);
    this->SetPosX(48);
    this->SetPosY(600-65);
    this->SetRotZ(0);
}

void TestGameObject::Update()
{
    /*
     * Обновление логики, втом числе движение объекта
    */
    float time = 1.0f/Fps::getInstance()->GetFps();
    j = 3;

    Qt::MouseButton button = ManagerMouse::getInstance()->GetButton();
    int x = ManagerMouse::getInstance()->GetX();
    int y = ManagerMouse::getInstance()->GetY();

    if (button == Qt::LeftButton)
    {
        this->SetPosX(x);
        this->SetPosY(600-y);
        QVector3D t = this->GetPos();
        t.setX(t.x()-48.0/2.0);
        t.setY(t.y()-65.0/2.0);
        ManagerTileMap::getInstance()->GetTiles("collision", this->GetPos());
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Right))
    {
        this->MoveX(120*time);

        i = i + 15 * time;
        if (i > 4)
            i = i -4;
        j = 1;
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Left))
    {
        this->MoveX(-120*time);

        i = i + 15 * time;
        if (i > 4)
            i = i -4;
        j = 2;   
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Up))
    {
        this->MoveY(120*time);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Down))
    {
        this->MoveY(-120*time);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_A))
    {
        this->RotateZ(-120*time);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_D))
    {
        this->RotateZ(120*time);
    }

    QVector3D tmp;
    QRectF bound(this->GetPosX(), this->GetPosY(), 48, 65);
    if (ManagerTileMap::getInstance()->CheckCollision("collision", this->GetPos(), bound, tmp))
    {
        qDebug()<<"Collision";
        this->SetPos(tmp);
    }

}

void TestGameObject::Draw()
{
    /*
     * Прорисовка объекта
    */

    sprite->Bind(48, 65, int(i), int(j));
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
