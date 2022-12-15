#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Sound.h"
#include "GameObject.h"
#include "Component.h"

class GameObject;

Sound::Sound(GameObject  &associated): Component(associated), chunk(nullptr){

channel = -1;

}


Sound::Sound(GameObject  &associated,string file): Sound(associated){

Open(file.c_str());

}

void Sound::Play(int times){

    channel = Mix_PlayChannel( -1 ,  chunk, times-1);
    if (channel == -1) {
    SDL_Log("Mix_PlayChannel: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

}

void Sound::Stop(){

    if(chunk!=nullptr){

 if(Mix_HaltChannel(channel) != 0) {
      SDL_Log("Mix_HaltChannel: %s", SDL_GetError());
      exit(EXIT_FAILURE);
    }

    }
}

void Sound::Open(string file) {
    
    chunk = Mix_LoadWAV(file.c_str());
    if(chunk==nullptr){

           SDL_Log("Mix_LoadWAV: %s", SDL_GetError());
          exit(EXIT_FAILURE);
    }
}

Sound::~Sound(){

    Stop();
    Mix_FreeChunk(chunk);
    

}

void Sound::Update(float dt) {}

void Sound::Render() {}
bool Sound::GetIsPlaying() {
  return Mix_Playing(channel) > 0;
}
    
bool Sound::Is(string type) {
  if (type.compare("Sound") == 0) {
    return true;
  }
  return false;
}

