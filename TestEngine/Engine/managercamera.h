#ifndef MANAGERCAMERA_H
#define MANAGERCAMERA_H

#include <QHash>
#include "camera.h"

class ManagerCamera
{
public:
    ManagerCamera();
    ~ManagerCamera();
    static ManagerCamera* getInstance();
    void Add(QString key, Camera* value);
    Camera* GetValue(QString key);
    Camera* GetCurrentCamera();
    void SetCurrentCamera(QString key);
    void Clear();
    void Destroy();
private:
    static ManagerCamera* instance;
    QHash<QString, Camera*> hash_tab;
    Camera* current;
};

#endif // MANAGERCAMERA_H
