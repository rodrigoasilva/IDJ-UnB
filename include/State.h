#ifndef STATE_H 
#define STATE_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include <vector>
#include <memory>
#include "GameObject.h"
#include <algorithm>
#include <string>


class State {
protected:
 
   bool started;
   bool popRequested;
   bool quitRequested;
   void StartArray();
   virtual void UpdateArray(float dt);
   virtual void RenderArray();
   bool debug = false;
   std::vector<std::shared_ptr<GameObject>> objectArray;
public:
    State();
    virtual ~State();
    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    bool PopRequested();
    std::weak_ptr< GameObject > AddObject(GameObject* go);
    std::weak_ptr< GameObject > GetObjectPtr(GameObject* go);
    bool QuitRequested();
    virtual void LoadAssets() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    bool isDebug() const;
    void setDebug(bool debug);
 
};
#endif