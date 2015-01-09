#include "geometry.h"

Geometry::Geometry()
{
}

float Geometry::DegreeToRadian(float degree)
{
    return degree*M_PI/180.0;
}

float Geometry::RadianToDegree(float radian)
{
    return radian*180.0/M_PI;
}
