#include "vector3.h"
#include <math.h>
#include <sstream>

vector3::vector3()
{}

vector3::~vector3()
{
  //  cout << "~vector3() :" << getString() << endl;
}


vector3::vector3(float x1, float y1, float z1)
{
    x = x1;
    y = y1;
    z = z1;
}

vector3::vector3(vector3 &v)
{
   // cout << " vector3::vector3(vector3 &v) : "  << getString() << endl;
    x = v.x;
    y = v.y;
    z = v.z;
}


vector3 vector3::operator+(vector3 vVector)
{
    return vector3(vVector.x + x, vVector.y + y, vVector.z + z);
}


vector3 vector3::operator+(float num)
{
    return vector3(x + num, y + num, z + num);
}

vector3 vector3::operator-(float num)
{
    return vector3(x - num, y - num, z - num);
}


vector3 vector3::operator-(vector3 vVector)
{
    return vector3(x-vVector.x, y-vVector.y, z-vVector.z);
}

vector3 vector3::operator*(float n)
{
    return vector3(x*n, y*n, z*n);
}

float vector3::operator*(vector3 vVector)
{
    return (x*vVector.x + y*vVector.y + z*vVector.z);
}


vector3 vector3::operator/(float num)
{
        return vector3(x/num,y/num,z/num);
}




float vector3::length()
{
    return (sqrt(x*x + y*y + z*z));

}

vector3 vector3::normalize()
{
    return (this->operator/(this->length()));
}

string vector3::getString()
{
    ostringstream os;
    string s;

    os << x << " " << y << " " << z;
    s = os.str();
    return s;

}

 vector2 vector3::oxzProjection()
 {
     return vector2(this->x, this->z);
 }

