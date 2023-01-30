#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "State.h"






State::State(){

started = false;
popRequested = false;
quitRequested = false;

}



bool State::QuitRequested() {
    return quitRequested;
}


State::~State() {
     for(auto it = objectArray.rbegin(); it != objectArray.rend(); ++it) {
        (*it).reset();
    }
    
    objectArray.clear();
}

bool State::PopRequested() {
    return popRequested;
}

bool State::isDebug() const {
    return debug;
}

void State::setDebug(bool debug) {
    this->debug = debug;
}

void State::StartArray() {
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Start();
    }
    started = true;
}

void State::UpdateArray(float dt) {
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Update(dt);
    }
}

void State::RenderArray() {
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Render();
    }
}






std::weak_ptr< GameObject > State::AddObject(GameObject* go){
 
 shared_ptr<GameObject> gameObject(go);
    objectArray.push_back(gameObject);
    if(started){
        gameObject->Start();
    }
    return weak_ptr<GameObject>(gameObject);

}


std::weak_ptr< GameObject > State::GetObjectPtr(GameObject* go){
 for (auto &i : objectArray) {
        if(i.get() == go){
            return weak_ptr<GameObject>(i);
        }
    }
    return weak_ptr<GameObject>();
}