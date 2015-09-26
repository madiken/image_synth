#include "Sphere.h"
#include <fstream>

#include <QtDebug>

vector3 Sphere::getSurfacePoint(){
    cout << "not implemented" << endl;
    return vector3(0,0,0);
}
Rgb Sphere::getLightLuminance(vector3 currPoint, vector3 objectNormal, vector3 lightPoint){
    cout << "not implemented" << endl;
    return Rgb(0,0,0);
}
Sphere::Sphere(float r, int xcentre, int ycentre, int zcentre, materialConstants m) : Primitive(m)
{
    radius = r;
    centre = new vector3(xcentre, ycentre, zcentre);
}

Sphere::Sphere(float r, vector3 c, materialConstants m) : Primitive(m)
{
    radius = r;
    centre = new vector3(c);
}



Sphere::Sphere(Sphere &s): Primitive(s.getMaterial())
{
    radius = s.getRadius();
    centre = new vector3(s.getCentre());
}

Sphere::~Sphere()
{
    cout << "delete sphere started" << endl;
    delete centre;
    cout << "delete sphere finished" << endl;
}


float Sphere::getRadius()
{
    return radius;
}

vector3 Sphere::getCentre()
{
    return *centre;
}


vector3 Sphere::getNormal(vector3 currPoint)
{
    vector3 no = currPoint - *centre;
    no = no.normalize();
    return no;
}


bool Sphere::intersect(vector3 d, vector3 eye, float &t)
{
    float t1, t2;


    float rad = radius;


              float x0 = centre->x;
              float y0 = centre->y;
              float z0 = centre->z;

              float a = d.x*d.x + d.y*d.y + d.z*d.z;
              float b = 2*(d.x*eye.x + d.y*eye.y + d.z*eye.z - d.x*x0 - d.y*y0 - d.z*z0);
              float c = eye.x*eye.x + eye.y*eye.y + eye.z*eye.z  + x0*x0  + y0*y0 + z0*z0
                        - 2*(eye.x*x0 + eye.y*y0 + eye.z*z0)
                        - rad*rad;


              bool boo = sqrUravn(a, b, c, t1, t2);

              if (boo){
                  if ((t1 > PRECISION) && (t2 > PRECISION)){
                  t = min (t1, t2);
                   if (t > PRECISION)
                    return true;
                  }

                  if (t1 * t2 < PRECISION){
                    t = max(t1, t2);
                    return true;
                  }
                  if (abs (t2) < PRECISION){
                   t = t1;
                   return true;
                  }

              }

        return false;
}

