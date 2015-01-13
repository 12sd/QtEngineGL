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

void Camera::MoveX(float x)
{
    this->pos.setX(this->pos.x()+x);
}

void Camera::MoveY(float y)
{
    this->pos.setY(this->pos.y()+y);
}

void Camera::MoveZ(float z)
{
    this->pos.setZ(this->pos.z()+z);
}

void Camera::MovePos(QVector3D pos)
{
    this->pos.setX(this->pos.x()+pos.x());
    this->pos.setY(this->pos.y()+pos.y());
    this->pos.setZ(this->pos.z()+pos.z());
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

///*Функция возврата результативной матрицы

QMatrix4x4 Camera::GetMatrix()
{
    QVector3D dir(0, 0, 0);
    QMatrix4x4 mat_rot;
    mat_rot.setToIdentity();
    mat_rot.rotate(Geometry::DegreeToRadian(rot.x()), 1, 0);
    mat_rot.rotate(Geometry::DegreeToRadian(rot.y()), 0, 1);
    mat_rot.rotate(Geometry::DegreeToRadian(rot.z()), 0, 0, 1);
    dir = mat_rot*dir;
    //qDebug()<<"Dir"<<pos+dir;

    QMatrix4x4 mat;
    mat.setToIdentity();
    mat.lookAt(pos, QVector3D(pos.x(), pos.y(), 0), QVector3D(0, 1, 0));
    return mat;
}

//*/Функция возврата результативной матрицы
