#ifndef GAME_H 
#define GAME_H 
using namespace std;
#include "SDL_include.h"
#include <stack>
#include "State.h"


 
class Game
{
private:
  
   static Game* instance;
   SDL_Window* window;
   SDL_Renderer* renderer;
   State* storedState;
   int frameStart;
   float dt;
   void CalculateDeltaTime();
   stack<unique_ptr<State>> stateStack;
 
public:
    Game(string title , int width , int height );
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetCurrentState();
    void Push(State *state);
    static Game& GetInstance();
    float GetDeltaTime();
 
};
#endif
