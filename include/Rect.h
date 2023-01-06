#ifndef RECT_H 
#define RECT_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <memory>
#include "Vec2.h"
 
class Rect
{

 
public:
  float x,y,w,h;

  Rect();
  Rect(float x, float y, float w, float h);

  Rect SumVec2(Vec2 v);
  Rect SubVec2(Vec2 v);
  Rect MulVec2(Vec2 v);
  void SetPos(Vec2 pos);
  Vec2 GetPos();
  Vec2 GetCenter();

  float DistRecs(Rect r);
  float DistVec2(Vec2 v);
  bool Contains(Vec2 v);

  Rect operator+(Vec2 offset);
  Rect operator+=(Vec2 v);

  Rect operator*(Vec2 scale);
  Rect operator*=(Vec2 scale);
 
};
#endif