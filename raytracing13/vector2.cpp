#include "vector2.h"
#include "math.h"
#include <iostream>
using namespace std;
vector2::vector2()
{
}
vector2::vector2(float x, float y){
    this->x = x;
    this->y = y;
}

vector2::vector2(vector2 &v)
{
    this->x = v.x;
    this->y = v.y;
}

vector2 vector2::operator+(vector2 v)
{
    return vector2(x + v.x, y + v.y);
}

vector2 vector2::operator-(vector2 v)
{
    return vector2(x - v.x, y - v.y);
}


void vector2::rotate(vector2 v, float alpha)
{
    float resx = v.x + (this->x - v.x)*cos(alpha) - (this->y - v.y)*sin(alpha);
    float resy = v.y + (this->x - v.x)*sin(alpha) + (this->y - v.y)*cos(alpha);

    this->x = resx;
    this->y = resy;
}
