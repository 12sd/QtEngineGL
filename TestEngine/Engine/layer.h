#ifndef LAYER_H
#define LAYER_H

#include <QDebug>
#include <QVector2D>
#include <QRectF>

class Layer
{
public:
    Layer();
    ~Layer();
    void Create(int count_x, int count_y);
    void Destroy();
    void SetValue(int i, int j, int value);
    int GetValue(int i, int j);
private:
    int count_x;
    int count_y;
    int* data;
};

struct DataLayer
{
    QString layer_name;
    Layer* layer;
};

struct Tile
{
    int id;
    QVector2D ij;
    QRectF pos;
};

#endif // LAYER_H
