#include "camera.h"

camera::camera()
{
        focusVector = new vector3(0,0,1500);
        cameraPos = new vector3(0, -50, -200);
}

camera::~camera()
{
    delete focusVector;
    delete cameraPos;
}



vector3 calcNormal(vector3 vVector1, vector3 vVector2)
{
        vector3 vNormal;
        vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
        vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
        vNormal.z  = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

        return vNormal;
}



