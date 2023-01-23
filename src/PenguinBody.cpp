#include <cstdlib>
#include <iostream>
#include <ctime>
#include "SDL_include.h"
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "PenguinBody.h"
#include "Sprite.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"
#include "Collider.h"
#include "Camera.h"
#include "Bullet.h"
#include "Sound.h"

PenguinBody* PenguinBody::player;



PenguinBody::PenguinBody(GameObject &associated) : Component(associated),speed(0, 0), linearSpeed(0), angle(0), hp(100){



associated.AddComponent(new Sprite(associated, "img/penguin.png"));
associated.AddComponent(new Collider(associated));

player = this;

}

PenguinBody::~PenguinBody(){
player = nullptr;
}

void  PenguinBody::Start(){

    auto *pcannonGO = new GameObject;
    pcannonGO->AddComponent(new PenguinCannon(*pcannonGO,Game::GetInstance().GetState().GetObjectPtr(&associated)));

    pcannon = Game::GetInstance().GetState().AddObject(pcannonGO);




}


void  PenguinBody::Update(float dt){

     
     if(hp <=0) {
     
    associated.RequestDelete();
    (*pcannon.lock()).RequestDelete();
    Camera::Unfollow();


    auto penguindeath(new GameObject());
    penguindeath->AddComponent(new Sprite(*penguindeath, "img/penguindeath.png", 5, 0.1, 0.5));
    penguindeath->box.x = associated.box.GetCenter().x - penguindeath->box.w/2;
    penguindeath->box.y = associated.box.GetCenter().y - penguindeath->box.h/2;;

    auto explosionSound(new Sound(*penguindeath, "audio/boom.wav"));
    penguindeath->AddComponent(explosionSound);
    explosionSound->Play();
    Game::GetInstance().GetState().AddObject(penguindeath);
    
  }

    
    if(InputManager::GetInstance().IsKeyDown(W_KEY) || InputManager::GetInstance().IsKeyDown(S_KEY)) {
        if (InputManager::GetInstance().IsKeyDown(W_KEY) && linearSpeed < 25) {
            linearSpeed += 600 * dt * dt / 2;
        }

        if (InputManager::GetInstance().IsKeyDown(S_KEY) && linearSpeed > -25) {
            linearSpeed -= 600 * dt * dt / 2;
        }
    }
    
    else {
        
        if(abs(linearSpeed) < 2) {
            linearSpeed = 0;
        }

        if (linearSpeed > 0) {
            linearSpeed -= 400 * dt * dt / 2;
        } else if (linearSpeed < 0) {
            linearSpeed += 400 * dt * dt / 2;
        }
    }

    if (InputManager::GetInstance().IsKeyDown(A_KEY)){
        angle -= 200 * dt;
    }

    if (InputManager::GetInstance().IsKeyDown(D_KEY)){
        angle += 200* dt;
    }

    Rect borders = {0, 0, 1408, 1280};
    if(associated.box.x > borders.w - associated.box.w){
        associated.box.x = borders.w - associated.box.w;
    } else if(associated.box.x < 0){
        associated.box.x = 0;
    }

    if(associated.box.y > borders.h - associated.box.h){
        associated.box.y = borders.h - associated.box.h;
    } else if(associated.box.y < 0){
        associated.box.y = 0;
    }

    associated.angleDeg = angle;
    speed = Vec2(linearSpeed , 0).RotateDeg(angle);
    associated.box += speed;

     


 }

void  PenguinBody::Render(){






} 

bool PenguinBody::Is(string type){

    if(type.compare("PenguinBody") == 0){
        
        return true;
    }
    return false;


}

void PenguinBody::NotifyCollision(GameObject& other){

    auto enemyBullet = (Bullet*) other.GetComponent("Bullet");

    if (enemyBullet && enemyBullet->targetsPlayer) {
        hp -= enemyBullet->GetDamage();
    }

}

Vec2 PenguinBody::GetPlayerCenter() {
	return associated.box.GetCenter();
}