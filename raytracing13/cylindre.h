#ifndef CYLINDRE_H
#define CYLINDRE_H
#include <QtGui/QImage>

#include "primitive.h"
#include "plane.h"
#include "vector3.h"
#include "projectionpane.h"
#include "rgb.h"



#include "Constants.h"
#include "math.h"
#include "utils.h"
class cylindre : public Primitive
{

private :
    vector3 *position;
    vector3 *normal;

    Plane *upper;
    Plane *lower;

    ProjectionPane *texture;

    vector3 *textureStart;
    vector3 *textureStartRotatedHalfPii;
public:
    cylindre(int h, vector3 n, vector3  coords, int rad, materialConstants m);
    cylindre(cylindre &c);
    ~cylindre();
    float height;

    int radius;



    Rgb getTextureColor(vector3 currPoint);
    bool pointBetweenBases(vector3 point);


    bool intersect(vector3 d, vector3 eye, float &t);
    vector3 getNormal(vector3 currPoint);
    Rgb getColor(vector3 currPoint);

    vector3 getSurfacePoint();
    Rgb getLightLuminance(vector3 currPoint, vector3 objectNormal, vector3 lightPoint);

    vector3 getNormal();
    Plane getUpper();
    Plane getLower();
    vector3 getTextuteStart();
    vector3 getTextureStartRotatedHalfPii();
    vector3 getPosition();

    ProjectionPane *getTexture();
    void setTexture(ProjectionPane p);
    void setTexture(QImage im);


    bool baseintersect(vector3 d, vector3 eye, float  &t);
    bool baseintersect_m(vector3 d, vector3 eye, float  &t);

};

#endif // CYLINDRE_H
