#include <cstdlib>
#include <iostream>
#include <ctime>
#include "SDL_include.h"
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include <Sprite.h>
#include <Game.h>
#include <Collider.h>
#include <Bullet.h>
#include <Sound.h>
#include "Minion.h"

Minion::Minion( GameObject& associated , std::weak_ptr< GameObject > alienCenter,  float  arcOffsetDeg ) : Component(associated), alienCenter(*alienCenter.lock()), arc(arcOffsetDeg){
Sprite* sprite = new Sprite(associated, "img/minion.png");
 float scale = rand() / (float) RAND_MAX;
float random = 1.0 + scale * ( 1.5f -1.0f );
sprite->SetScale(random, random);
associated.AddComponent(sprite);

}

void Minion::Update(float dt){



   if((alienCenter.IsDead())){

        

        associated.RequestDelete();
    }
    arc +=  M_PI/4* dt;
    Vec2 raioOrbita = Vec2(150, 30).Rotate(arc);
    Vec2 distOrigem = alienCenter.box.GetCenter();

   
    associated.box += raioOrbita - associated.box.GetCenter() + distOrigem;
    associated.angleDeg = raioOrbita.InclX() * 180 / M_PI;
}


void Minion::Render(){


}

bool Minion::Is(string type){

    if(type.compare("Minion") == 0){
        
        return true;
    }
    return false;

}


void Minion::Shoot(Vec2 target){

  
  
  GameObject* go = new GameObject();
  go->box.x = associated.box.GetCenter().x - go->box.w/2;
  go->box.y = associated.box.GetCenter().y - go->box.h/2;

    float angle = (target - associated.box.GetCenter()).InclXDeg();
  
  Bullet* bullet = new Bullet(*go,angle, 300, 5,1000, "img/minionbullet2.png",3,0.33);
  bullet->targetsPlayer = true;
  go->AddComponent(bullet);

  
  Game::GetInstance().GetCurrentState().AddObject(go);
    
} 

void Minion::NotifyCollision(GameObject& other){



}