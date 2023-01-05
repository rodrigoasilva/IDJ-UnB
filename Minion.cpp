#include <cstdlib>
#include <iostream>
#include <ctime>
#include "SDL_include.h"
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Minion.h"
#include "Sprite.h"
#include "Component.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Game.h"
#include <queue>
#include <memory>
#include <stdlib.h> 
#include <vector>
#include <time.h> 

Minion::Minion( GameObject& associated , std::weak_ptr< GameObject > alienCenter,  float  arcOffsetDeg ) : Component(associated), alienCenter(*alienCenter.lock()), arc(arcOffsetDeg){
Sprite* sprite = new Sprite(associated, "img/minion.png");
 float scale = rand() / (float) RAND_MAX;
float random = 1.0 + scale * ( 1.5f -1.0f );
sprite->SetScale(random, random);
associated.AddComponent(sprite);

}

void Minion::Update(float dt){
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
  
  go->AddComponent(new Bullet(*go,angle, 300, 5,1000, "img/minionbullet1.png"));
 
  Game::GetInstance().GetState().AddObject(go);
    
} 