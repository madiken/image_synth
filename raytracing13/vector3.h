#ifndef VECTOR3_H
#define VECTOR3_H
#include <iostream>
#include <string>
#include "vector2.h"

using namespace std;
class vector3
{
public:
    float x;
    float y;
    float z;
    vector3(float x, float y, float z);
    vector3();
    ~vector3();
    vector3(vector3 &v);

    vector3 operator+(vector3 vVector);
    vector3 operator+(float num);
    vector3 operator*(float n);
    float operator*(vector3 vVector);
    vector3 operator-(vector3 vVector);    
    vector3 vector3::operator-(float num);
    vector3 operator/(float num);
    vector2 oxzProjection();
    string getString();

    float length();

    vector3 normalize();
};

#endif // VECTOR3_H
