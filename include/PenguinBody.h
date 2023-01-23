#ifndef PENGUINBODY_H 
#define PENGUINBODY_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "Component.h"

class PenguinBody: public Component {

private:
    std::weak_ptr< GameObject > pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;


public:

    PenguinBody(GameObject& associated);
    ~PenguinBody();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    static PenguinBody* player;
    void NotifyCollision(GameObject& other);
    Vec2 GetPlayerCenter();





};
#endif

