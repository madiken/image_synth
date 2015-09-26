#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H
#include "primitive.h"
class Parallelogram : public Primitive
{
private :
    Rectangle *lowerSide;
    Rectangle *upperSide;
    Rectangle *leftSide;
    Rectangle *rightSide;
    Rectangle *faceSide;
    Rectangle *backSide;



public :
    Parallelogram(Rectangle lbase, float h, materialConstants m);

    Rectangle *lowerSide;
    Rectangle *upperSide;
    Rectangle *leftSide;
    Rectangle *rightSide;
    Rectangle *faceSide;
    Rectangle *backSide;

};

#endif // PARALLELOGRAM_H
