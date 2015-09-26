#ifndef RGB_H
#define RGB_H
#include <iostream>
#include <string>
#include <QtGui/QImage>
#include <QtGui/QColor>

using namespace std;

class Rgb
{
private:
    float r;
    float g;
    float b;

public:

    Rgb operator+(Rgb c);
    Rgb operator/(float f);
    Rgb Rgb::operator*(Rgb c);
    Rgb Rgb::operator*(float f);


    float Rgb::red();
    float Rgb::green();
    float Rgb::blue();
    void setRed(float r);
    void setGreen(float g);
    void setBlue(float b);
    ~Rgb();
    Rgb() {};
    Rgb(float r, float g, float b);
    Rgb(Rgb &co);
    Rgb(int colo);
    string Rgb::getString();
};

#endif // RGB_H
