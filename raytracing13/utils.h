

#include <vector>
#include "vector3.h"
#ifndef UTILS_H
#define UTILS_H

class Utils
{
public:

    Utils();
    static int round(float d);
    static float maximum(float a, float b);
    static float minimum(float a, float b);
    static vector3 vectorMult(vector3 a, vector3 b);

    //needs to have base on the floor


};

#endif // UTILS_H
