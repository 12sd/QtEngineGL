#include "testgameobject.h"

TestGameObject::TestGameObject()
{
}

void TestGameObject::Init()
{
    /*
     * Инициализация объекта
    */
    i = j = 0;
    ground = 150;
    onGround = false;
    sprite = ManagerSprite::getInstance()->GetValue(0);
    proj.setToIdentity();
    proj.ortho(0, 800, 0, 600, -1, 1);
    model.setToIdentity();
    model.scale(48.0, 65.0);
    model.translate(0.5, 0.5, 0);
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
        model.setToIdentity();
        model.translate(x,600-y,0);
        model.scale(48.0, 65.0);
        onGround = false;
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Right))
    {
        ManagerTileMap::getInstance()->Scroll(-22 * time);
        model.translate(3.0 * time, 0, 0);
        qDebug()<<"move right";
        i = i + 30 * time;
        if (i > 4)
            i = i -4;
        j = 1;
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Left))
    {
        ManagerTileMap::getInstance()->Scroll(22 * time);
        model.translate(-3.0 * time, 0, 0);
        qDebug()<<"move left";
        i = i + 30 * time;
        if (i > 4)
            i = i -4;
        j = 2;
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Space))
    {
        model.translate(0, 100.0 * time, 0);
        onGround = false;
        qDebug()<<"MatY"<<model.column(3).y()<<"onGround"<<onGround;
        ManagerKeyboard::getInstance()->Update(ManagerKeyboard::getInstance()->GetEvent(), false);
    }

    if (!onGround)
    {
        model.translate(0, -6.0 * time, 0);
    }

    if (model.column(3).y()<ground)
    {
        model.row(3).setY(ground);
        onGround = true;
    }
}

void TestGameObject::Draw()
{
    /*
     * Прорисовка объекта
    */
    sprite->Bind(48, 65, int(i), int(j));
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * model);
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
