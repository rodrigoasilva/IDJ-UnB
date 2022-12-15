#ifndef STATE_H 
#define STATE_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include <vector>
#include <memory>


class State {
private:
 
   
   Music music;
   bool quitRequested;
   void Input();
   void AddObject(int mouseX  , int mouseY );
   vector<unique_ptr<GameObject>> objectArray;
public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
 
};
#endif