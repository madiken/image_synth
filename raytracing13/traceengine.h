#ifndef TRACEENGINE_H
#define TRACEENGINE_H

#include "vector3.h"
#include "camera.h"
#include "sphere.h"
#include "plane.h"
#include "scene.h"
#include "primitive.h"
#include "settings.h"
#include "rgb.h"
#include "projectionpane.h"



#include <vector>
class traceEngine
{

    float viewPortx;
    float viewPorty;


    scene *myscene;//this is to be deleted externally

public:
    traceEngine();
    ~traceEngine();

    vector3 getReflectedRay(vector3 d, vector3 normal);
    void generateScene(QString str);
    void testTrace(ProjectionPane &pane, camera cacamera, Settings settings);

    Rgb path_trace(vector3 d, vector3 eye, int depth);
    vector3 get_reflected_ray(vector3 dir, vector3 normal);


    Primitive *intersectScene(vector3 d, vector3 eye, float &t);
    float shadow(vector3 currPoint);
    void setScene(scene *myscene);

    Rgb getTextureColor(vector3 point);//point on the floor
    Rgb ray_trace(vector3 d, vector3 eye, int depth);

    vector3 getRefractedRay(vector3 d, vector3 normal, float in, float out, bool &isRefracted);

    Rgb directLuminance(vector3 d, vector3 eye, vector3 currPoint, Primitive *obj,  int depth);
    bool shadowRayPassed(vector3 currPoint, vector3 lightPoint);
    Rgb getRefractedColor(vector3 d, vector3 eye, vector3 currPoint, Primitive *obj,  int depth);
    Rgb getMirrorColor(vector3 d, vector3 eye, vector3 currPoint, Primitive *obj,  int depth);
    Rgb getSpecularColor(vector3 d, vector3 eye, vector3 currPoint, Primitive *obj,  int depth);
    Rgb getDiffuseColor(vector3 d, vector3 eye, vector3 currPoint, Primitive *obj,  int depth);
};

#endif // TRACEENGINE_H
