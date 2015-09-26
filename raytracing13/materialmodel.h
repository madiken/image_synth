#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include "vector3.h"
class materialModel
{
public:
    materialModel();

    float calculateSpecular(vector3 currPoint, vector3 lightPos, vector3 normal, vector3 eye);
    float calculateDiffuse(vector3 currPoint, vector3 light, vector3 normal);
};

#endif // MATERIALMODEL_H
