#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#define INCLUDE_SDL_MIXER
#include "Game.h"
#include "State.h"
#include "Sprite.h"
#include "Music.h"
#include "Resources.h"

Music::Music() : music(nullptr){


}

void Music::Volume(int volume){
    Mix_VolumeMusic(volume);
}

Music::Music(string file) : music(nullptr) {
    

  Open(file);
}

void Music::Play( int times) {

     
     
      if (music != nullptr)
        Mix_PlayMusic(music, times);
    else {
        cout << "No music loaded: " << SDL_GetError() << endl;
        exit(1);
    }

}

void Music::Stop(int msToStop) {

  Mix_FadeOutMusic(msToStop);

}

void Music::Open(string file) {

music = Mix_LoadMUS(file.c_str());
 if (Music::music == nullptr) {
    SDL_Log("Unable to load music Mix_LoadMUS: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  Music::music = Resources::GetMusic(file);
}

bool Music::IsOpen(){

    if (Music::music != nullptr) {
    return true;
  }
  return false;

}

Music::~Music() {
    Stop(0);

}