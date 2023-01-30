#include <cstdlib>
#include <iostream>
#include <ctime>
#include "SDL_include.h"
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include <Sprite.h>
#include <InputManager.h>
#include <Game.h>
#include <Bullet.h>
#include <Collider.h>
#include <Timer.h>
#include <Sound.h>
#include "PenguinCannon.h"


PenguinCannon::PenguinCannon(GameObject& associated,std::weak_ptr< GameObject > penguinBody): Component(associated){
angle = 0;
associated.AddComponent(new Sprite(associated, "img/cubngun.png"));
associated.AddComponent(new Collider(associated));
pbody = penguinBody;
cooldown = Timer();
}

void PenguinCannon::Update(float dt){

GameObject &body = *pbody.lock();

if(body.IsDead()){
        associated.RequestDelete();
    }

   

    associated.box = body.box;
    associated.angleDeg = (Vec2(InputManager::GetInstance().GetMouseX(),InputManager::GetInstance().GetMouseY()) - associated.box.GetCenter()).InclXDeg();
    angle = (float)associated.angleDeg;

    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
       
           if(cooldown.Get() >= 0.01){
            Shoot();
            cooldown.Restart();
        }
            
      cooldown.Update(dt);
    }
   

}

void PenguinCannon::Render(){



}
bool PenguinCannon::Is(string type){

    if(type.compare("PenginCannon") == 0){
        
        return true;
    }
    return false;




}
void PenguinCannon::Shoot(){

auto bulletGo = new GameObject;
    auto offset = Vec2(associated.box.w/2, 0).RotateDeg(angle);

    bulletGo->box.x = associated.box.GetCenter().x - bulletGo->box.w/2 + offset.x;
    bulletGo->box.y = associated.box.GetCenter().y - bulletGo->box.h/2 + offset.y;
    Bullet* bullet =new Bullet(*bulletGo, angle, 300, 10, 1000, "img/penguinbullet.png", 4, 0.1);
    bullet->targetsPlayer = false;
    bulletGo->AddComponent(bullet);
    
    Game::GetInstance().GetCurrentState().AddObject(bulletGo);


}

void PenguinCannon::NotifyCollision(GameObject& other){



}