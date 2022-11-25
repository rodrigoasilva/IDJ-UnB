#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "Game.h"
#include "State.h"

State::State() : music("audio/stageState.ogg") , bg("img/ocean.jpg") {

    quitRequested = false;
    music.Volume(10);
    music.Play(-1);
}

void State::LoadAssets() {


}

void State::Update(float dt) {

   
 if( SDL_QuitRequested() == true ){
     music.Stop();
     quitRequested = true;
 }

}

void State::Render() {

    bg.Render(0,0);
}

bool State::QuitRequested() {
    return quitRequested;
}


