#ifndef SCENE_H
#define SCENE_H

#include "primitive.h"
#include <vector>
#include "projectionpane.h"
#include "plane.h"

#include "utils.h"
#include "sphere.h"
#include "Constants.h"
#include "cylindre.h"
#include "myrectangle.h"
using namespace std;

class scene
{
public:
    scene();
    scene(scene &s);

    vector <Primitive *> primitives;
    ProjectionPane *floorTexture;
    ~scene();

    void generateDefaultScene();
    void rotateFloorMyRectangle(MyRectangle *base, float alpha);
    vector<Primitive *> getParrallelogramSides(MyRectangle *base, float h);
};

#endif // SCENE_H
