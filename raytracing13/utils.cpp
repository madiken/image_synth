#include "utils.h"
#include "sphere.h"
#include <iostream>

#include <string>
using namespace std;

Utils::Utils()
{
}

int Utils::round(float d)
{
  return floor(d + 0.5);
}

float Utils::maximum(float a, float b)
{
    if (a > b) return a;
    else return b;
}

float Utils::minimum(float a, float b)
{
    if (a < b) return a;
    else return b;
}

vector3 Utils::vectorMult(vector3 a, vector3 b)
{
        return vector3(a.y * b.z - a.z * b.y,
                       a.z * b.x - a.x * b.z,
                       a.x * b.y - a.y * b.x);
}


