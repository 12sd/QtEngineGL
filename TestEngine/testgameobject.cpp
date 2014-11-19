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
    sprite = ManagerSprite::getInstance()->GetValue(0);
    proj.setToIdentity();
    proj.ortho(0, 800, 0, 600, -1, 1);
    model.setToIdentity();
    model.scale(48.0/2, 65.0/2);
    model.translate(1, 1, 0);
}

void TestGameObject::Update()
{
    /*
     * Обновление логики, втом числе движение объекта
    */
    Qt::MouseButton button = ManagerMouse::getInstance()->GetButton();
    int x = ManagerMouse::getInstance()->GetX();
    int y = ManagerMouse::getInstance()->GetY();
//    if (last_x!=x || last_y!=y)
//    {
//        last_x = x;
//        last_y = y;
//        i++;
//        if (i == 4)
//            i = 0;
//    }
    if (button == Qt::LeftButton)
    {
        qDebug()<<"j++";
        j++;
        if (j == 4)
            j = 0;
        model.setToIdentity();
        model.translate(x,600-y,0);
        model.scale(48.0/2, 65.0/2);
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Right))
    {
        model.translate(0.1,0,0);
        qDebug()<<"move right";
        i++;
        if (i == 4)
            i = 0;
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Left))
    {
        model.translate(-0.1,0,0);
        qDebug()<<"move left";
        i++;
        if (i == 4)
            i = 0;
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Up))
    {
        model.translate(0,0.1,0);
        qDebug()<<"move up";
        i++;
        if (i == 4)
            i = 0;
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Down))
    {
        model.translate(0,-0.1,0);
        qDebug()<<"move down";
        i++;
        if (i == 4)
            i = 0;
    }
}

void TestGameObject::Draw()
{
    /*
     * Прорисовка объекта
    */
    sprite->Bind(48, 65, i, j);
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * model);
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
