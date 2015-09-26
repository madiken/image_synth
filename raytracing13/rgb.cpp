#include "rgb.h"
#include <sstream>


Rgb::Rgb(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Rgb::Rgb(Rgb &co)
{
    this->r = co.red();
    this->g = co.green();
    this->b = co.blue();
}

Rgb Rgb::operator+(Rgb c){
    return Rgb(r+c.red(), g + c.green(), b + c.blue());
}

Rgb Rgb::operator*(Rgb c){
    return Rgb(r*c.red(), g*c.green(), b*c.blue());
}

Rgb Rgb::operator*(float f){
    return Rgb(r*f, g*f, b*f);
}

Rgb Rgb::operator/(float fl){
    return Rgb(r/fl, g/fl, b/fl);
}

float Rgb::red(){
    return r;
}

float Rgb::green(){
    return g;
}

float Rgb::blue(){
    return b;
}


void Rgb::setRed(float r)
{
    this->r = r;
}

void Rgb::setGreen(float g)
{
    this->g = g;
}

void Rgb::setBlue(float b)
{
    this->b = b;
}

Rgb::~Rgb(){

}

//delete this method
Rgb::Rgb(int colo){
    QColor qcolo = QColor(colo);
    r = qcolo.red();
    g = qcolo.green();
    b = qcolo.blue();

}

string Rgb::getString()
{
    ostringstream os;
    string s;

    os << r << " " << g << " " << b;
    s = os.str();
    return s;

}

