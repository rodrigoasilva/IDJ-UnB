#ifndef TITLESTATE_H 
#define TITLESTATE_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "State.h"

class TitleState : public State {

public:

    TitleState();
    ~TitleState();
    void LoadAssets();
    void Update(float dt);
    void Render(); 
    void Start();
    void Resume();
    void Pause();

};
#endif