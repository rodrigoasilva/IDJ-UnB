#include <cstdlib>
#include <iostream>
#include <ctime>
#include "SDL_include.h"
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Game.h"
#include <queue>
#include <memory>
#include <vector>


Alien::Alien(GameObject& associated, int nMinions) : Component(associated),speed({0, 0}), hp(30){

    associated.AddComponent(new Sprite(associated, "img/alien.png"));
    minionArray.resize((unsigned)(nMinions));
    nMinions = nMinions;
    
}

Alien::~Alien(){

    minionArray.clear();

}


void Alien::Start(){


    auto minionSize = minionArray.size();
    for(int i = 0; i <  minionSize; i++){
        auto *minionGO = new GameObject;

        
         auto setor = (float)( (M_PI*i*(360.0/(float)minionSize))/180.0f);

        minionGO->AddComponent(new Minion(*minionGO,
                                          Game::GetInstance().GetState().GetObjectPtr(&associated),
                                          setor));

         minionArray[i] = (Game::GetInstance().GetState().AddObject(minionGO));

}


}

void Alien::Update(float dt){

 Rect box = Alien::associated.box;
  
  /*if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
    Alien::taskQueue.push(Action(Action::SHOOT, mousePos.x, mousePos.y));
  }*/
  
   Vec2 mousePos = Vec2(InputManager::GetInstance().GetMouseX(),
                       InputManager::GetInstance().GetMouseY());
  
  if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)) {
    Alien::taskQueue.push(Action(Action::MOVE,
                                 mousePos.x,
                                 mousePos.y));
  }  

  if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
    Alien::taskQueue.push(Action(Action::SHOOT,
                                 mousePos.x,
                                 mousePos.y));
  }   

  if(!taskQueue.empty()){
  if(taskQueue.front().type == Action::SHOOT){
    Vec2 pos = Alien::taskQueue.front().pos;
    float minionDS = minionArray[0].lock()->box.GetCenter().Dist(pos);
    int nearestMinion = 0;

    for (int i = 1; i < minionArray.size(); i++) {
      if(minionArray[i].lock()->box.GetCenter().Dist(pos) < minionDS) {
        nearestMinion = i;
        minionDS = minionArray[i].lock()->box.GetCenter().Dist(pos);
      }
    }

    Minion* m = static_cast<Minion*>(minionArray[nearestMinion].lock()->GetComponent("Minion"));
    m->Shoot(pos+ Vec2(Camera::pos.x,Camera::pos.y));
    taskQueue.pop();


  }

  else if(taskQueue.front().type == Action::MOVE){ 

    Vec2 deltaX = {500 * dt, 0};
    Vec2 calculado = taskQueue.front().pos - Vec2(associated.box.x + (associated.box.w/2), associated.box.y + (associated.box.h/2)) + Vec2(Camera::pos.x,Camera::pos.y);
    Vec2 real = deltaX.Rotate(calculado.InclX());
    
      
    if(calculado.Mag() < real.Mag()){
        //chegou em destination
        associated.box += calculado;
        taskQueue.pop();      
    }
    else{   
        associated.box += real;
    }
              
  }}
}


void Alien::Render(){



}


bool Alien::Is(string type){

    if(type.compare("Alien") == 0){
        
        return true;
    }
    return false;
    

}

Alien::Action::Action(ActionType type, float x, float y) {
  Action::type = type;
  pos = Vec2(x, y);
}