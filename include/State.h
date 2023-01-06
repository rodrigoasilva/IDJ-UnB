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
#include "GameObject.h"
#include <algorithm>
#include <string>


class State {
private:
 
   bool started;
   Music music;
   bool quitRequested;
   void AddObject(int mouseX  , int mouseY );
   std::vector<std::shared_ptr<GameObject>> objectArray;
public:
    State();
    ~State();
    void Start();
    std::weak_ptr< GameObject > AddObject(GameObject* go);
    std::weak_ptr< GameObject > GetObjectPtr(GameObject* go);
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
 
};
#endif