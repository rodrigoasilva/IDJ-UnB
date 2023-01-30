#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

#define INCLUDE_SDL
#include "SDL_include.h"
#include <Resources.h>
#include <Camera.h>

#include <utility>
#include <Bullet.h>
#include <Sprite.h>
#include "Game.h"


Sprite::Sprite(GameObject& associated) : Component(associated),texture(nullptr){


     width = 0;
     height = 0;
     frameCount = 0;
     frameTime = 0;
     timeElapsed =0;
     currentFrame =0;
     secondsToSelfDestruct =0;
     scale = Vec2 (1,1);

 

}

Sprite::Sprite(GameObject& associated,string file,int frameCount, float frameTime, float secondsToSelfDestruct) : Sprite(associated){
  this->frameCount = frameCount;
  this->frameTime = frameTime;
  this->secondsToSelfDestruct = secondsToSelfDestruct;
  Open(file);
  
  associated.box.w = Sprite::width/frameCount;
  associated.box.h = Sprite::height;


}

Sprite::~Sprite() {


}

void Sprite::Open(string file) {

  
 texture = Resources::GetImage(move(file));

  /* Loads texture. */
SDL_QueryTexture(texture.get(),nullptr,nullptr,&width,&height);

  /* Clips texture. */
  SetClip(0, 0, Sprite::width/frameCount, Sprite::height);
    
}

void Sprite::SetClip( int x , int y , int w ,  int h) {
  
    clipRect.x = x;
    clipRect.y = y;
    clipRect.h = h; 
    clipRect.w = w;

}

void Sprite::Render(int x ,  int y) {
  
   
 
  SDL_Rect dstrect;
  
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = clipRect.w;
  dstrect.h = clipRect.h;

  SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture.get(), &clipRect , &dstrect,associated.angleDeg,nullptr,SDL_FLIP_NONE);
}



int Sprite::GetHeight() {

  return (int)(height);
}


bool Sprite::IsOpen() {

     return texture != nullptr;

}

void Sprite::Update(float dt) {

      if(secondsToSelfDestruct > 0){
        selfDestructCount.Update(dt);
        if(selfDestructCount.Get() > secondsToSelfDestruct){
            associated.RequestDelete();
        }
    }


  timeElapsed += dt;
    if(timeElapsed >= frameTime){
        if(++currentFrame >= frameCount){
            currentFrame = 0;
        }
        SetFrame(currentFrame);
        timeElapsed = 0;
    }
}
bool Sprite::Is(std::string type) {
  if (type.compare("Sprite") == 0) {
    return true;
  }
  return false;
}

void Sprite::Render() {

  Render(associated.box.x - Camera::pos.x,associated.box.y - Camera::pos.y);
  
}

void Sprite::SetScale(float scaleX, float scaleY) {
    auto &box = associated.box;
    if(scaleX != 0){
        scale.x = scaleX;
        box.w = width * scaleX;
        box.x = box.GetCenter().x - box.w/2;
    }

    if(scaleY != 0){
        scale.y = scaleY;
        box.h = height * scaleY;
        box.y = box.GetCenter().y - box.h/2;
    }
}

Vec2 Sprite::GetScale() {
    return scale;
}

void Sprite::SetFrame(int frame){

  this->currentFrame = frame;
  SetClip(frame * GetWidth(), 0, clipRect.w, clipRect.h);

}
void Sprite::SetFrameCount(int frameCount){

    this->frameCount = frameCount;
    associated.box.w = GetWidth();
    SetClip(0, clipRect.y, GetWidth(), clipRect.h);

}

void Sprite::SetFrameTime(float frameTime){

  this->frameTime = frameTime;

}

int Sprite::GetWidth(){

return (int)(width/frameCount);

}