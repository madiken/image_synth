#include "settings.h"

Settings::Settings()
{

}

int Settings::getWidth()
{
    return this->width;
}

int Settings::getHeight()
{
    return this->height;
}

int Settings::getRecursionDepth()
{
    return this->recursionDepth;
}

int Settings::getRaysPerPixel()
{
    return raysPerPixel;
}

bool Settings::getSavehdr()
{
    return savehdr;
}


int Settings::getSize()
{
    return size;
}


void Settings::setWidth(int w)
{
    width = w;
}

void Settings::setHeight(int h)
{
    height = h;
}

void Settings::setRecursionDepth(int d)
{
    recursionDepth = d;
}

void Settings::setRaysPerPixel(int r)
{
    raysPerPixel = r;
}

void Settings::setSavehdr(bool fl)
{
    savehdr = fl;
}


void Settings::setSize(int s)
{
    size = s;
}
