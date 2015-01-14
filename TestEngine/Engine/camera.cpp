#include "camera.h"

Camera* Camera::instance = 0;

Camera* Camera::getInstance()
{
    if (!instance)
        instance = new Camera();
    return instance;
}


Camera::Camera()
{
    SetPos(QVector3D(0, 0, 1));
    SetDirection(QVector3D(0, 0, -1));
}
/////////////////////////////////////////////////////////////

///*Функции для движения

void Camera::SetPosX(float x)
{
    this->pos.setX(x);
}

void Camera::SetPosY(float y)
{
    this->pos.setY(y);
}

void Camera::SetPosZ(float z)
{
    this->pos.setZ(z);
}

void Camera::SetPos(QVector3D pos)
{
    this->pos.setX(pos.x());
    this->pos.setY(pos.y());
    this->pos.setZ(pos.z());
}

float Camera::GetPosX()
{
    return this->pos.x();
}

float Camera::GetPosY()
{
    return this->pos.y();
}

float Camera::GetPosZ()
{
    return this->pos.z();
}

QVector3D Camera::GetPos()
{
    return this->pos;
}

void Camera::MoveRight(float x)
{

}

void Camera::MoveUp(float y)
{

}

void Camera::MoveForward(float z)
{

}

//*/Функции для движения

///*Функции для вращения

void Camera::SetRotX(float x)
{
    this->rot.setX(x);
}
void Camera::SetRotY(float y)
{
    this->rot.setY(y);
}

void Camera::SetRotZ(float z)
{
    this->rot.setZ(z);
}

void Camera::SetRot(QVector3D rot)
{
    this->rot.setX(rot.x());
    this->rot.setY(rot.y());
    this->rot.setZ(rot.z());
}

float Camera::GetRotX()
{
    return this->rot.x();
}

float Camera::GetRotY()
{
    return this->rot.y();
}

float Camera::GetRotZ()
{
    return this->rot.z();
}

QVector3D Camera::GetRot()
{
    return this->rot;
}

void Camera::RotateX(float x)
{
    this->rot.setX(this->rot.x()+x);
}

void Camera::RotateY(float y)
{
    this->rot.setY(this->rot.y()+y);
}

void Camera::RotateZ(float z)
{
    this->rot.setZ(this->rot.z()+z);
}

void Camera::RotateRot(QVector3D rot)
{
    this->rot.setX(this->rot.x()+rot.x());
    this->rot.setY(this->rot.y()+rot.y());
    this->rot.setZ(this->rot.z()+rot.z());
}

//*/Функции для вращения

///*Функции для взгляда

void Camera::SetDirectionX(float x)
{
    dir.setX(x);
}

void Camera::SetDirectionY(float y)
{
    dir.setY(y);
}

void Camera::SetDirectionZ(float z)
{
    dir.setZ(z);
}

void Camera::SetDirection(QVector3D dir)
{
    this->dir.setX(dir.x());
    this->dir.setY(dir.y());
    this->dir.setZ(dir.z());
}

float Camera::GetDirectionX()
{
    return dir.x();
}

float Camera::GetDirectionY()
{
    return dir.y();
}

float Camera::GetDirectionZ()
{
    return dir.z();
}

QVector3D Camera::GetDirection()
{
    return dir;
}

//*/Функции для взгляда

///*Функция возврата результативной матрицы

QMatrix4x4 Camera::GetMatrix()
{
//    dir.setX(dir.x()*qCos(Geometry::DegreeToRadian(rot.y()))+dir.z()*qSin(Geometry::DegreeToRadian(rot.y())));
//    dir.setY(dir.y());
//    dir.setZ(dir.z()*qCos(Geometry::DegreeToRadian(rot.y()))-dir.x()*qSin(Geometry::DegreeToRadian(rot.y())));

    dir.setX(qCos(Geometry::DegreeToRadian(rot.y()))*qSin(Geometry::DegreeToRadian(rot.x())));
    dir.setY(qSin(Geometry::DegreeToRadian(rot.y())));
    dir.setZ(qCos(Geometry::DegreeToRadian(rot.y()))*qCos(Geometry::DegreeToRadian(rot.x())));

    qDebug()<<"POS,DIR,POS+DIR"<<pos<<dir<<pos+dir;

    QMatrix4x4 mat;
    mat.setToIdentity();
    mat.lookAt(pos, pos+dir, QVector3D(0, 1, 0));
    return mat;
}

//*/Функция возврата результативной матрицы
