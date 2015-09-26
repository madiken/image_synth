#ifndef POLYGON_H
#define POLYGON_H
#include "primitive.h"

class Polygon
{
private:
    Plane *plane;
public:

    float getDConst();
    vector3 getNormal();


    Polygon(float d, vector3 n, materialConstants m);
    Polygon(float d, vector3 n);

    bool intersect(vector3 d, vector3 eye, float &t);
    vector3 getNormal(vector3 currPoint);
};

#endif // POLYGON_H
