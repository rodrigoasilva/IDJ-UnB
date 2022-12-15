#ifndef GAMEOBJECT_H 
#define GAMEOBJECT_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Component.h"
#include <string>
#include <vector>
#include <memory>
#include "Rect.h"


class Component;

class GameObject
{
private:
  bool isDead;
  vector<unique_ptr<Component>> components;
 
public:
  GameObject();
  ~GameObject();
  void Update(float dt);
  void Render();
  void RequestDelete();
  void AddComponent(Component* cpt);
  void RemoveComponent(Component* cpt);
  Component* GetComponent(string type);
  Rect box;
  bool IsDead();
 
};
#endif
