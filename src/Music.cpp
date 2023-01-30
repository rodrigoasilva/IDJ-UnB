#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#define INCLUDE_SDL_MIXER
#include <utility>
#include <Game.h>
#include <Resources.h>
#include <Music.h>

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
        Mix_PlayMusic(music.get(), times);
    else {
        cout << "No music loaded: " << SDL_GetError() << endl;
        exit(1);
    }
}

void Music::Stop(int msToStop) {

  Mix_FadeOutMusic(msToStop);

}

void Music::Open(string file) {


 music = Resources::GetMusic(move(file));
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