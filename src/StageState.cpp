#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include <Alien.h>
#include <PenguinBody.h>
#include <StageState.h>
#include "TitleState.h"
#include <Collider.h>
#include <TileMap.h>
#include <Collision.h>
#include "GameData.h"
#include "EndState.h"



StageState::StageState()  : backgroundMusic(Music()){
 started = false;
    auto bgGO(new GameObject);
    bgGO->AddComponent(new CameraFollower(*bgGO));
    bgGO->AddComponent(new Sprite(*bgGO, "img/ocean.jpg"));

    objectArray.emplace_back(bgGO);

    auto mapGO(new GameObject);

    TileSet *tileSet = new TileSet(64, 64, "img/tileset.png");
    TileMap *tileMap = new TileMap(*mapGO, "map/tileMap.txt", tileSet);
    mapGO->AddComponent(tileMap);
    objectArray.emplace_back(mapGO);

    auto penguinBodyGO(new GameObject);
    penguinBodyGO->box += {704, 640};
    penguinBodyGO->AddComponent(new PenguinBody(*penguinBodyGO));
    Camera::Follow(penguinBodyGO);
    objectArray.emplace_back(penguinBodyGO);

    auto alien1GO(new GameObject);
    Rect &alien1Box = alien1GO->box;
    alien1Box += {512 + alien1Box.w/2, 300 + alien1Box.h/2};
    alien1GO->AddComponent(new Alien(*alien1GO,8));
    objectArray.emplace_back(alien1GO);

    auto alien2GO(new GameObject);
    Rect &alien2Box = alien2GO->box;
    alien2Box += {112 + alien2Box.w/2, 800 + alien2Box.h/2};
    alien2GO->AddComponent(new Alien(*alien2GO,8));
    objectArray.emplace_back(alien2GO);

    auto alien3GO(new GameObject);
    Rect &alien3Box = alien3GO->box;
    alien3Box += {712 + alien3Box.w/2, 900 + alien3Box.h/2};
    alien3GO->AddComponent(new Alien(*alien3GO, 8));
    objectArray.emplace_back(alien3GO);

    quitRequested = false;




}

void StageState::LoadAssets() {

	backgroundMusic.Open("audio/stageState.ogg");
   backgroundMusic.Play();

}

void StageState::Update(float dt){
  int mouseX, mouseY;
      

  SDL_GetMouseState(&mouseX, &mouseY);
  Camera::Update(dt);  
  State::quitRequested = InputManager::GetInstance().QuitRequested();
  popRequested =InputManager::GetInstance().KeyPress(ESCAPE_KEY);

  if(InputManager::GetInstance().KeyPress(SDLK_F6)) {
        setDebug(!isDebug());
    }
 
 UpdateArray(dt);
  
 
  
  if(InputManager::GetInstance().MousePress(SDL_QUIT)) {
				quitRequested = true;
			} 
  

      if (Alien::alienCount == 0 || PenguinBody::player == nullptr) {
        GameData::playerVictory = PenguinBody::player != nullptr;
        popRequested = true;
        Game::GetInstance().Push(new EndState());
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

void StageState::Render() {
  
 
  for (auto &it : objectArray) {
        it->Render();
    }

}



StageState::~StageState() {
    
    objectArray.clear();
}



void StageState::Start(){

  LoadAssets();
   
  StartArray();
  State::started = true;

}
void StageState::Pause() {}

void StageState::Resume() {}

