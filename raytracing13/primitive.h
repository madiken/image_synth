
#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "Constants.h"
#include "materialconstants.h"
#include "vector3.h"
#include <cmath>




using namespace std;

class Primitive
{

protected :
    materialConstants *material;

    bool isLightSource;
public:

  /*  Primitive()
    {

    }
*/

    void setIslightSource(bool fl)
    {
        isLightSource = fl;
    }

    bool ifIsLightSource()
    {
        return isLightSource;
    }

    Primitive(Primitive &p){

        cout << "Primitive(Primitive &p) " << endl;
        material = new materialConstants(p.getMaterial());
        isLightSource = p.ifIsLightSource();
    }

    Primitive(materialConstants m){
        material = new materialConstants(m);
        isLightSource = false;
    }

    virtual Rgb getColor(vector3 currPoint)
    {
        return material->getColor();
    }

    virtual materialConstants getMaterial()
    {
        return *material;
    }

    virtual vector3 getSurfacePoint(){
        cout << "not implemented" << endl;
        return vector3(0,0,0);
    }

    virtual Rgb getLightLuminance(vector3 currPoint, vector3 objectNormal, vector3 lightPoint){
        cout << "not implemented" << endl;
        return Rgb(0,0,0);
    }

    virtual void setMaterial(materialConstants m )
    {
        delete material;
        material = new materialConstants(m);
    }

    virtual ~Primitive()
    {
        delete material;
    }

    virtual vector3 getNormal(vector3 currPoint) = 0;
    virtual bool intersect(vector3 d, vector3 eye, float &t) = 0;
    bool sqrUravn(float a, float b, float c, float &t1, float &t2);

    float min(float t1, float t2)
    {
        if (t1 < t2) return t1;
        return t2;
    };




};

#endif // PRIMITIVE_H
