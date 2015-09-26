#ifndef PROJECTIONPANE_H
#define PROJECTIONPANE_H
#include "rgb.h"
#include <QtGui/QImage>
#include <QtGui/QColor>
class ProjectionPane
{
    Rgb ***pane;

    int width;
    int height;

public:
    ProjectionPane(int width, int height);
    ProjectionPane(ProjectionPane &p);
    ProjectionPane(QImage &im);

    ~ProjectionPane();

    int getWidth();
    int getHeight();
    Rgb getPixel(int i, int j);
    void setPixel(int i, int j, Rgb color);

};

#endif // PROJECTIONPANE_H
