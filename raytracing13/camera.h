#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"

class camera {
private :
    vector3 *cameraPos;
    vector3 *focusVector;
public :


    camera(camera &c){
        cameraPos = new vector3(c.getCameraPos());
        focusVector = new vector3(c.getFocusVector());
    }

    camera();
    ~camera();

    vector3 getCameraPos(){
        return *cameraPos;
    }
    vector3 getFocusVector(){
        return *focusVector;
    }

};




#endif // CAMERA_H
