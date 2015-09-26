#include "Plane.h"
#include "materialconstants.h"

#include "Constants.h"
Plane::Plane(Plane &p) : Primitive(p.getMaterial())
{
    d_const = p.getDConst();
    normal = new vector3(p.getNormal());
}


Plane::Plane(float d, vector3 n, materialConstants m) : Primitive(m)
{
    d_const = d;


    normal = new vector3(n.normalize());

    cout << " Plane constructor--------- " << endl;


    cout << "plane normal actual: " << normal->getString() << endl;
    cout << "------------------------" << endl;
}

/*Plane::Plane(Plane &p){
    cout << " COPIER!!!!!!! " << endl;
}*/

Plane::~Plane()
{

    cout << " delete plane start" << endl;
    cout << "deleting normal :" << normal->getString() << endl;
    delete normal;
    cout << " delete plane finished" << endl;

}

float Plane::getDConst()
{
    return d_const;
}

vector3 Plane::getNormal()
{
 /*   cout << " plane get normal :";
    cout << normal->getString();// << end;
    cout << endl;*/
    return *normal;
}

vector3 Plane::getNormal(vector3 currPoint)
{
    return getNormal();
}

bool Plane::intersect(vector3 d, vector3 eye, float &t)
{
    float dnormal = d*(*normal);
    t = (d_const - eye*(*normal))/(dnormal);
    return true;
}

