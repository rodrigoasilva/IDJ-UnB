#ifndef PENGUINCANNNON_H 
#define PENGUINCANNNON_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "Component.h"
#include <vector>
#include "Timer.h"

class PenguinCannon: public Component {
private:
    std::weak_ptr< GameObject > pbody;
    float angle; 
    Timer cooldown;
public:

    PenguinCannon(GameObject& associated,std::weak_ptr< GameObject > penguinBody);
    void Update(float dt);
    void Render();
    bool Is(string type);
    void Shoot();
    void NotifyCollision(GameObject& other);


};
#endif