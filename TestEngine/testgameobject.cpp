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
    ground = 200;
    onGround = false;
    sprite = ManagerSprite::getInstance()->GetValue(0);
    proj.setToIdentity();
    proj.ortho(0, 800, 0, 600, -1, 1);
    model.setToIdentity();
    model.scale(32.0, 32.0);
    model.translate(0.5, 0.5, 0);
}

void TestGameObject::Update()
{
    /*
     * Обновление логики, втом числе движение объекта
    */
    float time = 1.0f/Fps::getInstance()->GetFps();
    j = 3;

    QVector2D pos;
    QVector2D res_pos;
    bool right = true;
    bool up = false;


    Qt::MouseButton button = ManagerMouse::getInstance()->GetButton();
    int x = ManagerMouse::getInstance()->GetX();
    int y = ManagerMouse::getInstance()->GetY();

    if (button == Qt::LeftButton)
    {
        model.setToIdentity();
        model.translate(x,600-y,0);
        model.scale(32.0, 32.0);
        onGround = false;
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Right))
    {
        model.translate(3.0*time, 0, 0);
        right = true;
        i = i + 30 * time;
        if (i > 4)
            i = i -4;
        j = 1;
    }
    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Left))
    {
        model.translate(-3*time, 0, 0);
        right = false;
        i = i + 30 * time;
        if (i > 4)
            i = i -4;
        j = 2;   
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Up))
    {
        model.translate(0, 3*time, 0);
        up = true;
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Down))
    {
        model.translate(0, -3*time, 0);
        up = false;
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Space))
    {
        model.translate(0, 100.0 * time, 0);
        onGround = false;
        qDebug()<<"MatY"<<model.column(3).y()<<"onGround"<<onGround;
        ManagerKeyboard::getInstance()->Update(ManagerKeyboard::getInstance()->GetEvent(), false);
    }

    pos.setX(model.column(3).x());
    pos.setY(model.column(3).y());
    qDebug()<<"PosX"<<pos.x()<<"PosY"<<pos.y();

    if (ManagerTileMap::getInstance()->CollisionX("collision", pos, 32, 32, right, &res_pos))
    {
        model.setToIdentity();
        model.translate(res_pos.x(), pos.y(), 0);
        model.scale(32.0, 32.0);
        qDebug()<<"COLLISION X="<<res_pos.x()<<" Y="<<res_pos.y();
    }

    pos.setX(model.column(3).x());
    pos.setY(model.column(3).y());
    qDebug()<<"PosX"<<pos.x()<<"PosY"<<pos.y();

    if (ManagerTileMap::getInstance()->CollisionY("collision", pos, 32, 32, up, &res_pos))
    {
        model.setToIdentity();
        model.translate(pos.x(), res_pos.y(), 0);
        model.scale(32.0, 32.0);
        qDebug()<<"COLLISION Y="<<res_pos.x()<<" Y="<<res_pos.y();
    }

//    if (!onGround)
//    {
//        model.translate(0, -3.0 * time, 0);
//    }

//    if (ManagerTileMap::getInstance()->CollisionY("collision", pos, 48, 65, onGround, &res_pos) && onGround==false)
//    {
//        model.setToIdentity();
//        model.translate(pos.x(), res_pos.y(), 0);
//        model.scale(48.0, 65.0);
//        qDebug()<<"COLLISION X="<<res_pos.x()<<" Y="<<res_pos.y();
//        onGround = true;
//    }
}

void TestGameObject::Draw()
{
    /*
     * Прорисовка объекта
    */
    sprite->Bind(32, 32, int(i), int(j));
    sprite->GetShader()->setUniformValue(sprite->GetShader()->GetNameMatrixPos().toStdString().c_str(), proj * model);
    glDrawArrays(GL_TRIANGLES, 0, sprite->GetMesh()->GetCountVertex());
}
