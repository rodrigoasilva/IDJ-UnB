#include <cstdlib>
#include <iostream>
#include <ctime>
#include "SDL_include.h"
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Bullet.h"
#include "Sprite.h"
#include "Vec2.h"
#include <queue>
#include <memory>
#include <vector>
#include "Collider.h"

Bullet::Bullet( GameObject& associated, float angle, float speed, int damage , float maxDistance,string sprite , int frameCount ,float frameTime) : Component(associated),damage(damage){

associated.AddComponent(new Sprite(associated, sprite,frameCount,frameTime));
associated.AddComponent(new Collider(associated));
associated.angleDeg = angle;


    this->speed = Vec2(speed, 0).RotateDeg(angle);
    this->distanceLeft = maxDistance;


}

void Bullet::Update(float dt){

    associated.box += speed * dt;
    distanceLeft -= (speed * dt).Mag();
    if(distanceLeft < 0){
        associated.RequestDelete();
    }
    

}

void Bullet::Render(){



}

bool  Bullet::Is(string type){

     if(type.compare("Bullet") == 0){
        
        return true;
    }
    return false;
}

int Bullet::GetDamage(){

 return damage;

}

void Bullet::NotifyCollision(GameObject& other){

if((other.GetComponent("Alien") && !targetsPlayer) || (other.GetComponent("PenguinsBody") && targetsPlayer)){
        associated.RequestDelete();
    }

}

