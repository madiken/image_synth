#include "projectionpane.h"
#include "utils.h"


ProjectionPane::ProjectionPane(int w, int h)
{
    width = w;
    height = h;

    pane = new Rgb**[height];

    for (int i = 0; i < height; i++){
        pane[i] = new Rgb*[width];
        for (int j = 0; j < width; j++)
            pane[i][j] = new Rgb(0, 0, 0);
    }
}

ProjectionPane::ProjectionPane(ProjectionPane &p)
{
    width = p.getWidth();

    height = p.getHeight();

    pane = new Rgb**[height];

    for (int i = 0; i < height; i++){
        pane[i] = new Rgb*[width];
        for (int j = 0; j < width; j++)
            pane[i][j] = new Rgb(p.getPixel(i, j));
    }
}

ProjectionPane::ProjectionPane(QImage &im)
{
    width = im.width();
    height = im.height();

    pane = new Rgb**[height];

    float maxcolor = 0;

    for (int i = 0; i < height; i++){
        pane[i] = new Rgb*[width];
        for (int j = 0; j < width; j++){
            Rgb color = im.pixel(j, i);
            pane[i][j] = new Rgb(color);

            float co = Utils::maximum(color.red(),  Utils::maximum(color.green(),color.blue() ));
            if (maxcolor < co) maxcolor = co;
        }
    }

    for (int i = 0; i < height; i++){

        for (int j = 0; j < width; j++){
            this->setPixel(i, j, this->getPixel(i, j)* (1/maxcolor));
        }
    }

}


ProjectionPane::~ProjectionPane()
{
    for (int i = 0; i < height; i++){

        for (int j = 0; j < width; j++)
            delete pane[i][j];

        delete[] pane[i];
    }

    delete[] pane;
}


int ProjectionPane::getWidth()
{
    return this->width;
}

int ProjectionPane::getHeight(){
    return this->height;
}

void ProjectionPane::setPixel(int i, int j, Rgb color)
{
    pane[i][j]->setRed(color.red());
    pane[i][j]->setGreen(color.green());
    pane[i][j]->setBlue(color.blue());
}


Rgb ProjectionPane::getPixel(int i, int j)
{
    if ((i >= 0) & (j >= 0)
            &(i < height) & (j < width))
    return *pane[i][j];
    else  return Rgb(0,0,0);
}


