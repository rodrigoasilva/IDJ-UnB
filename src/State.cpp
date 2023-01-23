#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "Game.h"
#include "State.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include <math.h>
#include "Vec2.h"
#include "Sound.h"
#include "Alien.h"
#include "Minion.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Rect.h"
#include <stack>
#include "PenguinBody.h"
#include "Collider.h"
#include "Collision.h"



State::State()  : music(Music()),started(false){

 State::started = false;
  GameObject* bg = new GameObject();
  bg->box.x = 0;
  bg->box.y = 0;
  bg->AddComponent(new Sprite(*bg, "img/ocean.jpg"));
  bg->AddComponent(new CameraFollower(*bg));
 
  objectArray.emplace_back(bg);
  
  

 


  GameObject* tileMap = new GameObject();
  TileSet* tileSet = new TileSet(64, 64, "img/tileset.png");
  tileMap->box.x = 0;
  tileMap->box.y = 0;
  tileMap->AddComponent(new TileMap(*tileMap, "map/tileMap.txt", tileSet));
  objectArray.emplace_back(tileMap);
  GameObject* go = new GameObject();
  go->AddComponent(new Alien(*go, 8));
  go->box.SetPos(Vec2(512 - go->box.w/2, 300 - go->box.h/2));
  go->box.x = 512 - go->box.w/2;
  go->box.y = 300 - go->box.h/2;
  AddObject(go);
  go = new GameObject();
  go->AddComponent(new PenguinBody(*go));
  go->box.x = 704;
  go->box.y = 640;
  Camera::Follow(go);



  AddObject(go);

 


  quitRequested = false;

}

void State::LoadAssets() {

	music.Open("audio/stageState.ogg");
    music.Play();

}

void State::Update(float dt){
  


  int mouseX, mouseY;

  

  SDL_GetMouseState(&mouseX, &mouseY);
  Camera::Update(dt);  
  State::quitRequested = InputManager::GetInstance().QuitRequested();

	
  if(InputManager::GetInstance().KeyPress(SDLK_ESCAPE)) {
				quitRequested = true;
			} 

  if(InputManager::GetInstance().MousePress(SDL_QUIT)) {
				quitRequested = true;
			} 
	 
		
  for (int i = (int)objectArray.size() - 1; i >= 0; i--) {
    State::objectArray.at(i)->Update(dt);
  }
 

  for(int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }


   for (int i = 0; i < objectArray.size(); i++) {
        for(int j = i+1; j < objectArray.size(); j++){
            auto &objA = objectArray[i];
            auto &objB = objectArray[j];

            Collider *colliderA = (Collider*) objA->GetComponent("Collider");
            Collider *colliderB = (Collider*) objB->GetComponent("Collider");
            if(colliderA && colliderB){
                auto boxA = colliderA->box;
                auto boxB = colliderB->box;

                auto angleOfA = (float)(objA->angleDeg);
                auto angleOfB = (float)(objB->angleDeg);

                if (Collision::IsColliding(boxA, boxB, angleOfA, angleOfB)) {
                    objA->NotifyCollision(*objB);
                    objB->NotifyCollision(*objA);
                }
            }
        }
    }

}

void State::Render() {
  
 
  
   for (unsigned int i = 0; i < objectArray.size(); i++) {
   
   objectArray[i]->Render();
  
  }

}

bool State::QuitRequested() {
    return quitRequested;
}


State::~State() {
    
    objectArray.clear();
}




void State::AddObject(int mouseX , int mouseY)  {





 
}

void State::Start(){

  LoadAssets();
   
  for (unsigned int i = 0; i < State::objectArray.size(); i++) {
    State::objectArray[i]->Start();
  }
  State::started = true;

}

std::weak_ptr< GameObject > State::AddObject(GameObject* go){
 
 shared_ptr<GameObject> gameObject(go);
    objectArray.push_back(gameObject);
    if(started){
        gameObject->Start();
    }
    return weak_ptr<GameObject>(gameObject);

}


std::weak_ptr< GameObject > State::GetObjectPtr(GameObject* go){
 for (auto &i : objectArray) {
        if(i.get() == go){
            return weak_ptr<GameObject>(i);
        }
    }
    return weak_ptr<GameObject>();
}