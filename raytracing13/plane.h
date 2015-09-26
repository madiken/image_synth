

#ifndef PLANE_H
#define PLANE_H
#include "vector3.h"
#include "primitive.h"

class Plane : public Primitive
{
protected:
    float d_const;
    vector3 *normal;

public:

    float getDConst();
    vector3 getNormal();

    Plane(Plane &p);
    Plane(float d, vector3 n, materialConstants m);

    ~Plane();
    bool intersect(vector3 d, vector3 eye, float &t);
    vector3 getNormal(vector3 currPoint);
    vector3 getSurfacePoint(){
        cout << "not implemented" << endl;
        return vector3(0,0,0);
    }
    virtual Rgb getLightLuminance(vector3 currPoint, vector3 objectNormal, vector3 lightPoint){
        cout << "not implemented" << endl;
        return Rgb(0,0,0);
    }


   // Plane::Plane(Plane &p);
};

#endif // PLANE_H
