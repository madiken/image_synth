#include "traceengine.h"
#include "materialmodel.h"
#include "myrectangle.h"
#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>
#include <QtDebug>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include "randutils.h"


using namespace std;


vector3 light(0,-80,-120);//(0,-70, -20);//(30, -40 , 0);
float lightintensity = 2;
//-----------------------------

Rgb traceEngine::getTextureColor(vector3 point)//point on the floor
{
   if (myscene->floorTexture == NULL) return Rgb(0, 0, 0);
   point.x = point.x + 700000;
   point.z = point.z + 700000;
   float unitx = 300000/myscene->floorTexture->getWidth();
   float unity = 300000/myscene->floorTexture->getHeight();

   float texx = (point.x) - (int)point.x/(int)unitx * unitx;
   float texy = (point.z) - (int)point.z/(int)unity * unity;
//out << "texx " << (int) texx << "  " << (int) texy << endl
  //      << " "<< texx << " "<< texy << endl;


   texx *= myscene->floorTexture->getWidth()/unitx;
   texy *= myscene->floorTexture->getHeight()/unity;
   return myscene->floorTexture->getPixel(abs((int)texx), abs((int)texy));
}


traceEngine::traceEngine()
{

    viewPortx = 1500;
    viewPorty = 1500;
}
/*
bool sqrUravn1(float a, float b, float c, float &t1, float &t2)
{
    float deskr = (b*b - 4*a*c);
    if (deskr < 0) return 0;

    t1 = (-b + sqrt(deskr)) / (2 * a);
    t2 = (-b - sqrt(deskr)) / (2 * a);
    return true;
}
*/

vector3 traceEngine::get_reflected_ray(vector3 dir, vector3 normal)
{
    float cosI =  - (normal * dir);
    return dir + normal * cosI * 2;

}


Primitive *traceEngine::intersectScene(vector3 d, vector3 eye, float &t)
{
    vector <Primitive *> :: iterator it;

    float currMin = 2000;
    int index, i;

    for (it = myscene->primitives.begin(), i = 0; it != myscene->primitives.end(); it++, i++){


        bool boo = (*it)->intersect(d, eye, t);

        if (boo) {
              //out << " id : "<< (*it)->getPrimitiveId() << endl;
            //return (*it);
            if ((t < currMin)&&(t > PRECISION)) {
                currMin = t;
                index = i;
            }
        }
    }


    if (currMin < 2000)  {t = currMin; return myscene->primitives[index];}

    return NULL;
}


float traceEngine::shadow(vector3 currPoint)
{
    vector3 dir = light - currPoint;
    dir = dir.normalize();

    float t;
    Primitive *obj = intersectScene(dir, currPoint, t);

    vector3 intersector = dir * t;
    vector3 lightvector = light - currPoint;
    if (obj != NULL)

        if (intersector.length() < lightvector.length()) {
            return 0.0;
        }

    return 1;
}




vector3 traceEngine::getReflectedRay(vector3 d, vector3 normal)
{
    return d + (normal * 2 *abs(d * normal));
}

vector3 traceEngine::getRefractedRay(vector3 d, vector3 normal, float in, float out, bool &isRefracted)
{
    float cosa = d * normal;
    if(cosa  > 0) {
        normal = normal * (-1);
    }

    float n = in/out;
    float cosalfa = d * normal;
    float cosBetaSqr = (1 - ((n * n) * (1 - (cosalfa * cosalfa))));

    if (cosBetaSqr < 0){
        isRefracted = false;
        return vector3(0,0,0);
    }
    else{
        isRefracted = true;
        return  (d - normal * cosalfa) * n  - normal * sqrt(cosBetaSqr);

    }
}

float  MAX(float a, float b){
   if  ( a>b ) return a;
   else return b;
}

float  MIN(float a, float b){
   if  ( a<b ) return a;
   else return b;
}



float schlick(float in, float out, vector3 d, vector3 normal)
{
    float rn = in/out;
    float cosalpha = abs (d * normal);
    float R0 = (1 - cosalpha * rn) / (1 + cosalpha * rn);

    return R0 + (1 - R0) * (pow( 1 - cosalpha, 5));
}

