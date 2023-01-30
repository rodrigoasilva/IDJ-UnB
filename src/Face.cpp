#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Face.h"

#include "Sound.h"
#include "Sprite.h"

Face::Face(GameObject& associated) : Component(associated){

  hitpoints = 30;

}

void Face::Damage(int damage){

   hitpoints-=damage;
   if(hitpoints<=0){
   
    static_cast<Sound*>(associated.GetComponent("Sound"))->Play(1);
    Sprite* sprite = static_cast<Sprite*>(associated.GetComponent("Sprite"));
    if (sprite != nullptr) {
      associated.RemoveComponent(sprite);
    Sprite* sprite =
        static_cast<Sprite*>(associated.GetComponent("Sprite"));
    if (sprite != nullptr) {
      Face::associated.RemoveComponent(sprite);
    }
   
      
  
   }
}
}

void Face::Update(float dt){

    if (hitpoints <= 0) {
    if (!(static_cast<Sound*>(associated.GetComponent("Sound"))->GetIsPlaying())) {
    if (!(static_cast<Sound*>(associated.GetComponent("Sound"))->
                                  GetIsPlaying())) {
      Face::associated.RequestDelete();
    }
  }


}}

void Face::Render(){


}

bool Face::Is(string type) {
  if (type.compare("Face") == 0) {
    return true;
  }
  return false;
}
bool Face::IsDead() {
  return hitpoints <= 0;
}