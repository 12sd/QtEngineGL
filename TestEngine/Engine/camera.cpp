#include "camera.h"

Camera::Camera()
{
    SetPos(QVector3D(0, 0, 1));
    SetTarget(QVector3D(0, 0, 0));
    type_cam = Free_Camera;
    dist = 1;
}

Camera::~Camera()
{
    qDebug()<<"~Camera";
}

TypeCamera Camera::GetTypeCamera()
{
    return type_cam;
}

void Camera::SetTypeCamera(TypeCamera type)
{
    type_cam = type;
}

QRectF Camera::GetRect()
{
    QRectF rect;
    rect.setLeft(pos.x());
    rect.setTop(pos.y());
    rect.setWidth(Setting::GetViewPort().width());
    rect.setHeight(Setting::GetViewPort().height());
    return rect;
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
    QMatrix4x4 mat_rot;
    mat_rot.setToIdentity();
    mat_rot.rotate(rot.x(), 1, 0, 0);
    mat_rot.rotate(rot.y(), 0, 1, 0);
    mat_rot.rotate(rot.z(), 0, 0, 1);
    QVector3D dir;
    dir.setX(x*mat_rot.column(0).x());
    dir.setY(x*mat_rot.column(1).x());
    dir.setZ(x*mat_rot.column(2).x());
    pos+=dir;
}

void Camera::MoveUp(float y)
{
    QMatrix4x4 mat_rot;
    mat_rot.setToIdentity();
    mat_rot.rotate(rot.x(), 1, 0, 0);
    mat_rot.rotate(rot.y(), 0, 1, 0);
    mat_rot.rotate(rot.z(), 0, 0, 1);
    QVector3D dir;
    dir.setX(y*mat_rot.column(0).y());
    dir.setY(y*mat_rot.column(1).y());
    dir.setZ(y*mat_rot.column(2).y());
    pos+=dir;
}

void Camera::MoveForward(float z)
{
    QMatrix4x4 mat_rot;
    mat_rot.setToIdentity();
    mat_rot.rotate(rot.x(), 1, 0, 0);
    mat_rot.rotate(rot.y(), 0, 1, 0);
    mat_rot.rotate(rot.z(), 0, 0, 1);
    QVector3D dir;
    dir.setX(-z*mat_rot.column(0).z());
    if (type_cam==Free_Camera)
        dir.setY(-z*mat_rot.column(1).z());
    if (type_cam==Direction_Camera) // Для камеры от первого лица
        dir.setY(0);
    dir.setZ(-z*mat_rot.column(2).z());
    pos+=dir;
}

void Camera::MovePos(QVector3D pos)
{
    QMatrix4x4 mat_rot;
    mat_rot.setToIdentity();
    mat_rot.rotate(rot.x(), 1, 0, 0);
    mat_rot.rotate(rot.y(), 0, 1, 0);
    mat_rot.rotate(rot.z(), 0, 0, 1);
    QVector3D dir;
    dir.setX(pos.x()*mat_rot.column(0).x()+pos.y()*mat_rot.column(0).y()-pos.z()*mat_rot.column(0).z());
    if (type_cam==Free_Camera)
        dir.setY(pos.x()*mat_rot.column(1).x()+pos.y()*mat_rot.column(1).y()-pos.z()*mat_rot.column(1).z());
    if (type_cam==Direction_Camera) // Для камеры от первого лица
        dir.setY(pos.y());
    dir.setZ(pos.x()*mat_rot.column(2).x()+pos.y()*mat_rot.column(2).y()-pos.z()*mat_rot.column(2).z());
    this->pos+=dir;
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

void Camera::SetTargetX(float x)
{
    target.setX(x);
}

void Camera::SetTargetY(float y)
{
    target.setY(y);
}

void Camera::SetTargetZ(float z)
{
    target.setZ(z);
}

void Camera::SetTarget(QVector3D target)
{
    this->target.setX(target.x());
    this->target.setY(target.y());
    this->target.setZ(target.z());
}

float Camera::GetTargetX()
{
    return target.x();
}

float Camera::GetTargetY()
{
    return target.y();
}

float Camera::GetTargetZ()
{
    return target.z();
}

QVector3D Camera::GetTarget()
{
    return target;
}

void Camera::SetTargerDist(float dist)
{
    this->dist = dist;
}

float Camera::GetTargetDist()
{
    return dist;
}

//*/Функции для взгляда

///*Функция возврата результативной матрицы

QMatrix4x4 Camera::GetMatrix()
{
    if (rot.x()>360.0)
        rot.setX(rot.x()-360.0);
    if (rot.y()>360.0)
        rot.setY(rot.y()-360.0);
    if (rot.z()>360.0)
        rot.setZ(rot.z()-360.0);
    QMatrix4x4 mat_rot;
    mat_rot.setToIdentity();
    mat_rot.rotate(rot.x(), 1, 0, 0);
    mat_rot.rotate(rot.y(), 0, 1, 0);
    mat_rot.rotate(rot.z(), 0, 0, 1);

    QMatrix4x4 mat_pos;
    mat_pos.setToIdentity();
    if (type_cam==Target_Camera)
    {
        mat_pos.translate(-target.x(), -target.y(), -target.z());
    }else
    {
        mat_pos.translate(-pos.x(), -pos.y(), -pos.z());
    }

    if (type_cam==Target_Camera)
    {
        QMatrix4x4 mat_dop;
        mat_dop.setToIdentity();
        mat_dop.translate(0, 0, -dist);
        QMatrix4x4 mat_res;
        mat_res.setToIdentity();
        mat_res = mat_dop*mat_rot*mat_pos;
        pos.setX(-mat_res.column(3).x());
        pos.setY(-mat_res.column(3).y());
        pos.setZ(-mat_res.column(3).z());
        //qDebug()<<"Pos Camera:"<<pos;
        return mat_res;
    }else
    {
        return mat_rot*mat_pos;
    }
}

//*/Функция возврата результативной матрицы
