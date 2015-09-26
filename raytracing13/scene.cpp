#include <QCoreApplication>
#include <QtCore\QtCore>
#include <QtGui\QtGui>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include "scene.h"
#include "MyRectangle.h"
#include "vector2.h"


void scene::rotateFloorMyRectangle(MyRectangle *base, float alpha)
{
    vector3 center = (base->getEdge2() + base->getEdge4())/2;
    vector2 floorCenter = vector2(center.x, center.z);
    vector2 e1 = base->getEdge1().oxzProjection();
    vector2 e2 = base->getEdge2().oxzProjection();
    vector2 e3 = base->getEdge3().oxzProjection();
    vector2 e4 = base->getEdge4().oxzProjection();

    e1.rotate(floorCenter, alpha);
    e2.rotate(floorCenter, alpha);
    e3.rotate(floorCenter, alpha);
    e4.rotate(floorCenter, alpha);

    vector3 newE1 = vector3(e1.x, base->getEdge1().y, e1.y);
    vector3 newE2 = vector3(e2.x, base->getEdge2().y, e2.y);
    vector3 newE3 = vector3(e3.x, base->getEdge3().y, e3.y);
    vector3 newE4 = vector3(e4.x, base->getEdge4().y, e4.y);


    base->setEdge1(newE1);
    base->setEdge2(newE2);

    base->setEdge3(newE3);
    base->setEdge4(newE4);

}

vector<Primitive *> scene::getParrallelogramSides(MyRectangle *base, float h)
{
    vector<Primitive *> result;

    vector3 modify(0, -h, 0);

    Primitive *rightSide = new MyRectangle(base->getEdge3() + modify, base->getEdge4() + modify, base->getEdge4(), base->getMaterial());
    Primitive *faceSide = new MyRectangle(base->getEdge2(), base->getEdge3(), base->getEdge3() + modify, base->getMaterial());
    Primitive *backSide = new MyRectangle(base->getEdge1(), base->getEdge4(), base->getEdge4() + modify, base->getMaterial());
    Primitive *leftSide = new MyRectangle(base->getEdge1(), base->getEdge2(), base->getEdge2() + modify, base->getMaterial());
    Primitive *upperSide = new MyRectangle(base->getEdge1() + modify, base->getEdge2() + modify, base->getEdge3() + modify, base->getMaterial());

    result.push_back(base);
    result.push_back(upperSide);

    result.push_back(leftSide);
    result.push_back(rightSide);

    result.push_back(faceSide);
    result.push_back(backSide);

    /*Sphere *s2 = new Sphere(2, dynamic_cast<MyRectangle *>(upperSide)->getEdge3(), materialConstants (1.0f,1.0f,1.0f, 0x00ff00, 0.5f));
    Sphere *s3 = new Sphere(2,dynamic_cast<MyRectangle *> (upperSide)->getEdge4(), materialConstants (1.0f,1.0f,1.0f, 0x00ff00, 0.5f));
    Sphere *s4 = new Sphere(2, dynamic_cast<MyRectangle *>(upperSide)->getEdge2(), materialConstants (1.0f,1.0f,1.0f, 0x00ff00, 0.5f));
    Sphere *s5 = new Sphere(2,dynamic_cast<MyRectangle *> (upperSide)->getEdge1(), materialConstants (1.0f,1.0f,1.0f, 0x00ff00, 0.5f));
    result.push_back(s2);
    result.push_back(s3);
    result.push_back(s4);
    result.push_back(s5);
*/
    return result;
}

scene::scene()
{
}

scene::scene(scene &s)
{
    cout << "scene::scene(scene &s)" << endl;
}

scene::~scene()
{
    cout << "delete scene----------------------" << endl;
    for (vector<Primitive *>::iterator it = primitives.begin() ; it != primitives.end(); ++it)
    {
        cout << " delete scene item------------------------------------------" << endl;
      delete *it;
    }
    cout << "delete scene finished--------------" << endl;
}

