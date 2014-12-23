#ifndef LAYER_H
#define LAYER_H

#include <QDebug>

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

#endif // LAYER_H
