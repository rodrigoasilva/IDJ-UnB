#ifndef TILESET_H 
#define TILESET_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "GameObject.h"
#include "Sprite.h"

class TileSet{
private:
   Sprite tileSet;
   int rows;
   int columns;
   int tileWidth;
   int tileHeight;
 
public:

    TileSet(int tileWidth, int tileHeight, string file);
    void RenderTile(unsigned int index,float x , float y);
    int GetTileWidth();
    int GetTileHeight();

};
#endif