#ifndef VEC2_H 
#define VEC2_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <memory>


class Vec2
{

 
public:
    float x,y;
    Vec2();
    Vec2(float x, float y);

    Vec2 Sum(Vec2 v);
    Vec2 Sub(Vec2 v);
    Vec2 Mul(const float escalar);
    float Mag();
    Vec2 Norm();
    float Dist(Vec2 v);
    float InclX();
    float InclXDeg();
    float Incl(Vec2 v);

    Vec2 Rotate(const float ang);
    Vec2 RotateDeg(const float angDeg);

    Vec2 operator+(const Vec2& v);
    Vec2 operator+(const Vec2& v) const;

    Vec2 operator-(const Vec2& v);
    Vec2 operator-(const Vec2& v) const;

    Vec2 operator*(const float escalar);
    Vec2 operator*(const float escalar) const;

    bool operator==(const Vec2& v);

    Vec2 operator+=(const Vec2& v);
    Vec2 operator-=(const Vec2& v);


 
};
#endif