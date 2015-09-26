#include "materialconstants.h"
/*
materialConstants::materialConstants()
{
}
*/

materialConstants::materialConstants(float refl, float diff, float spec, Rgb col,  int t, float ph, float refr)

{
    reflectance = refl;
    diffuse = diff;
    specular = spec;
    color = new Rgb(col);
    refraction = refr;
    phong = ph;
    type = t;
}

materialConstants::materialConstants( Rgb col)

{
    reflectance = 0;
    diffuse = 0;
    specular = 0;
    refraction = 0;
    color = new Rgb(col);
    phong = 0;
    type = 0;
}

materialConstants::materialConstants(materialConstants &m)
{
    reflectance = m.reflectance;
    diffuse = m.diffuse;
    specular = m.specular;
    color = new Rgb(m.getColor());
    type = m.type;
    phong = m.phong;
    refraction = m.refraction;
}


materialConstants::~materialConstants()
{
    delete color;
}
