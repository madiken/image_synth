
#include "Constants.h"

#include "plane.h"
#include "primitive.h"
#include <iostream>

#include "randutils.h"
#ifndef MyRectangle_H
#define MyRectangle_H

class MyRectangle : public Primitive
{

private:
    vector3 *edge1;
    vector3 *edge2;
    vector3 *edge3;
    vector3 *edge4;//edge4 against edge2!!! is calculated in cinstructor
   // vector3 *normal;
    Plane *plane;

public:
    bool intersect(vector3 d, vector3 eye, float &t);
    vector3 getSurfacePoint();
    vector3 getNormal(vector3 currPoint);
    vector3 getNormal();


    //specific
    MyRectangle(vector3 edge1, vector3 edge2, vector3 edge3,  materialConstants m);
    MyRectangle(MyRectangle &r);
    ~MyRectangle();
    vector3 getEdge1();
    vector3 getEdge2();
    vector3 getEdge3();
    vector3 getEdge4();

    void setEdge1(vector3 v);
    void setEdge2(vector3 v);
    void setEdge3(vector3 v);
    void setEdge4(vector3 v);

    float MyRectangle::getSquare();
    Plane getPlane();
    Rgb  getLightLuminance(vector3 currPoint, vector3 objectNormal, vector3 lightPoint);




};

#endif // MyRectangle_H
