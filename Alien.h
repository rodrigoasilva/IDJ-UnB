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
#include "Vec2.h"
#include <queue>
#include <memory>
#include <vector>

class Alien : public Component{
private:
   Vec2 speed;
   int hp;
   class Action{
    public: 
        
        enum ActionType { MOVE, SHOOT };
        ActionType type;
        Action(ActionType type, float x,  float y);
        Vec2 pos;
   
   };
   queue<Action> taskQueue;
   std::vector< std::weak_ptr<GameObject> > minionArray;
   
 
public:
   Alien(GameObject& associated, int nMinions);
   ~Alien();
   void Start();
   void Update(float dt);
   void Render();
   bool Is(string type);

};
#endif