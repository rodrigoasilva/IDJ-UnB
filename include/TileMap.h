#ifndef TILEMAP_H 
#define TILEMAP _H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "TileSet.h"
#include "Component.h"
#include "GameObject.h"


class TileMap : public Component{
private:
    vector<int> tileMatrix;
    TileSet*  tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
 
public:
    TileMap(GameObject& associated, string file,TileSet* tileSet);
    void Load(string file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y,  int z = 0); 
    void Render();
    void RenderLayer(int layer, int cameraX  = 0, int cameraY  = 0);
    int GetWidth(); 
    int GetHeight();
    int GetDepth();
    bool Is(string type);
    void Update(float dt);
     

};
#endif