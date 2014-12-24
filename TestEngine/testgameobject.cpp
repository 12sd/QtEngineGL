#include "testgameobject.h"

TestGameObject::TestGameObject()
{
}

void TestGameObject::Init(QHash<QString,QString> property)
{
    /*
     * Инициализация объекта
    */
    pos_x = 0;
    pos_y = 300;
    i = j = 0;
    ground = 200;
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

    int res_x = 0, res_y = 0;
    bool right = true;
    bool up = false;

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
        pos_x+=3;
        right = true;
        i = i + 15 * time;
        if (i > 4)
            i = i -4;
        j = 1;
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Left))
    {
        pos_x-=3;
        right = false;
        i = i + 15 * time;
        if (i > 4)
            i = i -4;
        j = 2;   
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Up))
    {
        pos_y-=3;
        up = true;
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Down))
    {
        pos_y+=3;
        up = false;
    }

    ManagerTileMap::getInstance()->CollisionX("collision", pos_x, pos_y, 48, 65, right, &res_x);
    ManagerTileMap::getInstance()->CollisionY("collision", pos_x, pos_y, 48, 65, up, &res_y);

    if (res_x!=0)
        pos_x = res_x;
    if (res_y!=0)
    pos_y = res_y;

}

void TestGameObject::Draw()
{
    /*
     * Прорисовка объекта
    */
    model.setToIdentity();

    model.translate(pos_x-48/2, 600-pos_y-65/2, 0);
    model.scale(48.0, 65.0);
    qDebug()<<"tmp_X="<<pos_x<<"tmp_Y="<<pos_y;
    qDebug()<<"X="<<model.column(3).x()<<"Y="<<model.column(3).y();

    sprite->Bind(48, 65, int(i), int(j));
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * model);
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
