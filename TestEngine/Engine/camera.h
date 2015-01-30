#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include "geometry.h"
#include "setting.h"

enum TypeCamera {Free_Camera, Direction_Camera, Target_Camera};

class Camera
{
public:
    Camera();
    ~Camera();
    TypeCamera GetTypeCamera();
    void SetTypeCamera(TypeCamera type);
    QRectF GetRect();
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
    //Функции для взгляда
    void SetTargetX(float x);
    void SetTargetY(float y);
    void SetTargetZ(float z);
    void SetTarget(QVector3D target);
    float GetTargetX();
    float GetTargetY();
    float GetTargetZ();
    QVector3D GetTarget();
    void SetTargerDist(float dist);
    float GetTargetDist();
    //Функция возврата результативной матрицы
    QMatrix4x4 GetMatrix();
private:
    TypeCamera type_cam;
    QVector3D pos;
    QVector3D rot;
    QVector3D target;
    float dist;
};

#endif // CAMERA_H
