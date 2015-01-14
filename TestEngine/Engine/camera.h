#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include "geometry.h"

class Camera
{
public:
    static Camera* getInstance();
    Camera();
    ///////////////////////////////
    //Функции для движения
    void SetPosX(float x);
    void SetPosY(float y);
    void SetPosZ(float z);
    void SetPos(QVector3D pos);
    float GetPosX();
    float GetPosY();
    float GetPosZ();
    QVector3D GetPos();
    void MoveRight(float x);
    void MoveUp(float y);
    void MoveForward(float z);
    //Функции для вращения
    void SetRotX(float x);
    void SetRotY(float y);
    void SetRotZ(float z);
    void SetRot(QVector3D rot);
    float GetRotX();
    float GetRotY();
    float GetRotZ();
    QVector3D GetRot();
    void RotateX(float x);
    void RotateY(float y);
    void RotateZ(float z);
    void RotateRot(QVector3D rot);
    //Функции для взгляда
    void SetDirectionX(float x);
    void SetDirectionY(float y);
    void SetDirectionZ(float z);
    void SetDirection(QVector3D dir);
    float GetDirectionX();
    float GetDirectionY();
    float GetDirectionZ();
    QVector3D GetDirection();
    //Функция возврата результативной матрицы
    QMatrix4x4 GetMatrix();
private:
    static Camera* instance;
    ///////////////////////////////
    QVector3D pos;
    QVector3D rot;
    QVector3D dir;
};

#endif // CAMERA_H
