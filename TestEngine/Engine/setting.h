#ifndef SETTING_H
#define SETTING_H

#include <QOpenGLFunctions>
#include <QMatrix4x4>

class Setting
{
public:
    Setting();
    static QMatrix4x4 GetProjection();
    static void SetProjection(QMatrix4x4 proj);
    static QRectF GetViewPort();
    static void SetViewPort(QRectF rect);
private:
    static QMatrix4x4 projection;
    static QRectF view_port;
};

#endif // SETTING_H