bool traceEngine::shadowRayPassed(vector3 currPoint, vector3 lightPoint)
{
    vector3 dir = lightPoint - currPoint;
    dir = dir.normalize();

    float t;
    Primitive *obj = intersectScene(dir, currPoint, t);
    if (obj != NULL){
        vector3 intersector = dir * t;
        vector3 lightvector = lightPoint - currPoint;
        if (intersector.length() < lightvector.length()) {
                return false;
            }
    }
    return true;
}
//specular brdf is not exactly correct now
Rgb traceEngine::directLuminance(vector3 d, vector3 eye, vector3 currPoint, Primitive *obj,  int depth)
{

    vector3 normal = obj->getNormal(currPoint);
    if ((d*normal) > 0){
        normal = normal*(-1);
    }
    vector <Primitive *> :: iterator it;

    Rgb result = Rgb(0,0,0);
    for (it = myscene->primitives.begin(); it != myscene->primitives.end(); it++){
        Primitive *pr = *it;
        if (pr->ifIsLightSource()){
            Rgb light;
            vector3 lightPoint = pr->getSurfacePoint();
            if (shadowRayPassed(currPoint, lightPoint)){
                light =  pr->getLightLuminance( currPoint, normal, lightPoint);
                float diff = obj->getMaterial().diffuse;
                float spec = obj->getMaterial().specular;
                float pho = obj->getMaterial().phong;

                vector3  s = (lightPoint - currPoint).normalize();
                vector3  v = (eye - currPoint).normalize();
                vector3 h = ((s + v)* 0.5).normalize();
                result = result + light * (diff/pii * (s * normal ) + spec * (pow(h * normal, pho)));
            }
        }


    }
    return result;
}

Rgb traceEngine::getRefractedColor(vector3 d, vector3 eye, vector3 currPoint, Primitive *obj,  int depth)
{
    float refl = obj->getMaterial().reflectance;


    //sphere always has proper normal
    //todo :change logic of choise

    float inRayEnvIndex, outRayEnvIndex;
    if (d * obj->getNormal(currPoint) > 0) //from sphere to air
    {
        inRayEnvIndex = obj->getMaterial().refraction;
        outRayEnvIndex = 1.0;//air
    }
    else
    {
        inRayEnvIndex = 1.0;
        outRayEnvIndex = obj->getMaterial().refraction;
    }

    bool isRefracted;
    vector3 refracted = getRefractedRay(d, obj->getNormal(currPoint), inRayEnvIndex, outRayEnvIndex, isRefracted);
    refracted = refracted.normalize();

    Rgb reflectedColor = getMirrorColor(d, eye, currPoint, obj, depth);

    float sch = schlick(inRayEnvIndex, outRayEnvIndex, d, obj->getNormal(currPoint));
    Rgb refractedColor;
    if (isRefracted) {
        refractedColor = path_trace(refracted.normalize(), currPoint, depth - 1); // refl.kT * trace(refractRay, depth + 1);
        return reflectedColor * sch + refractedColor * (1-sch);
    }

    return refractedColor ;
}


Rgb traceEngine::getMirrorColor(vector3 d, vector3 eye, vector3 currPoint, Primitive *obj,  int depth)
{
    //Reflectance refl = intersection.primitive->getReflectance(intersection.point);
    float refl = obj->getMaterial().reflectance;

    vector3 normal = obj->getNormal(currPoint);
    if ((d*normal) > 0){
        normal = normal*(-1);
    }
    vector3 reflectionDirection = getReflectedRay(d, normal);
    reflectionDirection = reflectionDirection.normalize();

    Rgb reflectedColor = path_trace(reflectionDirection, currPoint,  depth - 1);
    Rgb thisColor = obj->getColor(currPoint);

    Rgb resultColor = reflectedColor * thisColor * refl ;
    return  resultColor;
}

