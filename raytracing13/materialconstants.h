#ifndef MATERIALCONSTANTS_H
#define MATERIALCONSTANTS_H
#include <QtGui/QImage>
#include <QtGui/QColor>
#include "rgb.h"
class materialConstants
{
private:
    Rgb *color;

public:
   // materialConstants();
    ~materialConstants();
    materialConstants(float refl, float diff, float spec, Rgb col, int type = 0, float phong = 0, float refr = 0);
    materialConstants(Rgb col);
    materialConstants(materialConstants &m);
    float reflectance;
    float diffuse;
    float specular;
    float ambient;//deprecated
    float phong;
    float refraction;
    Rgb getColor(){
        return *color;
    }

    int type; //ambient = 0 glossy = 1 mirror = 2 refracting = 3;
};

#endif // MATERIALCONSTANTS_H
