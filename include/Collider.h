#ifndef COLLIDER_H 
#define COLLIDER_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "Component.h"
#include "Rect.h"
#include "Vec2.h"
#include <vector>


class Collider: public Component {

private:
    Vec2 scale;
    Vec2 offset;
public:

    Collider(GameObject& associated , Vec2  scale  = {1, 1}, Vec2  offset = {0, 0});
    Rect box;
    void Update(float dt);
    void Render();
    bool Is(string type); 
    void SetScale(Vec2 scale );
    void SetOffset(Vec2 offset );
   
    

};

#endif