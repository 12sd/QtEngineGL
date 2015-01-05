#include "transformer.h"

Transformer::Transformer()
{

}

///*Функции для движения

void Transformer::SetPosX(float x)
{
    this->pos.setX(x);
}

void Transformer::SetPosY(float y)
{
    this->pos.setY(y);
}

void Transformer::SetPosZ(float z)
{
    this->pos.setZ(z);
}

void Transformer::SetPos(QVector3D pos)
{
    this->pos.setX(pos.x());
    this->pos.setY(pos.y());
    this->pos.setZ(pos.z());
}

float Transformer::GetPosX()
{
    return this->pos.x();
}

float Transformer::GetPosY()
{
    return this->pos.y();
}

float Transformer::GetPosZ()
{
    return this->pos.z();
}

QVector3D Transformer::GetPos()
{
    return this->pos;
}

void Transformer::MoveX(float x)
{
    this->pos.setX(this->pos.x()+x);
}

void Transformer::MoveY(float y)
{
    this->pos.setY(this->pos.y()+y);
}

void Transformer::MoveZ(float z)
{
    this->pos.setZ(this->pos.z()+z);
}

void Transformer::MovePos(QVector3D pos)
{
    this->pos.setX(this->pos.x()+pos.x());
    this->pos.setY(this->pos.y()+pos.y());
    this->pos.setZ(this->pos.z()+pos.z());
}

//*/Функции для движения

///*Функции для вращения

void Transformer::SetRotX(float x)
{
    this->rot.setX(x);
}
void Transformer::SetRotY(float y)
{
    this->rot.setY(y);
}

void Transformer::SetRotZ(float z)
{
    this->rot.setZ(z);
}

void Transformer::SetRot(QVector3D rot)
{
    this->rot.setX(rot.x());
    this->rot.setY(rot.y());
    this->rot.setZ(rot.z());
}

float Transformer::GetRotX()
{
    return this->rot.x();
}

float Transformer::GetRotY()
{
    return this->rot.y();
}

float Transformer::GetRotZ()
{
    return this->rot.z();
}

QVector3D Transformer::GetRot()
{
    return this->rot;
}

void Transformer::RotateX(float x)
{
    this->rot.setX(this->rot.x()+x);
}

void Transformer::RotateY(float y)
{
    this->rot.setY(this->rot.y()+y);
}

void Transformer::RotateZ(float z)
{
    this->rot.setZ(this->rot.z()+z);
}

void Transformer::RotateRot(QVector3D rot)
{
    this->rot.setX(this->rot.x()+rot.x());
    this->rot.setY(this->rot.y()+rot.y());
    this->rot.setZ(this->rot.z()+rot.z());
}

//*/Функции для вращения

///*Функции для масшабирования

void Transformer::SetScalX(float x)
{
    this->scal.setX(x);
}

void Transformer::SetScalY(float y)
{
    this->scal.setY(y);
}

void Transformer::SetScalZ(float z)
{
    this->scal.setZ(z);
}
void Transformer::SetScal(QVector3D scal)
{
    this->scal.setX(scal.x());
    this->scal.setY(scal.y());
    this->scal.setZ(scal.z());
}

float Transformer::GetScalX()
{
    return this->scal.x();
}

float Transformer::GetScalY()
{
    return this->scal.y();
}

float Transformer::GetScalZ()
{
    return this->scal.z();
}
QVector3D Transformer::GetScal()
{
    return this->scal;
}

void Transformer::ScaleX(float x)
{
    this->scal.setX(this->scal.x()+x);
}

void Transformer::ScaleY(float y)
{
    this->scal.setY(this->scal.y()+y);
}

void Transformer::ScaleZ(float z)
{
    this->scal.setZ(this->scal.z()+z);
}

void Transformer::ScaleScal(QVector3D scal)
{
    this->scal.setX(this->scal.x()+scal.x());
    this->scal.setY(this->scal.y()+scal.y());
    this->scal.setZ(this->scal.z()+scal.z());
}

//*/Функции для масшабирования

///*Функция возврата результативной матрицы

QMatrix4x4 Transformer::GetMatrix()
{
    QMatrix4x4 mat_pos;
    mat_pos.setToIdentity();
    mat_pos.translate(this->pos);
    QMatrix4x4 mat_rot;
    mat_rot.setToIdentity();
    mat_rot.rotate(this->rot.x(), 1, 0);
    mat_rot.rotate(this->rot.y(), 0, 1);
    mat_rot.rotate(this->rot.z(), 0, 0, 1);
    QMatrix4x4 mat_scal;
    mat_scal.setToIdentity();
    mat_scal.scale(this->scal);
    return mat_pos*mat_rot*mat_scal;
}

//*/Функция возврата результативной матрицы