Rgb traceEngine::getSpecularColor(vector3 d, vector3 eye, vector3 currPoint, Primitive *obj,  int depth)
{
   // cout << "get specular started " << endl;
    //Reflectance refl = intersection.primitive->getReflectance(intersection.point);
    float specular = obj->getMaterial().specular;
    float phong = obj->getMaterial().phong;

    vector3 normal = obj->getNormal(currPoint);
    if ((d*normal) > 0){
        normal = normal*(-1);
    }
    vector3 reflectionDirection = getReflectedRay(d, normal);
    reflectionDirection = reflectionDirection.normalize();

    vector3 newDirection = RandUtils::getRandomDirection(reflectionDirection);

    Rgb reflectedColor = path_trace(newDirection, currPoint,  depth - 1);
    Rgb thisColor = obj->getColor(currPoint);

    float pho = newDirection*reflectionDirection;
    float pho1 = pow(pho, phong);
    float cosa = (newDirection * normal);
    Rgb resultColor = reflectedColor * thisColor * cosa * specular * pho1 ;//* (phong + 1) ??? ;
   // cout << "get specular finished : " << resultColor.getString() << endl;
    return  resultColor;
}

Rgb traceEngine::getDiffuseColor(vector3 d, vector3 eye, vector3 currPoint, Primitive *obj,  int depth)
{
    vector3 normal = obj->getNormal(currPoint);
    if ((d*normal) > 0){
        normal = normal*(-1);
    }

    vector3 newDirection = RandUtils::getRandomDirection(normal);

    Rgb reflectedColor = path_trace(newDirection, currPoint,  depth - 1);


    float cosi = (normal * newDirection);
    float diffuse = obj->getMaterial().diffuse;
    Rgb thisColor = obj->getColor(currPoint);


    Rgb multiplication = thisColor * reflectedColor;
    Rgb color = multiplication * 2 * cosi * diffuse;

    return color;
}





Rgb traceEngine::path_trace(vector3 d, vector3 eye, int depth)
{

    Rgb resultColor = Rgb(0, 0, 0);
    if (depth <= 0) return resultColor;


    float t;
    Primitive *obj = intersectScene(d, eye, t);

    if (obj != NULL){
        vector3 currPoint  = eye + d*t;

        if (obj->ifIsLightSource())
        {
            resultColor = obj->getColor(currPoint);
        }
        else {
            if (obj->getMaterial().type == 0) // diffuse
                resultColor = getDiffuseColor(d, eye, currPoint,obj, depth);
            else if (obj->getMaterial().type == 1) //glossy : diffuse or specular
            {
                bool choise = RandUtils::ifDiffuseIsChosen(obj->getMaterial().specular,  obj->getMaterial().diffuse);
                float s = obj->getMaterial().specular;
                float di = obj->getMaterial().diffuse;
                float probabilitySpec = s/(s + di);
                float probabilityDiff = 1-probabilitySpec;

                if (choise == false){

                   resultColor = getSpecularColor(d, eye, currPoint, obj, depth) * 1/probabilitySpec ;
                }
                else{
                   resultColor = getDiffuseColor(d, eye, currPoint, obj, depth) * 1/probabilityDiff ;
                }

            }
            else if (obj->getMaterial().type == 2){
                 resultColor = getMirrorColor(d, eye, currPoint, obj, depth);
            }
            else if (obj->getMaterial().type == 3){
                resultColor = getRefractedColor(d, eye, currPoint, obj, depth);
            }
        }

      //  Rgb cc = directLuminance(d, eye, currPoint, obj, depth);

       // resultColor = resultColor;// + cc;
    }



    return resultColor;
}

