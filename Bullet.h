#ifndef BULLET_H 
#define BULLET_H 
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


class Bullet : public Component{


private:
    Vec2 speed;
    float distanceLeft;
    int damage;



public:
    Bullet(GameObject& associated,  float angle ,float speed, int damage, float maxDistance, string  sprite);
    void Update(float dt);
    void Render();
    bool Is(string type);
    int GetDamage();
   




};
#endif