#include <cstdlib>
#include <iostream>
#include <ctime>
#include "SDL_include.h"
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Alien.h"
#include "Sprite.h"
#include "Camera.h"
#include "InputManager.h"
#include "Minion.h"
#include "Game.h"
#include "Bullet.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "Sound.h"


int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated),speed({0, 0}), hp(30){

    associated.AddComponent(new Sprite(associated, "img/alien.png"));
    associated.AddComponent(new Collider(associated));
    minionArray.resize((unsigned)(nMinions));
    nMinions = nMinions;
    alienCount++;
    state = RESTING;
    timeOffset = 1 + (rand()%11)/10;
   
}

Alien::~Alien(){

    minionArray.clear();
    alienCount--;
}


void Alien::Start(){


    auto minionSize = minionArray.size();
    for(int i = 0; i <  minionSize; i++){
        auto *minionGO = new GameObject;

        
         auto setor = (float)( (M_PI*i*(360.0/(float)minionSize))/180.0f);

        minionGO->AddComponent(new Minion(*minionGO,
                                          Game::GetInstance().GetCurrentState().GetObjectPtr(&associated),
                                          setor));

         minionArray[i] = (Game::GetInstance().GetCurrentState().AddObject(minionGO));
        restTimer = *new Timer;
}


}

void Alien::Update(float dt){

 Rect box = Alien::associated.box;
  
   Vec2 mousePos = Vec2(InputManager::GetInstance().GetMouseX(),
                       InputManager::GetInstance().GetMouseY());

  
  if (hp <=0) {
    auto deathalien(new GameObject());
    deathalien->AddComponent(new Sprite(*deathalien, "img/aliendeath.png", 4, 0.1, 0.4));
    deathalien->box.x = associated.box.GetCenter().x - deathalien->box.w/2;
    deathalien->box.y = associated.box.GetCenter().y - deathalien->box.h/2;

    auto explosionSound(new Sound(*deathalien, "audio/boom.wav"));
    deathalien->AddComponent(explosionSound);
    explosionSound->Play();

    Game::GetInstance().GetCurrentState().AddObject(deathalien);
    associated.RequestDelete();
  }
  else{


  

  associated.angleDeg += -2;



  PenguinBody *player = PenguinBody::player;
        if(player) {
            if (state == RESTING) {
                restTimer.Update(dt);
                if (restTimer.Get() > (3+timeOffset)) {
                    
                    state = MOVING;
                    restTimer.Restart();
                    timeOffset = 1 + (rand()%11)/10;
                    destination = player->GetPlayerCenter();
                    speed = Vec2(300, 0).Rotate((destination - associated.box.GetCenter()).InclX());
                
                }
            } else if (state == MOVING) {
                Vec2 deltaX = {300* dt, 0};
                Vec2 calculado = destination - Vec2(associated.box.x + (associated.box.w/2), associated.box.y + (associated.box.h/2));
                Vec2 real = deltaX.Rotate(calculado.InclX());

                
                if((calculado.Mag() < real.Mag())){
                    
                    associated.box += calculado;

                    auto pos = player->GetPlayerCenter();
                    float minionDS = minionArray[0].lock()->box.GetCenter().Dist(pos);

                    int nearestMinion = 0;

                    for (int i = 1; i < minionArray.size(); i++) {
                      if(minionArray[i].lock()->box.GetCenter().Dist(pos) < minionDS) {
                          nearestMinion = i;
                          minionDS = minionArray[i].lock()->box.GetCenter().Dist(pos);
                       }
                   }

      Minion* m = static_cast<Minion*>(minionArray[nearestMinion].lock()->GetComponent("Minion"));
      m->Shoot(pos);
      
                   
                    

                    state = RESTING;
                    Alien::restTimer.Restart();
                } else {
                    associated.box += real;
                }

            }
        }
    } 

  
  


}


void Alien::Render(){



}


bool Alien::Is(string type){

    if(type.compare("Alien") == 0){
        
        return true;
    }
    return false;
    

}



void Alien::NotifyCollision(GameObject& other){
 
 auto bullet = (Bullet*) other.GetComponent("Bullet");
 if (bullet && !bullet->targetsPlayer) {
        hp -= bullet->GetDamage(); 
    }


}