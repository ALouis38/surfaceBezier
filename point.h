#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <ostream>

using namespace std;

class Point
{
public:
    Point(float x, float y, float z);

    float getX() const;
    void setX(float value);

    float getY() const;
    void setY(float value);

    float getZ() const;
    void setZ(float value);

    void afficherPoint();

    string ecrirePoint();

private:
    float x;
    float y;
    float z;
};

#endif // POINT_H