void scene::generateDefaultScene()
{

    //add bounding box

    MyRectangle *roomFloor = new MyRectangle(vector3(-70, 0, 0), vector3(-70, 0, -201), vector3(70, 0, -201),  materialConstants (0.7f,1.0f,1.0f, Rgb(0.9, 0.9, 0.3), 0));

  //Utils::rotateFloorMyRectangle(roomFloor, pii/13);
   float roomHeight = 130;
   vector<Primitive *> parallelogramSides = getParrallelogramSides(roomFloor, roomHeight);
   Primitive *leftSide = parallelogramSides[2];
   Primitive *rightSide = parallelogramSides[3];
   leftSide->setMaterial(materialConstants (1.0f,1.0f,1.0f, Rgb(1, 0.2, 0.2)));
   rightSide->setMaterial(materialConstants (1.0f,1.0f,1.0f, Rgb(0.2, 1, 0.2)));


   primitives.insert( primitives.end(), parallelogramSides.begin(), parallelogramSides.end() );

   //add box
   MyRectangle *base = new MyRectangle(vector3(-15, 0, -20), vector3(-45, 0, -20), vector3(-40, 0, -50),  materialConstants (1.0f,1.0f,1.0f, Rgb(0.9, 0.9, 0.3), 0));
   rotateFloorMyRectangle(base, pii/10);
  float boxHeight = 50;

  vector<Primitive *> baseSides = getParrallelogramSides(base, boxHeight);

   primitives.insert( primitives.end(), baseSides.begin(), baseSides.end() );



//add sphere----------------------------------------

  // Sphere *sp = new Sphere(20, vector3(-30, -20, -50), materialConstants (1.0f,0.2f, 1.0f,  Rgb(0.9, 0.8, 0.3), 1, 0.9));//glossy
 //  Sphere *sp = new Sphere(20, vector3(-30, -20, -50), materialConstants (1.0f,0.2f, 1.0f,  Rgb(0.9, 0.8, 0.3), 3, 0.9, 1.5));//refraction

   Sphere *spMirror = new Sphere(12, vector3(-30, -boxHeight-12, -35), materialConstants (1.0f,0.2f, 1.0f,  Rgb(0.8, 0.8, 0.8), 2, 0));//mirror
   primitives.push_back(spMirror);

//add light----------------------------------------
  MyRectangle *lightSource = new MyRectangle(vector3(-50, -roomHeight + 0.5f, -20), vector3(-50, -roomHeight + 0.5f, -150), vector3(50, -roomHeight + 0.5f, -150),  materialConstants (Rgb(0.8, 1, 1)));
 //  MyRectangle *lightSource = new MyRectangle(vector3(-30, -roomHeight + 0.5f, -30), vector3(-30, -roomHeight + 0.5f, -110), vector3(30, -roomHeight + 0.5f, -110),  materialConstants (Rgb(0.8, 1, 1)));

   lightSource->setIslightSource(true);
   cout << " LIGHT : " << lightSource->ifIsLightSource() << endl;

   primitives.push_back(lightSource);
//cylindre-------------------------------------------
   cylindre * cy = new cylindre(50, vector3(0,-1,0), vector3(37, 0, -30),17, materialConstants(1.0f,0.4f,1.0f, Rgb(1, 1, 1) , 1, 2.5));
   QImage fanta = QImage("fanta.jpg");
   cout << "height :"<< fanta.height() << endl;
   cout << "width : "<< fanta.width() << endl;

   cy->setTexture(fanta);

   primitives.push_back(cy);
   //refracting----------------------------------------------
   Sphere *sp = new Sphere(12, vector3(10, -12, -72), materialConstants (1.0f,0.2f, 1.0f,  Rgb(0.9, 0.8, 0.3), 3, 0.9, 1.2));//refraction
   primitives.push_back(sp);

   cout << "  i'm alive " << endl;
}
