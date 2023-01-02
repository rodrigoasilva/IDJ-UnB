#ifndef CAMERA_H 
#define CAMERA_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "GameObject.h"



class Camera
{
private:
    static GameObject* focus;
   
public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);
    static Vec2 pos;
    static Vec2 speed;

   
};
#endif
