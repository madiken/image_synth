#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
private:
    int width;
    int height;
    int raysPerPixel;
    int recursionDepth;
    bool savehdr;
    int size;


public:
    Settings();
    int getWidth();
    int getHeight();
    int getRecursionDepth();
    int getRaysPerPixel();
    bool getSavehdr();
    int getSize();


    void setWidth(int w);
    void setHeight(int h);
    void setRecursionDepth(int d);
    void setRaysPerPixel(int r);
    void setSavehdr(bool fl);
    void setSize(int);


};

#endif // SETTINGS_H
