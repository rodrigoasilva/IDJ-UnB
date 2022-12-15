#ifndef COMPONENT_H 
#define COMPONENT_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "GameObject.h"


class GameObject;
class Component
{
protected:
   GameObject& associated;
 
public:
   explicit Component(GameObject& associated);
   virtual ~Component();
   virtual void  Update(float dt) = 0;
   virtual void Render() =0;
   virtual bool Is(string type) =0;
};
#endif
