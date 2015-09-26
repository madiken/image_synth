#include "materialmodel.h"
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <math.h>

float max(float t1, float t2)
{
    if (t1 > t2) return t1;
    return t2;
}

materialModel::materialModel()
{


}


float materialModel::calculateSpecular(vector3 currPoint, vector3 lightPos, vector3 normal, vector3 eye)
{

    vector3 v = eye - currPoint;
    v = v.normalize();

    vector3 r = normal*(normal*v)*2 - v;
    r = r.normalize();
    float koef = 0;
        vector3 l = lightPos - currPoint;
        l = l.normalize();
        koef += max(0.0f, (l*r)*(l*r)*(l*r)*(l*r)*(l*r));
        return koef;
}


float materialModel::calculateDiffuse(vector3 currPoint, vector3 light, vector3 normal)

{
    vector3 lightDirection = light - currPoint;
    lightDirection = lightDirection.normalize();
    float koef =  max(0.0f, (normal*lightDirection)*(normal*lightDirection));
    return koef;
}


