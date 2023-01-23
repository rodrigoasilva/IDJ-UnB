#ifndef TIMER_H 
#define TIMER_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


class Timer {

private:
    float timer;

public: 

    Timer();
    void Update(float dt);
    void Restart();
    float Get();

};
#endif