#ifndef SPRITE_H 
#define SPRITE_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "Component.h"

 
class Sprite : public Component{
private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;

public:
    Sprite(GameObject& associated);
    explicit Sprite(GameObject& associated,string file);
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

};
#endif