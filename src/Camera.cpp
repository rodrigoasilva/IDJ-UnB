#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <Game.h>
#include <InputManager.h>
#include "Camera.h"

Vec2 Camera::pos = *new Vec2();
Vec2 Camera::speed = *new Vec2();
GameObject *Camera::focus = nullptr;

void Camera::Follow( GameObject* newFocus){

    focus = newFocus;
}

void Camera::Unfollow(){

 focus = nullptr;
}

void Camera::Update(float dt){
    
    if(focus != nullptr){
        pos = {focus->box.x - 512 + focus->box.w/2, focus->box.y -300 +focus->box.h/2};
    } else {
        
        speed = {0, 0};
        Vec2 direcional = { 100*dt, 0};

        bool right = InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY);
        bool down = InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY);
        bool left = InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY);
        bool up = InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY);

        if (right) {
            speed = direcional;
        } else if (down) {
            speed = direcional.Rotate((float) M_PI / 2);
        } else if (left) {
            speed = direcional.Rotate((float) M_PI);
        } else if (up) {
            speed = direcional.Rotate((float)-M_PI / 2);
        }

        if(right && down){
            speed = direcional.Rotate((float) M_PI / 4);
        } else if(left && down){
            speed = direcional.Rotate((float) 3 * M_PI / 4);
        } else if(left && up){
            speed = direcional.Rotate((float) -3 * M_PI / 4);
        } else if(right && up){
            speed = direcional.Rotate((float) -M_PI / 4);
        }

        pos += speed;
    }

}