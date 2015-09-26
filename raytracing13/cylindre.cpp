#include "cylindre.h"



vector3 cylindre::getSurfacePoint(){
    cout << "not implemented" << endl;
    return vector3(0,0,0);
}
Rgb cylindre::getLightLuminance(vector3 currPoint, vector3 objectNormal, vector3 lightPoint){
    cout << "not implemented" << endl;
    return Rgb(0,0,0);
}

cylindre::cylindre(int h, vector3 n, vector3  coords,int rad, materialConstants m) : Primitive(m)
{
    height = h;
    normal = new vector3(n);
    radius = rad;
    position = new vector3(coords);


    lower = new Plane( -(*position).y, (*normal)*(-1) , materialConstants(0,0,0,qRgb(0,0,0)));
    upper = new Plane( height - (*position).y, (*normal), materialConstants(0,0,0,qRgb(0,0,0)));
    texture = NULL;
//-------------------------------
    vector3 ts = vector3(-1, 0, 0.9);
    textureStart = new vector3 (ts.normalize());
//-------------------------------
    vector2 textureStartProjection  = getTextuteStart().oxzProjection() ;
    vector2 positionProjection = position->oxzProjection();
    vector2 textureStartPointProjection = positionProjection + textureStartProjection;
    textureStartPointProjection.rotate(positionProjection, pii/2);

    vector3 textureStartPointRotated = vector3(textureStartPointProjection.x, 0, textureStartPointProjection.y );
    vector3 v = textureStartPointRotated - getPosition();
    textureStartRotatedHalfPii = new vector3 (v.normalize());

}

cylindre::cylindre(cylindre &c) :  Primitive(c.getMaterial())
{
    height = c.height;
    normal = new vector3(c.getNormal());
    radius = c.radius;
    position = new vector3(c.getPosition());

    upper = new Plane(c.getUpper());
    lower = new Plane(c.getLower());

    if (c.getTexture() != NULL) texture = new ProjectionPane(*c.getTexture());
    textureStart = new vector3(c.getTextuteStart());
    textureStartRotatedHalfPii = new vector3(c.getTextureStartRotatedHalfPii());

}

cylindre::~cylindre()
{
    delete normal;
    delete position;
    delete lower;
    delete upper;
    if (texture != NULL) delete texture;
    delete textureStart;
    delete textureStartRotatedHalfPii;
}

Rgb cylindre::getColor(vector3 currPoint)
{
    if (texture != NULL) return getTextureColor(currPoint);
    else return material->getColor();
}

Rgb cylindre::getTextureColor(vector3 currPoint)
{
    vector3 lowerBaseProjection = vector3(currPoint.x, 0, currPoint.z );
    vector3 upperBaseProjection = vector3(currPoint.x, -height, currPoint.z );

    //---------------------

    //--------------------

    float cosalpha = getTextuteStart() * (lowerBaseProjection - (getPosition())).normalize();
    float cosbeta = getTextureStartRotatedHalfPii() * (lowerBaseProjection - (getPosition())).normalize();

    float alpha;
    if (cosbeta >= PRECISION) alpha = acos(cosalpha);
    else alpha = 2*pii - acos(cosalpha);



    //todo : DEBUGG
    int px = Utils::round((alpha * radius)) % texture->getWidth();
    int py = Utils::round((currPoint - upperBaseProjection).length()) % texture->getHeight();
    //DEBUG
    if (px < 0){

        cout << "px : " << px << endl;
        cout << "getTextuteStart "<<  this->getTextuteStart().getString() << endl;
        cout << "getTextureStartRotatedHalfPii "<<  this->getTextureStartRotatedHalfPii().getString() << endl;

        cout << "cosalpha : " << cosalpha << endl;
        cout << "cosbeta : " << cosbeta << endl;
        cout << "acos(cosalpha) " << acos(cosalpha) << endl;
        cout << "alpha : " << alpha << endl;


     }

    //  cout << "texture get pixel " << px <<" " << py << endl;
    Rgb returnColor = texture->getPixel(py, px);
   // cout << "getTextureColor " << returnColor.getString() << endl;
    return returnColor;
}

bool cylindre::pointBetweenBases(vector3 point)
{
    vector3 tmp = point-(*position);
    if ((tmp* (*normal)) < 0 )return false;

    if ( abs (tmp.length()* (tmp * (*normal))/tmp.length()/(*normal).length())  > height) return false;

    return true;
}



void cylindre::setTexture(QImage c)
{
    cout << " settexture" << endl;
    if (texture != NULL) {
        delete texture;
    }
    texture = new ProjectionPane(c);
    cout << " settexture finished " << endl;
}

