
#ifndef TRATATA_H
#define TRATATA_H

#include <QtGui/QImage>
#include "scene.h"
#include "settings.h"

class tratata
{


    QImage *image;



public:
    void render(Settings settings, scene *myScene);

    ~tratata();

};

#endif // TRATATA_H
