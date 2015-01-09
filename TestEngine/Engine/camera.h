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
    void MoveX(float x);
    void MoveY(float y);
    void MoveZ(float z);
    void MovePos(QVector3D pos);
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
    //Функция возврата результативной матрицы
    QMatrix4x4 GetMatrix();
private:
    static Camera* instance;
    ///////////////////////////////
    QVector3D pos;
    QVector3D rot;
};

#endif // CAMERA_H
