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

}

bool Music::IsOpen(){

return music != nullptr;

}

Music::~Music() {
    Stop(0);

}