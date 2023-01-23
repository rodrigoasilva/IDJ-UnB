#include <cstdlib>
#include <iostream>
#include <ctime>
#include "SDL_include.h"
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include <Game.h>
#include <Camera.h>
#include <InputManager.h>
#include "Collider.h"
#include <queue>
#include <memory>
#include <vector>


Collider::Collider(GameObject& associated , Vec2  scale , Vec2  offset ) : Component(associated), scale(scale), offset(offset){



}

void Collider::Update(float dt){

    Rect aux = Rect();

    aux.w = associated.box.w * scale.x;
    aux.h = associated.box.h * scale.y;

    const Vec2 &center = associated.box.GetCenter();
    aux.x = center.x - aux.w/2;
    aux.y = center.y - aux.h/2;

    box = aux + offset.RotateDeg((float)(associated.angleDeg));

}

void Collider::Render(){

#ifdef DEBUG
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).Rotate( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).Rotate( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).Rotate( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG

 
 }

bool Collider::Is(string type){

    if(type.compare("Collider") == 0){
        
        return true;
    }
    return false;

 }


void Collider::SetScale(Vec2 scale){

    this->scale = scale;

  }

void Collider::SetOffset(Vec2 offset){

    this->offset = offset;

  }

