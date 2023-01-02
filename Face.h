#ifndef FACE_H 
#define FACE_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Component.h"

class Face : public Component{
private:
   int hitpoints;
 
public:
   explicit Face(GameObject& associated);
   void Damage(int damage);
   void  Update(float dt);
   void Render();
   bool Is(string type);
   bool IsDead();
};
#endif
