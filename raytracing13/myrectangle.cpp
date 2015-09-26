#include "MyRectangle.h"
#include "utils.h"
MyRectangle::MyRectangle(vector3 e1, vector3 e2,vector3 e3, materialConstants m) : Primitive(m)
{
    this->edge1 = new vector3(e1);
    this->edge2 = new vector3(e2);
    this->edge3 = new vector3(e3);

    vector3 v1 = *edge1 - *edge2;
    vector3 v2 = *edge3 - *edge2;
    this->edge4 = new vector3(*edge2+ (v1+v2));


    vector3 n = Utils::vectorMult(*edge1 - *edge2, *edge3 - *edge2);
    vector3 normalized  = n.normalize();

    this->plane = new Plane((normalized.operator *(*edge1)), n.normalize(), m);
}


MyRectangle::MyRectangle(MyRectangle &r) : Primitive(r.getMaterial())
{
    this->edge1 = new vector3(r.getEdge1());
    this->edge2 = new vector3(r.getEdge2());
    this->edge3 = new vector3(r.getEdge3());
    this->edge4 = new vector3(r.getEdge4());
    this->plane = new Plane(r.getPlane());
}

MyRectangle::~MyRectangle()
{
    cout << " delete MyRectangle started" << endl;
    delete edge1;
    delete edge2;
    delete edge3;
    delete edge4;

    delete plane;
    cout << " delete MyRectangle finished" << endl;
}

Plane MyRectangle::getPlane(){
    return *plane;
}

bool MyRectangle::intersect(vector3 d, vector3 eye, float &t)
{
    bool flag = plane->intersect(d,eye,t);
    if (!flag) return false;

    vector3 currPoint = eye + d*t;

    vector3 u = *edge1-*edge2;
    vector3 v = *edge3-*edge2;

    vector3 w = currPoint-*edge2;
    float s = ((u*v)*(w*v) - (v*v) * (w*u)) /
                (pow((u*v), 2) - (u*u) * (v*v));

    float tt = ((u*v)*(w * v) - (u*u) * (w*v)) /
            (pow((u*v), 2) - (u*u) * (v*v));


    if ((s > 1) | (s < 0)) return false;
    if ((tt > 1)| (tt < 0)) return false;

    return true;
}

vector3 MyRectangle::getNormal(vector3 currPoint)
{
    return plane->getNormal();
}


vector3 MyRectangle::getNormal()
{
    return plane->getNormal();
}


vector3 MyRectangle::getEdge1()
{
    return *edge1;
}

vector3 MyRectangle::getEdge2()
{
    return *edge2;
}

vector3 MyRectangle::getEdge3()
{
    return *edge3;
}

vector3 MyRectangle::getEdge4()
{
    return *edge4;
}


void MyRectangle::setEdge1(vector3 v){
    edge1->x = v.x;
    edge1->y = v.y;
    edge1->z = v.z;
}

void MyRectangle::setEdge2(vector3 v){
    edge2->x = v.x;
    edge2->y = v.y;
    edge2->z = v.z;
}

void MyRectangle::setEdge3(vector3 v){
    edge3->x = v.x;
    edge3->y = v.y;
    edge3->z = v.z;
}
void MyRectangle::setEdge4(vector3 v){
    edge4->x = v.x;
    edge4->y = v.y;
    edge4->z = v.z;
}

vector3 MyRectangle::getSurfacePoint()
{
    float r1 = RandUtils::getPixelDisplacement(500);
    float r2 = RandUtils::getPixelDisplacement(500);

    return (getEdge1()-getEdge2()) * r1 + (getEdge3()-getEdge2()) * r2 + getEdge2();
}

float MyRectangle::getSquare()
{
    return (getEdge3()-getEdge2()).length() * (getEdge1()-getEdge2()).length();
}

Rgb  MyRectangle::getLightLuminance(vector3 currPoint, vector3 objectNormal, vector3 lightPoint)
{
    vector3 toLight = (lightPoint - currPoint).normalize();
    vector3 fromLight = (currPoint - lightPoint).normalize();

    float cosa1 = objectNormal * toLight;
    float cosa2 = this->getNormal(lightPoint) * fromLight;
    float r = (lightPoint - currPoint).length();


    return this->getColor(currPoint) * cosa1 * cosa2 / r/ r * (getSquare()) ;

}