Rgb traceEngine::ray_trace(vector3 d, vector3 eye, int depth)
{

    materialModel matCalculator;

  Rgb color(0,0,0);
 Rgb reflectColor(0,0,0);

    float t;

    Primitive *obj = intersectScene(d, eye, t);

    if (obj != NULL){

        vector3 currPoint  = eye + d*t;

       // cout << " currPoint " << currPoint.getString() << endl;
        //if (obj->getPrimitiveId() == 3) out << currPoint.x << " " << currPoint.y << " " <<currPoint.z << endl;



        vector3 normal = obj->getNormal(currPoint);
        if ((d*normal) > 0){
            normal = normal*(-1);
        }


        float shadowkoef  = shadow(currPoint);



        float materialModelKoef = matCalculator.calculateDiffuse(currPoint, light, normal) *  obj->getMaterial().diffuse * shadowkoef
                                + matCalculator.calculateSpecular(currPoint, light,normal, eye) * obj->getMaterial().specular * shadowkoef
                                + 0.2 * obj->getMaterial().ambient;
       //умножаем на цвет объекта

     //   if (obj->getPrimitiveId() == 1)
      //      obj->getColor(currPoint) = QColor(getTextureColor(currPoint));


        float red =   obj->getColor(currPoint).red();
        float green = obj->getColor(currPoint).green();
        float blue =  obj->getColor(currPoint).blue();


        red *= materialModelKoef;
        green *= materialModelKoef;
        blue *= materialModelKoef;



        if (red > 255) red = 255;
        if (green > 255) green = 255;
        if (blue > 255) blue = 255;


        color  = Rgb(red , green , blue );

      /*  if (depth > 1){
            vector3 reflected = get_reflected_ray(d, normal);
            reflected = reflected.normalize();
            reflectColor = path_trace(reflected, currPoint, depth - 1);

            Rgb co = Rgb(color.red(), color.green(), color.blue());
            Rgb reco = Rgb(reflectColor.red(), reflectColor.green(), reflectColor.blue());

            //if (! ((reco.red() <= 0.01) && (reco.green() <= 0.01) && (reco.blue() <= 0.01))){
                float red =  co.red() + obj->getMaterial().reflectance * reco.red();
                if (red > 255) red = 255;

                float green = co.green() + obj->getMaterial().reflectance * reco.green();
                if (green > 255) green = 255;

                float blue =  co.blue() + obj->getMaterial().reflectance * reco.blue();
                if (blue > 255) blue = 255;

                color  = Rgb(red, green, blue);

       }*/
    }



  return color;
}

float ra()

{
    srand ( time(NULL) );

    float r = rand()%6 + 1;
    r /= 100;

    return r;
}


void traceEngine::testTrace(ProjectionPane &pane, camera cacamera, Settings settings)
{

   RandUtils::setupRand();
   vector3 eye = cacamera.getCameraPos();

    int xres = pane.getWidth();
    int yres = pane.getHeight();

    float pixelsizeX = viewPortx/pane.getWidth();
    float pixelsizeY = viewPorty/pane.getHeight();

    vector3 d;

    for (int x = 0; x < xres; x++)
        for (int y = 0; y < yres; y++){

           for (int r = 0; r < settings.getRaysPerPixel(); r++)
           {
                float displacementX = RandUtils::getPixelDisplacement(settings.getRaysPerPixel());
                float displacementY = RandUtils::getPixelDisplacement(settings.getRaysPerPixel());

                vector3 xvector(((float)viewPortx)/2,0,0);
                vector3 yvector(0,((float)viewPorty)/2,0);
                vector3 xv(((float)x + displacementX)*pixelsizeX,0,0);
                vector3 yv(0,((float)y + displacementY)*pixelsizeY,0);

                vector3 pixelPoint;
                pixelPoint = (xv - xvector) + (yv - yvector);

                d = cacamera.getFocusVector() + pixelPoint;//xvector*((float)x/(float)xres - 0.5)*2 + yvector*((float)y/(float)yres - 0.5)*2;
               // d = pixelPoint - eye;//xvector*((float)x/(float)xres - 0.5)*2 + yvector*((float)y/(float)yres - 0.5)*2;

                d = d.normalize();
                Rgb color = path_trace(d, eye, settings.getRecursionDepth());
                pane.setPixel(x, y, pane.getPixel(x, y) + color);
            }
            pane.setPixel(x, y, pane.getPixel(x, y)/settings.getRaysPerPixel());
            float percent = (float)(x * yres  + y)/(float)(xres * yres) * 100;
            cout  << " readiness : " << x << "/" << xres << " " << y << "/" << yres << " " << percent << "%" << endl;

     }
       cout << "testTrace finished" << endl;
}



traceEngine::~traceEngine()
{

    //do not need to delete myScene
}

void traceEngine::setScene(scene *scene)
{
    this->myscene = scene;
}