ProjectionPane *cylindre::getTexture()
{
    return texture;
}

 Plane cylindre::getUpper()
 {
    return *upper;
 }

 Plane cylindre::getLower()
 {
    return *lower;
 }


 vector3 cylindre::getTextuteStart()
 {
    return *textureStart;
 }

 vector3 cylindre::getTextureStartRotatedHalfPii()
 {
    return *textureStartRotatedHalfPii;

 }
 vector3 cylindre::getNormal()
 {
    return *normal;
 }


 vector3 cylindre::getPosition()
 {
    return *position;
 }

vector3 cylindre::getNormal(vector3 currPoint)
{
    vector3 r = vector3(currPoint.x - (*position).x, 0, currPoint.z - (*position).z);
    if (r.length() < radius - PRECISION) return vector3(0,1,0);

    r = r.normalize();
    return (r);
}


bool res(float t1,float t2,float &t)
{
    if ((t1 > PRECISION) && (t2 > PRECISION)){
    t = min (t1, t2);
     //if (t > PRECISION)
      return true;
    }

    if ( (t1 * t2) < PRECISION){
      t = max(t1, t2);
      //if (t > PRECISION)
      return true;
    }

    if (abs (t2) < PRECISION){
        if (t1 > PRECISION){
        t = t1;
        return true;}
 }
    if (abs (t1) < PRECISION){
        if (t2 > PRECISION){
     t = t2;
     return true;}
 }


    return false;
}



bool cylindre::baseintersect(vector3 d, vector3 eye, float  &t)
{
   float tb1, tb2;


    lower->intersect(d, eye, tb1);
    upper->intersect(d, eye, tb2);



   //t = min(tb1, tb2);
   //return true;
   // return res( tb1, tb2, t);
    t = min( tb1, tb2);
    return true;

}

bool cylindre::baseintersect_m(vector3 d, vector3 eye, float  &t)
{
   float tb1, tb2;

    lower->intersect(d, eye, tb1);
    upper->intersect(d, eye, tb2);



   //t = min(tb1, tb2);
   //return true;
    //return res( tb1, tb2, t);
    t = max(tb1, tb2);
    return true;


}


bool cylindre::intersect(vector3 d, vector3 eye, float &t)
{
    float t1, t2;
    vector3 currPoint;
    float rad = 10;

    float x0 = position->x;
    float y0 = position->y;
    float z0 = position->z;

    /*float a1 = d.x*d.x/a/a  + d.z*d.z/b/b;
    float b1 = 2*(d.x*eye.x/a/a + d.z*eye.z/b/b - d.x*x0/a/a  - d.z*z0/b/b);
    float c1 = eye.x*eye.x/a/a  + eye.z*eye.z/b/b  + x0*x0/a/a  + z0*z0/b/b
              - 2*(eye.x*x0/a/a + eye.z*z0/b/b)
              - 1;
*/


    float a1 = d.x*d.x  + d.z*d.z;
        float b1 = 2*(d.x*eye.x + d.z*eye.z - d.x*x0  - d.z*z0);
        float c1 = eye.x*eye.x  + eye.z*eye.z + x0*x0 + z0*z0
                  - 2*(eye.x*x0 + eye.z*z0)
                  - radius*radius;

    bool boo = sqrUravn(a1, b1, c1, t1, t2);


    if (boo){
        //return  res(t1, t2, t);


        vector3 point1 = eye + d*t1;
        vector3 point2 = eye + d*t2;


        if (! (pointBetweenBases(point1) && pointBetweenBases(point2))){


            if (!pointBetweenBases(point1) && pointBetweenBases(point2)){

                baseintersect_m(d ,eye , t1);

                //t = min(t1, t2);
                //return true;
                //return res(t1, t2, t);
                t =  t2;
                if (abs(t2) < PRECISION) return res(t1, t2, t);//t = t1;  //lightning
                if (abs(t1) < PRECISION)  {t = t1; return true;}
                return true;


            }

            else if (pointBetweenBases(point1) && !pointBetweenBases(point2)){

                baseintersect(d ,eye , t2);
               // t = min(t1, t2);
                //return true;
                //return res(t1, t2, t);
                t = t2;
                if (abs(t2) < PRECISION) return res(t1,t2,t);//t = t1;//lightning
                if (abs(t1) < PRECISION) {t = t1; return true;}
                return true;

            }
            else if (!pointBetweenBases(point1) && !pointBetweenBases(point2)){


                baseintersect_m(d ,eye , t1);
                baseintersect(d ,eye , t2);



                //baseintersect(d ,eye , t);
                baseintersect(d ,eye , t);
                //t = min(t1, t2);
                vector3 r = eye + d*t - (*position);
                r.y = 0;
                if (r.length() > radius) return false;

                if (abs(t2) < PRECISION) {t = t1; return true;}
                if (abs(t1) < PRECISION) {t = t1; return false;}//true;}


                return true;
            }

        }

        if (pointBetweenBases(point1) && pointBetweenBases(point2)){

           return res(t1, t2, t);
        }

    }

return false;

}
