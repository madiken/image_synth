#ifndef VECTOR2_H
#define VECTOR2_H

class vector2
{
public:
    float x;
    float y;

    vector2();
    vector2(float x, float y);
    vector2(vector2 &v);
    vector2 operator+(vector2 v);
    vector2 operator-(vector2 v);


    void rotate(vector2 v, float alpha);
};

#endif // VECTOR2_H
