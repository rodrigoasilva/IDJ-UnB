#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "Game.h"
#include "State.h"
#include "Sprite.h"
#include "Resources.h"
#include "Camera.h"


Sprite::Sprite(GameObject& associated) : Component(associated),texture(nullptr){


     width = 0;
     height = 0;
 

}

Sprite::Sprite(GameObject& associated,string file) : Component(associated),texture(nullptr){

   Open(file);
  
  associated.box.w = Sprite::width;
  associated.box.h = Sprite::height;


}

Sprite::~Sprite() {

   if(texture!=nullptr){

        SDL_DestroyTexture(texture);
   }

}

void Sprite::Open(string file) {

if (Sprite::texture != nullptr) {
    SDL_DestroyTexture(Sprite::texture);
  }
  Sprite::texture = Resources::GetImage(file);
  /* Loads texture. */
  Sprite::texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(),
                                    file.c_str());
  if (Sprite::texture == nullptr) {
    SDL_Log("Unable to initialize Texture: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
if (SDL_QueryTexture(Sprite::texture,
                       nullptr,
                       nullptr,
                       &width,
                       &height) != 0) {
    SDL_Log("Unable to initialize Query Texture: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  /* Clips texture. */
SetClip(0, 0, Sprite::width, Sprite::height);
  SetClip(0, 0, Sprite::width, Sprite::height);
    
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


  SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture, &clipRect , &dstrect,associated.angleDeg,NULL,SDL_FLIP_NONE);
}

int Sprite::GetWidth() {

   return (int)(width);
}

int Sprite::GetHeight() {

     return (int)(height);
}


bool Sprite::IsOpen() {

     return texture != nullptr;

}

void Sprite::Update(float dt) {
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