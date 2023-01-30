#ifndef ALIEN_H 
#define ALIEN_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Component.h"
#include "Timer.h"
#include <queue>
#include <memory>
#include <vector>


class Alien : public Component{
private:
   Vec2 speed;
   int hp;
   enum AlienState { MOVING, RESTING };
   AlienState state;
   Timer restTimer;
   Vec2 destination;
   std::vector< std::weak_ptr<GameObject> > minionArray;
   float timeOffset;
   
 
public:
   Alien(GameObject& associated, int nMinions);
   ~Alien();
   void Start();
   void Update(float dt);
   void Render();
   bool Is(string type);
   void NotifyCollision(GameObject& other);
   static int alienCount;

};
#endif