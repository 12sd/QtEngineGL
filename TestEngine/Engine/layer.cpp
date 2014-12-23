#include "layer.h"

Layer::Layer()
{
    data = 0;
    count_x = count_y = 0;
}

Layer::~Layer()
{
    Destroy();
    qDebug()<<"~Layer";
}

void Layer::Create(int count_x, int count_y)
{
    this->count_x = count_x;
    this->count_y = count_y;
    data = new int [count_x*count_x];
}

void Layer::Destroy()
{
    if (data!=0)
    {
        delete[] data;
        data = 0;
    }
}

void Layer::SetValue(int i, int j, int value)
{
    if (data!=0)
    {
        data[i*count_x+j] = value;
    }
}

int Layer::GetValue(int i, int j)
{
    if (data!=0)
    {
        return data[i*count_x+j];
    }
    return 0;
}
