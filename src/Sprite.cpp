#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "Game.h"
#include "State.h"
#include "Sprite.h"


Sprite::Sprite() : texture(nullptr){


 

}

Sprite::Sprite (string file) : texture(nullptr) {

   Open(file);
}

Sprite::~Sprite() {

   if(texture!=nullptr){

        SDL_DestroyTexture(texture);
   }

}

void Sprite::Open(string file) {

   if(texture==nullptr){

        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(),file.c_str());

        if(texture!=nullptr){

             SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
           
             SetClip(0, 0, width, height);
        }

        else{

          cout << "error" <<endl;
        }
   }
    
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


  SDL_RenderCopy(Game::GetInstance().GetRenderer(),texture, &clipRect , &dstrect);
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