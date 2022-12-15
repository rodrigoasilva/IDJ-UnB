#include <cstdlib>
#include <iostream>
#include <ctime>
#include "SDL_include.h"
#include "Game.h"
#include "State.h"
#include "Face.h"
#include <math.h>
#include "Vec2.h"
#include "Sound.h"
#include "Sprite.h"
#include "TileMap.h"
#include "TileSet.h"

using namespace std;

State::State()  : music(Music()){

  GameObject* bg = new GameObject();
  bg->box.x = 0;
  bg->box.y = 0;
  bg->AddComponent(new Sprite(*bg, "img/ocean.jpg"));
  objectArray.emplace_back(bg);
 


  GameObject* tileMap = new GameObject();
  TileSet* tileSet = new TileSet(64, 64, "img/tileset.png");
  tileMap->box.x = 0;
  tileMap->box.y = 0;
  tileMap->AddComponent(new TileMap(*tileMap, "map/tileMap.txt", tileSet));
  objectArray.emplace_back(tileMap);
  quitRequested = false;

}

void State::LoadAssets() {

	music.Open("audio/stageState.ogg");
    music.Play();

}

void State::Update(float dt) {

   
 Input();



  for (int i = (int)objectArray.size() - 1; i >= 0; i--) {
    State::objectArray.at(i)->Update(dt);
  }
  /* Sweep of dead objects around the game. */
  for (int i = (int)objectArray.size() - 1; i >= 0; i--) {
    if (objectArray.at(i)->IsDead()) {
        printf("State::Update ta tocando musica\n");
        objectArray.erase(objectArray.begin() + i);
    }
  }

}

void State::Render() {

   for (unsigned int i = 0; i < objectArray.size(); i++) {
   objectArray.at(i).get()->Render();
  }

}

bool State::QuitRequested() {
    return quitRequested;
}


State::~State() {
    
    objectArray.clear();
}


void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);

	while (SDL_PollEvent(&event)) {

		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		

		if(event.type == SDL_MOUSEBUTTONDOWN) {

			for(int i = objectArray.size() - 1; i >= 0; --i) {

				GameObject* go = (GameObject*) objectArray[i].get();
				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).Rotate( -3.14156 + 3.14156*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject (int mouseX , int mouseY)  {

	 GameObject* penguim = new GameObject();

  
  penguim->box.x = mouseX;
  penguim->box.y = mouseY;

  
  penguim->AddComponent(new Sprite(*penguim, "img/penguinface.png"));
  penguim->AddComponent(new Sound(*penguim, "audio/boom.wav"));
  penguim->AddComponent(new Face(*penguim));

  penguim->box.x -= static_cast<Sprite*>(penguim->GetComponent("Sprite"))->GetWidth() / 2;
  penguim->box.y -= static_cast<Sprite*>(penguim->GetComponent("Sprite"))->GetHeight() / 2;

  penguim->box.x -=
      static_cast<Sprite*>(penguim->GetComponent("Sprite"))->GetWidth() / 2;
  penguim->box.y -=
      static_cast<Sprite*>(penguim->GetComponent("Sprite"))->GetHeight() / 2;

  
  objectArray.emplace_back(penguim);



 
}