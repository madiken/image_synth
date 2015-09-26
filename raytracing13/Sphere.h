#ifndef Sphere_H
#define Sphere_H
#include "Constants.h"
#include "vector3.h"
#include "math.h"
#include "materialconstants.h"
#include "primitive.h"

#include <fstream>
using namespace std;


class Sphere : public Primitive
{
private:
    float radius;
    vector3 *centre;

public:

    vector3 getNormal(vector3 currPoint);

    vector3 getSurfacePoint();
    virtual Rgb getLightLuminance(vector3 currPoint, vector3 objectNormal, vector3 lightPoint);

    float getRadius();
    vector3 getCentre();


    Sphere(float raduis, int xcentre, int ycentre, int zcentre, materialConstants m);
    Sphere(float raduis, vector3 centre, materialConstants m);
    Sphere(Sphere &s);
    ~Sphere();
    bool intersect(vector3 d, vector3 eye, float &t);
};

#endif // Sphere_H
