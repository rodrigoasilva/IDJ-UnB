#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;
#include <Camera.h>
#include "InputManager.h"


InputManager& InputManager::GetInstance(){

    static InputManager S;
    return S;

}

InputManager::InputManager(){
    
    memset(mouseState, 0, sizeof(mouseState));
    memset(mouseUpdate, 0, sizeof(mouseUpdate));
    mouseX = 0;
    mouseY = 0;
    updateCounter = 0;
    quitRequested = false;

}
InputManager::~InputManager(){


}

void InputManager::Update(){


    SDL_Event event;
    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;

   
    
    while(SDL_PollEvent(&event)) { 

         if (event.key.repeat != 1) {
      if (event.type == SDL_QUIT) {
        InputManager::quitRequested = true;
      }
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        InputManager::mouseState[event.button.button] = true;
        InputManager::mouseUpdate[event.button.button] = InputManager::updateCounter;
      }
      if (event.type == SDL_MOUSEBUTTONUP) {
        InputManager::mouseState[event.button.button] = false;
        InputManager::mouseUpdate[event.button.button] = InputManager::updateCounter;
      }
      if (event.type == SDL_KEYDOWN) {
        InputManager::keyState[event.key.keysym.sym] = true;
        InputManager::keyUpdate[event.key.keysym.sym] = InputManager::updateCounter;
      }
      if (event.type == SDL_KEYUP) {
        InputManager::keyState[event.key.keysym.sym] = false;
        InputManager::keyUpdate[event.key.keysym.sym] = InputManager::updateCounter;
      }
    }
  }

    }






bool InputManager::KeyPress(int key) {
    return keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key) {
    return !keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button) {
    return !mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

int InputManager::GetMouseX(){

    return mouseX;
}


int InputManager::GetMouseY(){

    return mouseY;
}

bool InputManager::QuitRequested(){

    return quitRequested;
}