#ifndef GAME_H 
#define GAME_H 
using namespace std;
#include "SDL_include.h"
#include "State.h"


 
class Game
{
private:
   Game(string title , int width , int height );
   static Game* instance;
   SDL_Window* window;
   SDL_Renderer* renderer;
   State* state;
   int frameStart;
   float dt;
   void CalculateDeltaTime();
 
public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
    float GetDeltaTime();
 
};
#endif
