#ifndef GRIDCOORD_H
#define GRIDCOORD_H

#include <QOpenGLFunctions>
#include <QDebug>

class GridCoord
{
public:
    GridCoord();
    void SetColor(float r, float g, float b);
    //Вызывать последним, выполнив все UnBind()
    void Draw(float left, float right, float bottom, float top, float step = 1.0f);

private:
    float r;
    float g;
    float b;
};

#endif // GRIDCOORD_H
