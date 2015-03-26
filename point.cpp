#include "point.h"

Point::Point(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
float Point::getX() const
{
    return x;
}

void Point::setX(float value)
{
    x = value;
}
float Point::getY() const
{
    return y;
}

void Point::setY(float value)
{
    y = value;
}
float Point::getZ() const
{
    return z;
}

void Point::setZ(float value)
{
    z = value;
}

void Point::afficherPoint()
{
    cout << "(" << getX() << "," << getY() << "," << getZ() << ")" << endl;
}

string Point::ecrirePoint()
{
   return "v " + to_string(getX()) + " " + to_string(getY()) +" " + to_string(getZ());
}
