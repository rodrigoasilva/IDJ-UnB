#ifndef SPRITE_H 
#define SPRITE_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "Component.h"
#include "Timer.h"
 
class Sprite : public Component{
private:
    shared_ptr<SDL_Texture> texture;
    int width;
    int height;
    SDL_Rect clipRect;
    Vec2 scale; 
    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
    float secondsToSelfDestruct;
    Timer selfDestructCount;

public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated,string file,int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
    ~Sprite();
    void Open(string file);
    void SetClip(int x , int y , int w, int h);
    void Render(int x , int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    bool Is(string type);
    void Update(float dt);
    void Render();
    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();
    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);

};
#endif