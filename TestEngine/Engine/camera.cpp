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

///*Функции для масшабирования

void Camera::SetScalX(float x)
{
    this->scal.setX(x);
}

void Camera::SetScalY(float y)
{
    this->scal.setY(y);
}

void Camera::SetScalZ(float z)
{
    this->scal.setZ(z);
}
void Camera::SetScal(QVector3D scal)
{
    this->scal.setX(scal.x());
    this->scal.setY(scal.y());
    this->scal.setZ(scal.z());
}

float Camera::GetScalX()
{
    return this->scal.x();
}

float Camera::GetScalY()
{
    return this->scal.y();
}

float Camera::GetScalZ()
{
    return this->scal.z();
}
QVector3D Camera::GetScal()
{
    return this->scal;
}

void Camera::ScaleX(float x)
{
    this->scal.setX(this->scal.x()+x);
}

void Camera::ScaleY(float y)
{
    this->scal.setY(this->scal.y()+y);
}

void Camera::ScaleZ(float z)
{
    this->scal.setZ(this->scal.z()+z);
}

void Camera::ScaleScal(QVector3D scal)
{
    this->scal.setX(this->scal.x()+scal.x());
    this->scal.setY(this->scal.y()+scal.y());
    this->scal.setZ(this->scal.z()+scal.z());
}

//*/Функции для масшабирования


///*Функции для точки-центра отрисовки
float Camera::GetPivotX()
{
    return pivot.x();
}

float Camera::GetPivotY()
{
    return pivot.y();
}
float Camera::GetPivotZ()
{
    return pivot.z();
}
QVector3D Camera::GetPivot()
{
    return pivot;
}

void Camera::SetPivotX(float x)
{
    pivot.setX(x);
}

void Camera::SetPivotY(float y)
{
    pivot.setY(y);
}

void Camera::SetPivotZ(float z)
{
    pivot.setZ(z);
}

void Camera::SetPivot(QVector3D pivot)
{
    this->pivot.setX(pivot.x());
    this->pivot.setY(pivot.y());
    this->pivot.setZ(pivot.z());
}

//*/Функции для точки-центра отрисовки

///*Функция возврата результативной матрицы

QMatrix4x4 Camera::GetMatrix()
{
    QMatrix4x4 mat_pos;
    mat_pos.setToIdentity();
    mat_pos.translate(this->pos);

    QMatrix4x4 mat_rot;
    mat_rot.setToIdentity();
//    mat_rot.rotate(this->rot.x(), 1, 0);
//    mat_rot.rotate(this->rot.y(), 0, 1);
//    mat_rot.rotate(this->rot.z(), 0, 0, 1);

    QMatrix4x4 mat_scal;
    mat_scal.setToIdentity();
    //mat_scal.scale(this->scal);

    //return mat_pos*mat_rot*mat_scal;

    QMatrix4x4 mat;
    mat.setToIdentity();
    mat.lookAt(pos, QVector3D(pos.x(), 0, -1), QVector3D(pos.x(), 1, 0));
    return mat;
}

//*/Функция возврата результативной матрицы
