#include <cstdlib>
#include <iostream>
#include <ctime>
#include "SDL_include.h"
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Timer.h"


Timer::Timer() : timer(0){



}

void Timer::Update(float dt){

 timer += dt;
}

void Timer::Restart(){

 timer = 0;
}

float Timer::Get(){

return timer;

}