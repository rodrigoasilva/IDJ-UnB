#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "GameObject.h"


GameObject::GameObject() : box(Rect()), started(false)  {
  angleDeg=0;
 isDead = false;
    
}

GameObject::~GameObject()  {

    
    components.clear();
}


void GameObject::Update(float dt)  {

    for (int i = (int)components.size() - 1; i >= 0; i--) {
    components.at(i)->Update(dt);
  }
   

}

void GameObject::Render()  {

     for (unsigned int i = 0; i < components.size(); i++) {
        components.at(i)->Render();
  }
    
}

bool GameObject::IsDead()  {

    return isDead;
}

void GameObject::RequestDelete()  {

    isDead = true ;
}

void GameObject::AddComponent(Component *cpt){

 components.emplace_back(cpt);
 if(started){
        cpt->Start();
    }

}

void GameObject::RemoveComponent(Component *cpt){

   unsigned int posicao = 0;
  bool naoEsta = true;
  while (posicao != components.size()) {
    
    if (components.at(posicao).get() == cpt) {
      components.erase(components.begin() + posicao);
      naoEsta = false;
      break;
    }
  }

  
    
}

Component* GameObject::GetComponent(string type){

  for (int i = (int)components.size() - 1; i >= 0; i--) {
    if (components.at(i)->Is(type)) {
      return components.at(i).get(); 
      return components.at(i).get();
    }
  }
  return nullptr;    
    
}

void GameObject::Start(){



    for (auto &compon : components) {
        compon->Start();
    } 

 started = true;


}

void GameObject::NotifyCollision(GameObject& other){

  for(int i = 0; i < components.size(); i++){

      components[i]->NotifyCollision(other);
      
    }

}