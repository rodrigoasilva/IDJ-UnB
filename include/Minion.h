#ifndef MINION_H 
#define MINION_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Component.h"
#include "GameObject.h"
#include <queue>
#include <memory>
#include <vector>


class Minion : public Component {

private:

    GameObject& alienCenter;
    float arc;

public:

    Minion(GameObject& associated,std::weak_ptr< GameObject > alienCenter,  float arcOffsetDeg=0);
    void Update(float dt);
    void Render();
    bool Is(string type);
    void Shoot(Vec2 target);
    void NotifyCollision(GameObject& other);


};
#endif