#include "primitive.h"


bool Primitive::sqrUravn(float a, float b, float c, float &t1, float &t2)
{
   float deskr = (b*b - 4*a*c);
   if (abs(deskr) < PRECISION)  deskr = 0;

   if (deskr < 0) return 0;

   t1 = (-b + sqrt(deskr)) / (2 * a);
   t2 = (-b - sqrt(deskr)) / (2 * a);

   if (deskr == 0) t2 = t1;
   return true;
}
