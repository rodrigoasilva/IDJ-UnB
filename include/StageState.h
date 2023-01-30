#ifndef STAGESTATE_H 
#define STAGESTATE_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "State.h"
#include "TileSet.h"
#include "Music.h"

class StageState : public State {

public:

    StageState();
    ~StageState();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
private:
    TileSet* tileSet;
    Music backgroundMusic; 


};
#endif