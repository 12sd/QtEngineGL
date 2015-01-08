#include "setting.h"

QMatrix4x4 Setting::projection;
QRectF Setting::view_port;

Setting::Setting()
{
}

QMatrix4x4 Setting::GetProjection()
{
    return projection;
}

void Setting::SetProjection(QMatrix4x4 proj)
{
    projection = proj;
}

QRectF Setting::GetViewPort()
{
    return view_port;
}

void Setting::SetViewPort(QRectF rect)
{
    view_port = rect;
    glViewport(view_port.x(), view_port.y() ,view_port.width(), view_port.height());
}
