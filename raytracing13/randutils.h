#ifndef RANDUTILS_H
#define RANDUTILS_H
#include "vector3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


class RandUtils
{
public:
    RandUtils();


    static void setupRand()
    {
        int stime;
        long ltime;

        /* получает текущее календарное время */
        ltime = time(NULL);
        stime = (unsigned) ltime/2;
        srand(stime);
    }


    static float getPixelDisplacement(int perPixel)
    {
        float res = (rand()%perPixel);
        return (float)res/(float)perPixel;
    }

    static vector3 getRandomDirection(vector3 normal)
    {
        float x = rand();
        float y = rand();
        float z = rand();

        vector3 result = vector3(x, y, z);
        result = result.normalize();
/*
        if (result*normal < 0){
            result.x = -result.x;
        }
        if (result*normal < 0){
            result.y = -result.y;
        }
        if (result*normal < 0){
            result.z = -result.z;
        }
*/

        int basis[3];
        basis[0] = 0;//x
        basis[1] = 1;//y
        basis[2] = 2;//z


        if (result*normal < 0){
             arraymess(basis, 3);



            for (int i = 0; i < 3; i++)
            {
               if (basis[i] == 0){
                    if (result*normal < 0){
                        result.x = -result.x;
                        continue;

                    }

               }
               else if (basis[i] == 1){
                    if (result*normal < 0){
                        result.y = -result.y;
                         continue;
                    }
               }

               else if (basis[i] == 2){
                    if (result*normal < 0){
                        result.z = -result.z;
                         continue;
                    }
               }

            }
        }
     return result;
    }


    static int getZeroOrOne()
    {
        int n = 100;
        float r = rand()%n;

        r = (float)r/(float)n;
        if (r < 0.5) return 0;
        else return 1;
    }

    static bool ifDiffuseIsChosen(float spec, float diff)
    {
        //random value [0,1]
        int n = 100;
        float randomValue = rand()%n;

        randomValue = (float)randomValue/(float)n;


        float incident = spec/(spec + diff);
        if (randomValue > incident) return true; //diffuse
        else return false;



    }

    static void arraymess(int *ar, int size)
    {
        int index;
        for (int i = 0; i < size; i++)
        {
             index = rand()%size;
              int tmp = ar[i];
              ar[i] = ar[index];
              ar[index] = tmp;
        }
    }
};

#endif // RANDUTILS_H
