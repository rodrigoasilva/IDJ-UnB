#ifndef GAME_H 
#define GAME_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "State.h"


 
class Game
{
private:
   Game(string title , int width , int height );
   static Game* instance;
   SDL_Window* window;
   SDL_Renderer* renderer;
   State* state;
 
public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
 
};
#endif
